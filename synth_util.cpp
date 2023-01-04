#include <cstdint>
#include "synth_util.h"
#include "table.h"
namespace su_synth{
    std::uint16_t util::saturate(std::uint32_t in,std::uint16_t threshold){
        return (in >= threshold)?threshold:in;
    }

    std::uint16_t util::exp_minus_2(std::uint16_t in){
        std::uint16_t ret = 0x8000;
        std::uint16_t integer = in >> 11;
        std::uint16_t decimal_idx = (in >> 3) & 0xff;
        std::uint16_t decimal_residue = in & 0x7;
        std::uint16_t decimal = (exp_table[decimal_idx] * (0x8 - decimal_residue))/0x8;
        decimal += (exp_table[decimal_idx+1] * decimal_residue)/0x8;
        return ((std::uint32_t)ret * decimal) >> (15+integer);
    }

    std::uint16_t util::eg_exp_minus(std::uint16_t in){
        std::uint16_t integer = in >> 7;
        std::uint16_t decimal = in & 0x7f;
        std::uint16_t ret = (eg_exp_table[integer] * (0x80 - decimal))/0x80;
        ret += (eg_exp_table[integer+1] * decimal)/0x80;
        return ret;
    }

}