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
            synth_controller();
            //Instance of tone generators
            static su_synth::fm_tone tg_[];
            //Tone assign related variable
            static assign_info_t assign_info_[];
            static std::uint8_t lru_[];
            //Ch-Tone parameter table
            static synth_param_t    ch_param_[];
            static save_param_t     ch_save_param_[];
        public:
            //MIDI control related variables
            static control_value_t control_value[];
            static void init(void);
            static void reset(std::uint8_t ch);
            static void assert_tg(std::uint8_t note,std::uint8_t ch,std::uint8_t velocity);
            static void negate_tg(std::uint8_t note,std::uint8_t ch);
            static int assign_tg(std::uint8_t note,std::uint8_t ch);
            static int search_tg(std::uint8_t note,std::uint8_t ch);
            static void set_pitchbend(std::int16_t value,std::uint8_t ch);
            static void set_hold(std::uint8_t value,std::uint8_t ch);  
            static void set_volume(std::uint8_t value,std::uint8_t ch);
            static void set_expression(std::uint8_t value,std::uint8_t ch);  
            static void set_modulation(modulation_source_t source,std::uint8_t value,std::uint8_t ch);
            static void set_panpot(std::uint8_t value,std::uint8_t ch);
            static void set_timbre(prog_change_type_t type,std::uint8_t value,std::uint8_t ch);
            static void set_parameter_number(parameter_type_t type,std::uint8_t value,std::uint8_t ch);
            static void set_parameter_entry(bool is_MSB,std::uint8_t value,std::uint8_t ch);
            static void reset_parameter_number(uint8_t ch);
            static void calc_modulation_total(std::uint8_t ch);
            static std::uint16_t lookup_velocity(std::uint8_t velocity);
            static std::uint32_t lookup_delta(std::uint8_t note,std::int8_t offset);
            static void calc(std::int32_t* buf);
    };
}




#endif