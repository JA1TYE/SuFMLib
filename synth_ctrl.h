#ifndef _SYNTH_CTRL_H_
#define _SYNTH_CTRL_H_

#include<cstdint>
#include "synth_param.h"
#include "fmtone.h"

namespace su_synth{
    typedef struct{
        std::uint8_t note;
        std::uint8_t ch;
    }assign_info_t;
    typedef enum{
        MOD_WHEEL,
        MOD_BREATH,
        MOD_FOOT
    }modulation_source_t;
    typedef enum{
        RPN_MSB,
        RPN_LSB,
        NRPN_MSB,
        NRPN_LSB
    }parameter_type_t;
    typedef enum{
        PROGRAM_CHANGE,
        BANK_LSB,
        BANK_MSB
    }prog_change_type_t;
    class synth_controller{
        private:
            //Instance of tone generators
            su_synth::fm_tone tg_[MAX_TONES];
            //Tone assignment related variable
            assign_info_t assign_info_[MAX_TONES];
            std::uint8_t lru_[MAX_TONES];
            //Ch-Tone parameter table
            synth_param_t    ch_param_[MAX_CHANNELS];
            save_param_t     ch_save_param_[MAX_CHANNELS];

        public:
            synth_controller();
            //Class methods
            static std::uint32_t decimation_rate;
            static double sampling_freq;
            static void prepare_delta_table(double fsample);
            static std::uint32_t lookup_delta(std::uint8_t note,std::int8_t offset);
            //MIDI control related variables
            control_value_t control_value[MAX_CHANNELS];
            void init(void);
            void reset(std::uint8_t ch);
            void assert_tg(std::uint8_t note,std::uint8_t ch,std::uint8_t velocity);
            void negate_tg(std::uint8_t note,std::uint8_t ch);
            int assign_tg(std::uint8_t note,std::uint8_t ch);
            int search_tg(std::uint8_t note,std::uint8_t ch);
            void set_pitchbend(std::int16_t value,std::uint8_t ch);
            void set_hold(std::uint8_t value,std::uint8_t ch);  
            void set_volume(std::uint8_t value,std::uint8_t ch);
            void set_expression(std::uint8_t value,std::uint8_t ch);  
            void set_modulation(modulation_source_t source,std::uint8_t value,std::uint8_t ch);
            void set_panpot(std::uint8_t value,std::uint8_t ch);
            void set_timbre(prog_change_type_t type,std::uint8_t value,std::uint8_t ch);
            void set_parameter_number(parameter_type_t type,std::uint8_t value,std::uint8_t ch);
            void set_parameter_entry(bool is_MSB,std::uint8_t value,std::uint8_t ch);
            void reset_parameter_number(uint8_t ch);
            void calc_modulation_total(std::uint8_t ch);
            std::uint16_t lookup_velocity(std::uint8_t velocity);
            void calc(std::int32_t* buf);
    };
}




#endif