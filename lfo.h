#ifndef _LFO_H_
#define _LFO_H_

#include <cstdint>
#include "synth_param.h"

namespace su_synth{
    class lfo{
        private:
            typedef enum{
                LFO_EG_WAIT,
                LFO_EG_DELAY,
                LFO_EG_ATTACK,
                LFO_EG_SUSTAIN
            }lfo_eg_state_t;

            lfo_eg_state_t  state_;
            control_value_t* control_;
            synth_param_t* param_;
            std::uint32_t acc_;
            std::uint32_t noise_shift_;
            std::uint16_t delay_counter_;
            std::uint8_t sample_trigger_;
            std::int16_t sample_;
        public:
            lfo();
            std::uint16_t eg_level;
            void trigger_on(void);
            void prepare_sample(void);
            std::int32_t calc_pitch(std::uint32_t lower,std::uint32_t upper);
            std::uint16_t calc_amp(void);
            void eg_update(void);
            void set_control(control_value_t* c);
            void set_param(synth_param_t* p);
            void reset_phase();
            static const std::uint8_t PITCH_MOD_RANGE = 12;
    };
}

#endif
 