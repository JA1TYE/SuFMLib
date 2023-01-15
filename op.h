#ifndef _OP_H_
#define _OP_H_
#include <cstdint>

#include "osc.h"
#include "eg.h"
#include "synth_param.h"

namespace su_synth::fm{
    class fm_operator{
        private:
            op_param_t* param_;
            std::int32_t pitch_mod_value_;
            std::uint16_t amp_mod_value_;
            std::uint32_t delta_;
        public:
            fm_operator();
            void apply_pitch_mod(std::int32_t in);
            void apply_amp_mod(std::uint16_t in);
            void set_param(op_param_t* p);
            void set_control(control_value_t* c);
            void set_delta(std::uint32_t delta);
            void trigger_on(std::uint8_t note,std::uint16_t velocity);
            void trigger_off(void);
            inline void update(void){
                //Update EG Counter
                eg.update();
            }
            inline std::int32_t calc(std::int32_t mod){
                std::int32_t ret;
                //Process FM operation
                ret = osc.calc_sample(mod);
                //Apply LFO amp modulation
                ret = (amp_mod_value_ * ret) / 0x8000;
                //Apply EG
                ret = eg.calc(ret);
                //Return the result
                return ret;
            }
            oscillator osc;
            envelope_generator eg;
    };
}

#endif