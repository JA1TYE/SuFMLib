#include "stdio.h"
#include "lfo.h"
#include "synth_config.h"
#include "synth_param.h"
#include "synth_ctrl.h"
#include <cstdlib>
#include <math.h>
namespace su_synth{
    lfo::lfo(){
        acc_ = 0;
        noise_shift_ = 1;
        state_ = LFO_EG_WAIT;
        eg_level = 0;
        delay_counter_ = 0;
        sample_trigger_ = 0;
    }
    
    void lfo::set_param(synth_param_t* p){
        param_ = p;
    }

    void lfo::set_control(control_value_t* c){
        control_ = c;
    }

    void lfo::trigger_on(void){
        reset_phase();
        state_ = (param_->lfo_param.delay == 0)?LFO_EG_ATTACK:LFO_EG_DELAY;
        delay_counter_ = 0;
        eg_level = 0;
    }

    void lfo::eg_update(void){
        std::uint32_t tmp;
        //Simple EG Function
        if(state_ == LFO_EG_DELAY){
            delay_counter_++;
            if(delay_counter_ >= param_->lfo_param.delay){
                state_ = LFO_EG_ATTACK;                
            }
        }
        else if(state_ == LFO_EG_ATTACK){
            tmp = eg_level + (0x8001 - param_->lfo_param.delay);
            if(tmp >= 0x8000){
                eg_level = 0x8000;
                state_ = LFO_EG_SUSTAIN;
            }
            else{
                eg_level = tmp;
            }
        }
    }

    std::int32_t lfo::calc_pitch(std::uint32_t lower,std::uint32_t upper){
        std::int32_t value;
        std::uint32_t amount;
        if(sample_ <= 0){
            value = (lower * (std::int64_t)sample_) / 0x8000;
        }
        else{
            value = (upper * (std::int64_t)sample_) / 0x8000;
        }
        amount = control_->pitch_modulation_total;
        amount += (eg_level * (param_->lfo_param.pitch_modulation_depth))/0x8000;
        if(amount > 0x8000)amount = 0x8000;
        value = ((std::int64_t)value * amount) / 0x8000;
        return value;
    }

    std::uint16_t lfo::calc_amp(void){
        std::uint16_t value;
        std::uint32_t amount;
        value = (sample_ + 32768) / 2;
        amount = control_->amp_modulation_total;
        amount += (eg_level * (param_->lfo_param.amp_modulation_depth))/0x8000;
        if(amount > 0x8000)amount = 0x8000;
        value = value * amount / 0x8000;
        return value;
    }

    void lfo::prepare_sample(void){
        std::int32_t wave_out = 0;
        std::uint16_t idx;
        acc_ += param_->lfo_param.speed;
        idx = (acc_ >> 6) & 0xffff;
        if(param_->lfo_param.waveform == LFO_SAW){
            wave_out = idx;
            wave_out = wave_out - 32768;
            sample_ = (std::int16_t)wave_out;
        }
        else if(param_->lfo_param.waveform == LFO_TRI){
            if(idx < 0x4000){
                wave_out = idx;
            }
            else if(idx < 0x8000){
                wave_out = 16383 - (idx & 0x3fff);
            }
            else if(idx < 0xc000){
                wave_out = -(idx & 0x3fff);
            }
            else{
                wave_out = (idx & 0x3fff) - 16383;
            }
            sample_ =  (std::int16_t)(wave_out*2);
        }
        else if(param_->lfo_param.waveform == LFO_SQR){
            wave_out = (idx & 0x8000)?32767:-32768;
            sample_ = (std::int16_t)wave_out; 
        }
        else if(param_->lfo_param.waveform == LFO_SH){
            if((idx & 0x8000) != sample_trigger_ && (idx & 0x8000)){
                noise_shift_ = (noise_shift_ >> 1) ^ (-(noise_shift_ & 1) & 0xd0000001);
            }
            sample_trigger_ = idx & 0x8000;
            wave_out = noise_shift_;
            sample_ = (std::int16_t)wave_out;
        }
    }

    void lfo::reset_phase(void){
        acc_ = 0;
    }
    
}