#ifndef _FMTONE_H_
#define _FMTONE_H_

#include <cstdint>
#include "op.h"
#include "lfo.h"
#include "synth_config.h"
#include "synth_param.h"

namespace su_synth{
    class fm_tone{
        private:
            control_value_t* control_;
            synth_param_t* param_;
            std::int32_t feedback_buf_[2];
            std::uint32_t pitch_upper_;
            std::uint32_t pitch_lower_;
            std::uint32_t pitch_center_;
            std::uint32_t current_pitch_;
            std::uint32_t mod_pitch_upper_;
            std::uint32_t mod_pitch_lower_;
            std::uint16_t decimation_counter_;
            std::int32_t (*algo_p_)(fm_tone* inst);
            void select_algo(void);
            lfo lfo_;
        public:
            fm_tone();
            void set_pitchbend(std::int16_t value);            
            void trigger_on(std::uint8_t note,std::uint16_t velocity);
            void trigger_off(void);
            void set_control(control_value_t* c);
            void set_param(synth_param_t* p);
            std::int16_t calc(void);
            static std::int32_t algo_func_0(fm_tone* inst);
            static std::int32_t algo_func_1(fm_tone* inst);
            static std::int32_t algo_func_2(fm_tone* inst);
            static std::int32_t algo_func_3(fm_tone* inst);
            static std::int32_t algo_func_4(fm_tone* inst);
            static std::int32_t algo_func_5(fm_tone* inst);
            static std::int32_t algo_func_6(fm_tone* inst);
            static std::int32_t algo_func_7(fm_tone* inst);
            fm_operator op[NUM_OPERATOR];
    };
}
#endif