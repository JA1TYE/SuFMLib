#ifndef _SYNTH_PARAM_H_
#define _SYNTH_PARAM_H_
#include "synth_config.h"
#include <cstdint>
#include <cstddef>
#include <cmath>
namespace su_synth{

    typedef enum{
        ALGO_0 = 0,
        ALGO_1 = 1,
        ALGO_2 = 2,
        ALGO_3 = 3,
        ALGO_4 = 4,
        ALGO_5 = 5,
        ALGO_6 = 6,
        ALGO_7 = 7
    }tone_algo_t;

    typedef enum{
        LFO_TRI = 0,
        LFO_SQR = 1,
        LFO_SAW = 2,
        LFO_SH = 3
    }lfo_waveform_t;

    typedef enum{
        WAVE_SIN = 0,
        WAVE_HALF_SIN = 1,
        WAVE_RECT_SIN = 2,
        WAVE_DOUBLE_SIN = 3,
        WAVE_DOUBLE_RECT_SIN = 4,
        WAVE_CHOP_SIN = 5,
        WAVE_SAW = 6,
        WAVE_SQR = 7
    }waveform_t;

    const std::uint16_t RPN_NRPN_INVALID = 0xffff;
    const std::uint16_t RPN_NRPN_INVALID_MASK = 0xc000;
    const std::uint16_t RPN_NRPN_MSB_INVALID_MASK = 0x8000;
    const std::uint16_t RPN_NRPN_LSB_INVALID_MASK = 0x4000;

    typedef struct{
        std::uint16_t attack_rate;
        std::uint16_t decay_rate;
        std::uint16_t sustain_level;
        std::uint16_t sustain_rate;
        std::uint16_t release_rate;
        std::uint16_t total_level;
        std::uint8_t velocity_sensitivity;
        std::uint8_t  key_rate_scale;
        std::uint16_t  key_level_scale;
        std::uint16_t mul;
        std::int8_t   detune;
        waveform_t waveform;
        std::uint16_t lfo_pitch_sensitivity;
        std::uint16_t lfo_amp_sensitivity;
    }op_param_t;

    typedef struct{
        std::uint16_t amp_modulation_depth;
        std::uint16_t pitch_modulation_depth;
        std::uint16_t wheel_amount_amp;
        std::uint16_t wheel_amount_pitch;
        std::uint16_t breath_amount_amp;
        std::uint16_t breath_amount_pitch;
        std::uint16_t foot_amount_amp;
        std::uint16_t foot_amount_pitch;
        std::uint16_t speed;
        lfo_waveform_t waveform;
        std::uint16_t delay;  
    }lfo_param_t;

    typedef struct{
        //TG commom parameters
        std::int8_t note_offset;
        std::uint8_t pitchbend_sensitivity;
        tone_algo_t fm_algorithm;
        std::uint16_t feedback_amount;
        lfo_param_t lfo_param;
        //OP individal parameters
        op_param_t op_params[NUM_OPERATOR];
        char program_name[17];
    }synth_param_t;

    typedef struct{
        std::int16_t pitchbend;
        std::uint16_t modulation_wheel;
        std::uint16_t breath;
        std::uint16_t foot;
        std::uint16_t expression;
        std::uint16_t volume;
        bool          hold;
        std::uint16_t panning_left;
        std::uint16_t panning_right;
        std::uint16_t pitch_modulation_total;
        std::uint16_t amp_modulation_total;
        std::uint16_t RPN_value;
        std::uint16_t NRPN_value;
        bool          is_NRPN;
        std::uint16_t timbre_number;
    }control_value_t;

    const int SAVE_PARAM_NUM = 76;
    const size_t       BYTES_PER_SAVE_PARAM = 91;
    const int          SAVE_OP_PARAM_NUM = 15;
    const size_t       BYTES_OF_PROGRAM_NAME = 16;

    typedef std::uint8_t save_param_t[BYTES_PER_SAVE_PARAM];

    constexpr std::uint8_t count_bit_width(std::uint32_t in){
        if(in == 0)return 1;
        std::uint8_t width = 0;
        while(in != 0){
            width++;
            in = in >> 1;
        }
        return width;
    }

    constexpr std::uint32_t calc_out_scale(std::uint32_t in){
        if(in == 0) return 0;
        std::uint8_t shift_amount = count_bit_width(in - 1);

        std::uint32_t ret = 0;
        if(shift_amount < 32){
            ret = 1 << (16 - shift_amount);
        }
        
        return ret;
    }

    const std::uint32_t DECIMATION_RATE = (int)((double)SYNTH_FSAMPLE / (double)SYNTH_EG_FREQ + 0.5);
#ifndef STATIC_GAIN
    constexpr std::uint32_t OUT_SCALE = calc_out_scale(MAX_TONES);//TODO replace with value that is calculated from MAX_TONES
#else
    constexpr std::uint32_t OUT_SCALE = STATIC_GAIN;
#endif
}
#endif