#include <cstdint>
#include <stdio.h>
#include "synth_config.h"
#include "fmtone.h"
#include "table.h"
#include "synth_ctrl.h"
#include "synth_param.h"

namespace su_synth{
    /*In this class we use a fixed-point number expression like this:
    # for signed value
    - sign:1bit
    - integer:1bit
    - decimal:14bit
    # for feedback amount and velocity param
    - integer:1bit
    - decimal:15bit
    */
    fm_tone::fm_tone(){
        feedback_buf_[0] = 0;
        feedback_buf_[1] = 0;
        decimation_counter_ = 0;
        algo_p_ = &fm_tone::algo_func_0;
    }

    void fm_tone::select_algo(void){
        //Assign algo function
        if(param_->fm_algorithm == ALGO_0){
            algo_p_ = &algo_func_0; 
        }
        else if(param_->fm_algorithm == ALGO_1){
            algo_p_ = &algo_func_1; 
        }
        else if(param_->fm_algorithm == ALGO_2){
            algo_p_ = &algo_func_2; 
        }
        else if(param_->fm_algorithm == ALGO_3){
            algo_p_ = &algo_func_3; 
        }
        else if(param_->fm_algorithm == ALGO_4){
            algo_p_ = &algo_func_4; 
        }
        else if(param_->fm_algorithm == ALGO_5){
            algo_p_ = &algo_func_5; 
        }
        else if(param_->fm_algorithm == ALGO_6){
            algo_p_ = &algo_func_6; 
        }
        else if(param_->fm_algorithm == ALGO_7){
            algo_p_ = &algo_func_7; 
        }
        else{
            algo_p_ = &algo_func_0; 
        }
    }

    void fm_tone::set_control(control_value_t* c){
        control_ = c;
        lfo_.set_control(control_);
        for(int i = 0;i < NUM_OPERATOR;i++){
            op[i].set_control(control_);
        }
    }

    void fm_tone::set_param(synth_param_t* p){
        param_ = p;
        lfo_.set_param(param_);
        for(int i = 0;i < NUM_OPERATOR;i++){
            op[i].set_param(&(param_->op_params[i]));
        }
        select_algo();
    }

    void fm_tone::set_pitchbend(std::int16_t value){
        std::uint32_t delta;
        if(value <= 0){
            delta = (std::int64_t)pitch_center_ + (((std::int64_t)pitch_lower_*value) / 8192);
        }
        else{
            delta = (std::int64_t)pitch_center_ + (((std::int64_t)pitch_upper_*value) / 8192);
        }
        current_pitch_ = delta;
        for(int i = 0;i < NUM_OPERATOR;i++){
            op[i].set_delta(current_pitch_);
        }
    }

    void fm_tone::trigger_on(std::uint8_t note,std::uint16_t velocity){
        //Assign algo function
        select_algo();
        //Calculate pitch parameters
        pitch_center_ = synth_controller::lookup_delta(note,param_->note_offset);
        pitch_lower_ = pitch_center_ - 
                       synth_controller::lookup_delta(note,param_->note_offset-param_->pitchbend_sensitivity);
        pitch_upper_ = synth_controller::lookup_delta(note,param_->note_offset+param_->pitchbend_sensitivity)
                       - pitch_center_;
        current_pitch_ = pitch_center_;
        mod_pitch_lower_ = pitch_center_ - 
                       synth_controller::lookup_delta(note,param_->note_offset-lfo::PITCH_MOD_RANGE);
        mod_pitch_upper_ = synth_controller::lookup_delta(note,param_->note_offset+lfo::PITCH_MOD_RANGE)
                       - pitch_center_;
        //Reset LFO/EG decimation counter
        decimation_counter_ = 0;
        //Reset feedback buffer
        feedback_buf_[0] = 0;
        feedback_buf_[1] = 0;
        //Trigger operator
        for(int i = 0;i < NUM_OPERATOR;i++){
            op[i].trigger_on(note,velocity);
            op[i].set_delta(current_pitch_);
        }
        //Trigger LFO
        lfo_.trigger_on();
    }

    void fm_tone::trigger_off(){
        for(int i = 0;i < NUM_OPERATOR;i++){
            op[i].trigger_off();
        }
    }

    std::int16_t fm_tone::calc(void){
        std::int32_t ret = 0;
        std::int32_t lfo_pitch;
        std::uint16_t lfo_amp;
        //Process Low-Frequency(EG/LFO etc.) Update
        if(decimation_counter_ == 0){
            //Update LFO
            lfo_.eg_update();
            lfo_.prepare_sample();
            lfo_pitch = lfo_.calc_pitch(mod_pitch_lower_,mod_pitch_upper_);
            lfo_amp = lfo_.calc_amp();
            for(int i = 0;i < NUM_OPERATOR;i++){
                //Update LFO
                op[i].apply_pitch_mod(lfo_pitch);
                op[i].apply_amp_mod(lfo_amp);
                //Update EG
                op[i].update();
            }
        }
        decimation_counter_ = (decimation_counter_ == (DECIMATION_RATE - 1))?0:decimation_counter_ + 1;

        //Calc Operators operations
        ret = algo_p_(this);
        //Return sample as 16-bit signed value
        return ret / 0x10000;
    }

    std::int32_t fm_tone::algo_func_0(fm_tone* inst){
        std::int32_t tmp;
        /*
        [3]->[2]->[1]->[0]
        */
        tmp = ((std::int64_t)inst->feedback_buf_[0] + inst->feedback_buf_[1]) / 2;
        tmp = inst->op[3].calc(tmp);
        inst->feedback_buf_[1]  = inst->feedback_buf_[0];
        inst->feedback_buf_[0] = (std::int64_t)tmp * (inst->param_->feedback_amount) / 0x8000;
        return inst->op[0].calc(inst->op[1].calc(inst->op[2].calc(tmp)));
    }

    std::int32_t fm_tone::algo_func_1(fm_tone* inst){
        std::int32_t tmp;
        /*
        [3]->[1]->[0]
        [2]/
        */
        tmp = ((std::int64_t)inst->feedback_buf_[0] + inst->feedback_buf_[1]) / 2;
        tmp = inst->op[3].calc(tmp);
        inst->feedback_buf_[1]  = inst->feedback_buf_[0];
        inst->feedback_buf_[0] = (std::int64_t)tmp * (inst->param_->feedback_amount) / 0x8000;
        tmp = tmp / 2;
        tmp += inst->op[2].calc(0) / 2;
        return inst->op[0].calc(inst->op[1].calc(tmp));
    }

    std::int32_t fm_tone::algo_func_2(fm_tone* inst){
        std::int32_t tmp;
        /*
        [2]->[1]->[0]
                [3]/
        */
        tmp = ((std::int64_t)inst->feedback_buf_[0] + inst->feedback_buf_[1]) / 2;
        tmp = inst->op[3].calc(tmp);
        inst->feedback_buf_[1]  = inst->feedback_buf_[0];
        inst->feedback_buf_[0] = (std::int64_t)tmp * (inst->param_->feedback_amount) / 0x8000;
        tmp = tmp / 2;
        tmp += inst->op[1].calc(inst->op[2].calc(0)) / 2;
        return inst->op[0].calc(tmp);
    }

    std::int32_t fm_tone::algo_func_3(fm_tone* inst){
        std::int32_t tmp;
        /*
        [3]->[2]\
                [1]->[0]
        */
        tmp = ((std::int64_t)inst->feedback_buf_[0] + inst->feedback_buf_[1]) / 2;
        tmp = inst->op[3].calc(tmp);
        inst->feedback_buf_[1]  = inst->feedback_buf_[0];
        inst->feedback_buf_[0] = (std::int64_t)tmp * (inst->param_->feedback_amount) / 0x8000;
        tmp = inst->op[2].calc(tmp) / 2;
        tmp += inst->op[1].calc(0) / 2;
        return inst->op[0].calc(tmp);
    }
    
    std::int32_t fm_tone::algo_func_4(fm_tone* inst){
        std::int32_t tmp;
        /*
        [3]->[2]
        [1]->[0]
        */
        tmp = ((std::int64_t)inst->feedback_buf_[0] + inst->feedback_buf_[1]) / 2;
        tmp = inst->op[3].calc(tmp);
        inst->feedback_buf_[1]  = inst->feedback_buf_[0];
        inst->feedback_buf_[0] = (std::int64_t)tmp * (inst->param_->feedback_amount) / 0x8000;
        tmp = inst->op[2].calc(tmp) / 2;
        return tmp + inst->op[0].calc(inst->op[1].calc(0)) / 2; 
    }

    std::int32_t fm_tone::algo_func_5(fm_tone* inst){
        std::int32_t tmp,ret;
        /*
            /-[2]
        [3]->[1]
            \-[0]
        */
        //10922 is approx. value of 1/3 in "1.15" expression 
        tmp = ((std::int64_t)inst->feedback_buf_[0] + inst->feedback_buf_[1]) / 2;
        tmp = inst->op[3].calc(tmp);
        inst->feedback_buf_[1]  = inst->feedback_buf_[0];
        inst->feedback_buf_[0] = (std::int64_t)tmp * (inst->param_->feedback_amount) / 0x8000;
        ret = inst->op[2].calc(tmp) * 10922LL / 0x8000;
        ret += inst->op[1].calc(tmp) * 10922LL / 0x8000;
        ret += inst->op[0].calc(tmp) * 10922LL / 0x8000;
        return ret;
    }

    std::int32_t fm_tone::algo_func_6(fm_tone* inst){
        std::int32_t tmp,ret;
        /*
        [3]->[2]
                [1]
                [0]
        */
        //10922 is approx. value of 1/3 in "1.15" expression 
        tmp = ((std::int64_t)inst->feedback_buf_[0] + inst->feedback_buf_[1]) / 2;
        tmp = inst->op[3].calc(tmp);
        inst->feedback_buf_[1]  = inst->feedback_buf_[0];
        inst->feedback_buf_[0] = (std::int64_t)tmp * (inst->param_->feedback_amount) / 0x8000;
        ret = inst->op[2].calc(tmp) * 10922LL / 0x8000;
        ret += inst->op[1].calc(0) * 10922LL / 0x8000;
        ret += inst->op[0].calc(0) * 10922LL / 0x8000;
        return ret;
    }

    std::int32_t fm_tone::algo_func_7(fm_tone* inst){
        std::int32_t tmp;
        /*
        [3]
        [2]
        [1]
        [0] 
        */
        tmp = ((std::int64_t)inst->feedback_buf_[0] + inst->feedback_buf_[1]) / 2;
        tmp = inst->op[3].calc(tmp);
        inst->feedback_buf_[1]  = inst->feedback_buf_[0];
        inst->feedback_buf_[0] = (std::int64_t)tmp * (inst->param_->feedback_amount) / 0x8000;
        tmp = tmp / 4;
        tmp += inst->op[2].calc(0) / 4;
        tmp += inst->op[1].calc(0) / 4;
        tmp += inst->op[0].calc(0) / 4;
        return tmp;
    }

}