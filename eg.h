#ifndef _EG_H_
#define _EG_H_
#include <cstdint>
#include <cstdio>

#include "synth_param.h"
namespace su_synth::fm{
    typedef enum{
        EG_WAIT,
        EG_FORCE_DUMP,
        EG_ATTACK,
        EG_DECAY,
        EG_SUSTAIN,
        EG_SUSTAIN_HOLD,
        EG_RELEASE
    }eg_state_t;

    typedef enum{
        EG_RETRIG_ZERO,
        EG_RETRIG_FORCE_DUMP,
        EG_RETRIG_KEEP
    }eg_retrig_t;

    class envelope_generator{
        private:
            eg_state_t eg_state_;
            op_param_t* param_;
            control_value_t* control_;
            std::uint16_t velocity_;
            std::uint8_t note_;
            std::uint16_t amp_;
            std::uint16_t start_amp_;
            std::uint16_t eg_counter_;
            std::uint16_t final_level_;
            std::uint16_t final_attack_rate_;
            std::uint16_t final_decay_rate_;
            std::uint16_t final_sustain_rate_;
            std::uint16_t final_release_rate_;
            void calc_params(void);
            std::uint16_t lookup_rate_scale(std::uint8_t note);
            std::uint16_t lookup_level_scale(std::uint8_t note);
            std::uint16_t calc_final_velocity(std::uint16_t velocity);
            static const std::uint16_t FORCE_DUMP_RATE = 0x1000;
        public:
            envelope_generator();
            void set_param(op_param_t *p);
            void set_control(control_value_t* c);
            inline std::int32_t calc(std::int16_t input){
                std::int32_t t;
                //Apply envelope
                t = input * amp_;
                t = t / 0x8000;
                //Apply total level
                t = t * final_level_;
                return t;
            }

            void update(void);
            void trigger_on(std::uint8_t note,std::uint16_t velocity);
            void trigger_off();
            bool is_wait();
            static eg_retrig_t trigger_option;
    };
}

#endif