#include "osc.h"
#include "table.h"
#include "synth_config.h"
#include "synth_param.h"
#include <cstdlib>
#include <math.h>
#include <stdio.h>

namespace su_synth{
    void oscillator::set_param(op_param_t* p){
        param_ = p;
    }
    oscillator::oscillator(){
        acc_ = 0;
        delta_ = 0;
    }
    std::int16_t oscillator::calc_sample(std::int32_t mod){
        std::uint32_t idx_u;
        std::uint16_t table_idx;
        std::uint32_t table_decimal;
        std::int32_t wave_data[2];
        std::int32_t wave_out = 0;

        //Increment Acc.
        std::uint32_t inc = ((std::uint64_t)delta_ * (param_->mul)) >> 10;
        acc_ +=  inc;

        //Apply detune
        if(param_->detune > 0){
            acc_ += (delta_ >> (16 - param_->detune)); 
        }
        else if(param_->detune <0){
            uint32_t tmp = (delta_ >> (16 + param_->detune));
            if(inc < tmp)tmp = inc;
            acc_ -= tmp;
        }
        //if param_->detune == 0, do nothing

        idx_u = acc_ + ((std::uint32_t)((std::int64_t)mod + 0x40000000) << 5);
        table_idx = idx_u >> 22;
        table_decimal = (idx_u & 0x003fffff) >> 7;
        /*
        Normal sine wave
        /\
          \/
        */
        if(param_->waveform == WAVE_SIN){
            wave_data[0] = sin_table[table_idx];
            wave_data[1] = sin_table[(table_idx + 1)&0x3ff];
            wave_out = (wave_data[0] * (0x8000 - table_decimal)) / 0x8000;
            wave_out += (wave_data[1] * table_decimal) / 0x8000;
        }
        /*
        /\__

        */
        else if(param_->waveform == WAVE_HALF_SIN){
            wave_data[0] = sin_table[table_idx];
            wave_data[1] = sin_table[(table_idx + 1)&0x3ff];
            wave_out = (wave_data[0] * (0x8000 - table_decimal)) / 0x8000;
            wave_out += (wave_data[1] * table_decimal) / 0x8000;
            if(wave_out < 0){
                wave_out = 0;
            }
        }
        /*
        /\/\

        */
        else if(param_->waveform == WAVE_RECT_SIN){
            wave_data[0] = sin_table[table_idx];
            wave_data[1] = sin_table[(table_idx + 1)&0x3ff];
            wave_out = (wave_data[0] * (0x8000 - table_decimal)) / 0x8000;
            wave_out += (wave_data[1] * table_decimal) / 0x8000;
            if(wave_out <0){
                wave_out = -1 * wave_out;
            }
        }
        /*
        /\  ____
          \/
        */
        else if(param_->waveform == WAVE_DOUBLE_SIN){
            std::uint16_t shift_table_idx = (table_idx << 1) & 0x3ff;
            wave_data[0] = sin_table[shift_table_idx];
            wave_data[1] = sin_table[(shift_table_idx + 1)&0x3ff];
            wave_out = (wave_data[0] * (0x8000 - table_decimal)) / 0x8000;
            wave_out += (wave_data[1] * table_decimal) / 0x8000;
            if(table_idx & 0x200)wave_out = 0;
        }
        /*
        /\/\____
          
        */
        else if(param_->waveform == WAVE_DOUBLE_RECT_SIN){
            std::uint16_t shift_table_idx = (table_idx << 1) & 0x3ff;
            wave_data[0] = sin_table[shift_table_idx];
            wave_data[1] = sin_table[(shift_table_idx + 1)&0x3ff];
            wave_out = (wave_data[0] * (0x8000 - table_decimal)) / 0x8000;
            wave_out += (wave_data[1] * table_decimal) / 0x8000;
            if(wave_out < 0)wave_out = -wave_out;
            if(table_idx & 0x200)wave_out = 0;
        }
        /*
        
        */     
        else if(param_->waveform == WAVE_CHOP_SIN){
            table_idx = table_idx & 0xff;
            wave_data[0] = sin_table[table_idx];
            wave_data[1] = sin_table[(table_idx + 1)&0x3ff];
            wave_out = (wave_data[0] * (0x8000 - table_decimal)) / 0x8000;
            wave_out += (wave_data[1] * table_decimal) / 0x8000;
            if(table_idx < 0x100){
                wave_out = wave_out - 32767;
            }
            else if(table_idx < 0x200){
                wave_out = 32767 - wave_out;
            }
            else if(table_idx < 0x300){
                wave_out = wave_out + 1;
            }
            else{
                wave_out = -wave_out - 1;
            }
        }
        /*Normal saw*/
        else if(param_->waveform == WAVE_SAW){
            wave_out = (std::int32_t)(idx_u >> 16)-32768;
        }
        /*Normal square*/
        else if(param_->waveform == WAVE_SQR){
            wave_out = (table_idx & 0x200)?32767:-32768;
        }
        return (std::int16_t)wave_out;
    }
    void oscillator::set_delta(std::uint32_t delta){
        delta_ = delta;
    }
    void oscillator::reset_phase(void){
        acc_ = 0;
    }
    
}