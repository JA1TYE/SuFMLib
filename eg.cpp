#include <cstdint>
#include "synth_util.h"
#include "eg.h"
#include "synth_param.h"
#include "table.h"
#include "stdio.h"

namespace su_synth{
    /*In this class we use a fixed-point number expression like this:
        # for signed value
        - sign:1bit
        - integer:1bit
        - decimal:14bit
        # for unsigned value
        - integer:1bit
        - decimal:15bit
        # for key rate scaling
        - integer:8bit
        - decimal:8bit
    */
    envelope_generator::envelope_generator(){
        eg_state_ = EG_WAIT;
        amp_ = 0;
        eg_counter_ = 0;
    }

    eg_retrig_t envelope_generator::trigger_option = EG_RETRIG_ZERO;

    void envelope_generator::calc_params(void){
        //calculate final level
        final_level_ = param_->total_level * lookup_level_scale(note_) >> 15;
        final_level_ = final_level_ * calc_final_velocity(velocity_) >> 15;
        //calculate key rate scaling coeff.
        std::uint16_t key_rate_coeff = lookup_rate_scale(note_);
        //set final value of adsr rate
        final_attack_rate_ = util::saturate((std::uint32_t)(param_->attack_rate) * key_rate_coeff >> 8,0x8000);
        final_decay_rate_ = util::saturate((std::uint32_t)(param_->decay_rate) * key_rate_coeff >> 8,0x8000);
        final_sustain_rate_ = util::saturate((std::uint32_t)(param_->sustain_rate) * key_rate_coeff >> 8,0x8000);
        final_release_rate_ = util::saturate((std::uint32_t)(param_->release_rate) * key_rate_coeff >> 8,0x8000);
    }

    void envelope_generator::set_param(op_param_t *p){
        param_ = p;
        calc_params();
    }

    void envelope_generator::set_control(control_value_t* c){
        control_ = c;
    }

    void envelope_generator::update(void){
        std::int32_t t = 0;
        if(eg_state_ == EG_FORCE_DUMP){
            eg_counter_ = eg_counter_ + FORCE_DUMP_RATE;
            if(eg_counter_ >= 0x8000){
                t = 0;
            }
            else{
                t = start_amp_ * util::eg_exp_minus(eg_counter_) >> 15;
            }
            if(t == 0){
                eg_counter_ = 0;
                eg_state_ = EG_ATTACK;
            }
        }
        else if(eg_state_ == EG_ATTACK){
            eg_counter_ = eg_counter_ + final_attack_rate_;
            if(eg_counter_ >= 0x8000){
                t = 0x8000;
                eg_counter_ = 0;
                eg_state_ = EG_DECAY;
            }
            else{
                t = ((0x8000 - start_amp_) * util::eg_exp_minus(util::eg_exp_minus(eg_counter_))>>15) + start_amp_;
                if(t >= 0x8000){
                    t = 0x8000;
                    eg_counter_ = 0;
                    eg_state_ = EG_DECAY;
                }
            }
        }
        else if(eg_state_ == EG_DECAY){
            eg_counter_ = eg_counter_ + final_decay_rate_;
            if(eg_counter_ >= 0x8000){
                t = param_->sustain_level;
                eg_counter_ = 0;
                eg_state_ = EG_SUSTAIN;
            }
            else{
                t = (0x8000 * util::eg_exp_minus(eg_counter_) >> 15);
                //t = ((0x8000 - param_->sustain_level) * util::eg_exp_minus(eg_counter_) >> 15) + param_->sustain_level;
                if(t <= param_->sustain_level){
                    t = param_->sustain_level;
                    eg_counter_ = 0;
                    eg_state_ = EG_SUSTAIN;
                }
            }
            if(t == 0){
                eg_state_ = EG_WAIT;
            }
        }
        else if(eg_state_ == EG_SUSTAIN){
            eg_counter_ = eg_counter_ + final_sustain_rate_;
            if(eg_counter_ >= 0x8000){
                eg_counter_ = 0;
                t = 0;
            }
            else{
                t = param_->sustain_level * util::eg_exp_minus(eg_counter_) >> 15;
            }
            if(t == 0){
                eg_state_ = EG_WAIT;
            }
        }
        else if(eg_state_ == EG_SUSTAIN_HOLD){
            eg_counter_ = eg_counter_ + final_sustain_rate_;
            if(eg_counter_ >= 0x8000){
                eg_counter_ = 0;
                t = 0;
            }
            else{
                t = start_amp_ * util::eg_exp_minus(eg_counter_) >> 15;
                if(control_->hold == false){
                    start_amp_ = t;
                    eg_counter_ = 0;
                    eg_state_ = EG_RELEASE; 
                }
            }
            if(t == 0){
                eg_state_ = EG_WAIT;
            }
        }
        else if(eg_state_ == EG_RELEASE){
            eg_counter_ = eg_counter_ + final_release_rate_;
            if(eg_counter_ >= 0x8000){
                eg_counter_ = 0;
                t = 0;
            }
            else{
                t = start_amp_ * util::eg_exp_minus(eg_counter_) >> 15;
            }
            if(t == 0){
                eg_state_ = EG_WAIT;
            }
        }
        amp_ = t;
        return;
    }
    std::uint16_t envelope_generator::lookup_rate_scale(std::uint8_t note){
        std::uint32_t ret = 0x100;
        std::uint8_t scale = param_->key_rate_scale; 
        ret = 0x100 + (note * scale >> 6);
        if(ret > 0x200)ret = 0x200;//clip
        return (std::uint16_t)ret;
    }
    
    std::uint16_t envelope_generator::lookup_level_scale(std::uint8_t note){
        std::uint32_t ret = 0x8000;
        std::uint16_t scale = param_->key_level_scale;
        ret = note * scale >> 6;
        if(ret > 0x8000)ret = 0x8000;
        ret = 0x8000 - ret;
        return ret;
    }

    std::uint16_t envelope_generator::calc_final_velocity(std::uint16_t velocity){
        if(param_->velocity_sensitivity == 0)return 0x8000;
        return 0x8000 - ((0x8000 - velocity) >> ((7 - param_->velocity_sensitivity) * 2));
    }

    void envelope_generator::trigger_on(std::uint8_t note,std::uint16_t velocity){
        note_ = note;
        velocity_ = velocity;
        calc_params();
        //Prepare EG state
        if(trigger_option == EG_RETRIG_ZERO){
            amp_ = 0;
            start_amp_ = 0;
            eg_counter_ = 0;
            eg_state_ = EG_ATTACK;
        }
        else if(trigger_option == EG_RETRIG_FORCE_DUMP){
            if(amp_ != 0){
                start_amp_ = amp_;
                eg_counter_ = 0;
                eg_state_ = EG_FORCE_DUMP;
            }
            else{
                amp_ = 0;
                start_amp_ = 0;
                eg_counter_ = 0;
                eg_state_ = EG_ATTACK;
            }
        }
        else if(trigger_option == EG_RETRIG_KEEP){
            start_amp_ = amp_;
            eg_counter_ = 0;
            eg_state_ = EG_ATTACK;
        }
    }

    void envelope_generator::trigger_off(){
        if(eg_state_ != EG_WAIT){
            if(control_->hold == true){//HOLD mode
                if(eg_state_ != EG_SUSTAIN){
                    if(eg_state_ != EG_RELEASE){
                        start_amp_ = amp_;
                        eg_counter_ = 0;
                    }
                }
                else{
                    start_amp_ = amp_;
                }
                eg_state_ = EG_SUSTAIN_HOLD;
            }
            else{
                start_amp_ = amp_;
                eg_counter_ = 0;
                eg_state_ = EG_RELEASE;
            }
        }
    }

    bool envelope_generator::is_wait(){
        if(eg_state_ == EG_WAIT)return true;
        return false;
    }
}