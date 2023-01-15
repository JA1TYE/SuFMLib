#ifndef _OSC_H_
#define _OSC_H_

#include <cstdint>

#include "synth_param.h"
namespace su_synth::fm{
    class oscillator{
        private:
            std::uint32_t acc_;
            std::uint32_t delta_;
            op_param_t* param_;
        public:
            oscillator();
            void set_param(op_param_t* p);
            std::int16_t calc_sample(std::int32_t mod);
            void set_delta(std::uint32_t delta);
            void reset_phase();
    };
}

#endif
 