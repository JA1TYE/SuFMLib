#include <cstdint>
#include <cstdio>

#include "op.h"
#include "synth_config.h"
#include "synth_param.h"
#include "synth_util.h"

namespace su_synth::fm{
    /*In this class we use a fixed-point number expression like this:
    # for signed value
    - sign:1bit
    - integer:1bit
    - decimal:14bit
    # for multiplier param
    - integer:8bit
    - decimal:8bit
    */
    fm_operator::fm_operator(){
        
    }

    void fm_operator::set_param(op_param_t* p){
        param_ = p;
        osc.set_param(p);
        eg.set_param(p);
    }

    void fm_operator::set_control(control_value_t* c){
        eg.set_control(c);
    }

    void fm_operator::apply_pitch_mod(std::int32_t in){
        pitch_mod_value_ = ((std::int64_t)in * param_->lfo_pitch_sensitivity) / 0x8000;
        osc.set_delta(delta_ + pitch_mod_value_);
    }

    void fm_operator::apply_amp_mod(std::uint16_t in){
        std::uint16_t tmp;
        tmp = (in * param_->lfo_amp_sensitivity) / 0x8000;
        amp_mod_value_ = util::eg_exp_minus(tmp);
    }

    void fm_operator::set_delta(std::uint32_t delta){
        delta_ = delta;
        osc.set_delta(delta_ + pitch_mod_value_);
    }

    void fm_operator::trigger_on(std::uint8_t note,std::uint16_t velocity){
        osc.reset_phase();
        eg.trigger_on(note,velocity);
        osc.set_delta(delta_ + pitch_mod_value_);
    }

    void fm_operator::trigger_off(){
        eg.trigger_off();
    }

}