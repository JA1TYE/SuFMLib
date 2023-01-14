#ifndef _TABLE_H_
#define _TABLE_H_

#include<cstdint>

const std::int8_t NOTE_DEFAULT_OFFSET = 24;
#ifndef USE_STATIC_DELTA_TABLE
extern std::uint32_t delta_table[128 + (NOTE_DEFAULT_OFFSET * 2)];
#else
extern const std::uint32_t delta_table[128 + (NOTE_DEFAULT_OFFSET * 2)];
#endif
extern const std::int16_t sin_table[1024];
extern const std::uint16_t att_table[128];
extern const std::uint16_t exp_table[257];
extern const std::uint16_t eg_exp_table[258];
extern const std::uint16_t pan_table[128];
extern const std::uint16_t cc_lin_table[128];
extern const std::uint16_t cc_exp_table[128];
extern const std::uint16_t cc_time_table[128];
extern const std::uint16_t mul_frac_table[128];
extern const std::int8_t NOTE_DEFAULT_OFFSET;

void calc_delta_table(double fsample);
#endif