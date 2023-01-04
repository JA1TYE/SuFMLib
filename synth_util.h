#ifndef _SYNTH_UTIL_H_
#define _SYNTH_UTIL_H_

#include <cstdint>

namespace su_synth{
    class util{
        private:
            util();
        public:
            static std::uint16_t saturate(std::uint32_t in,std::uint16_t threshold); 
            static std::uint16_t exp_minus_2(std::uint16_t in);
            static std::uint16_t eg_exp_minus(std::uint16_t in);
    };
}

#endif
 