#include<cstdint>
#include <cstdio>

#include "synth_config.h"
#include "synth_param.h"
#include "synth_ctrl.h"
#include "timbre_manager.h"
#include "fmtone.h"
#include "table.h"

namespace su_synth::fm{
    const std::uint8_t ASSIGN_INVALID = 0xff;
    std::uint32_t synth_controller::decimation_rate = 48;
    double synth_controller::sampling_freq = 48000;

    synth_controller::synth_controller(timbre_manager *tm){
        tm_ = tm;
        printf("DECIMATION_RATE = %lu,OUT_SCALE = 0x%lx\n",decimation_rate,OUT_SCALE);
        for(int i = 0;i < MAX_CHANNELS;i++){
            tm_->get_timbre(0,&ch_save_param_[i]);
            tm_->parse_timbre(&ch_save_param_[i],&ch_param_[i]);
            set_expression(127,i);
            set_volume(127,i);
            set_panpot(64,i);
            control_value[i].pitch_modulation_total = 0;
            control_value[i].amp_modulation_total = 0;
            control_value[i].modulation_wheel = 0;
            control_value[i].breath = 0;
            control_value[i].foot = 0;
        }

        for(int i = 0;i < MAX_TONES;i++){
            assign_info_[i].note = ASSIGN_INVALID;
            assign_info_[i].ch = 0;
            lru_[i] = 0;
            tg_[i].set_param(&ch_param_[0]);
            tg_[i].set_control(&control_value[0]);
        }
    }

    //Calculate DDS delta value
    void synth_controller::prepare_delta_table(double fsample){
#ifndef USE_STATIC_DELTA_TABLE
        std::int32_t lowest_note_num = -NOTE_DEFAULT_OFFSET;
        std::int32_t highest_note_num = 127 + NOTE_DEFAULT_OFFSET;
        const std::uint64_t OVERFLOW_VALUE = 0x100000000ULL;
        double freq;
        for(int i = lowest_note_num,idx = 0;i <= highest_note_num;i++,idx++){
            //Frequency is calculated by midi tuning standard
            freq = std::pow(2,(i-69)/12.0) * 440.0;
            //Convert frequency to delta value
            std::uint64_t delta = std::round(freq * OVERFLOW_VALUE / fsample);
            //Boundary check
            if(delta >= 0x100000000ULL){
                delta = 0xFFFFFFFF;
            }
            delta_table[idx] = delta;
        }
 #endif               
        sampling_freq = fsample;
        decimation_rate = (int)((double)fsample / (double)SYNTH_EG_FREQ + 0.5);
    }


    void synth_controller::reset(std::uint8_t ch){
        set_pitchbend(0,ch);
        set_expression(127,ch);
        set_volume(127,ch);
        set_panpot(64,ch);
        set_hold(0,ch);
        set_timbre(PROGRAM_CHANGE,0,ch);
        set_timbre(BANK_MSB,0,ch);
        set_timbre(BANK_LSB,0,ch);
    }

    std::uint16_t synth_controller::lookup_velocity(std::uint8_t velocity){
        return att_table[velocity];
    }

    std::uint32_t synth_controller::lookup_delta(std::uint8_t note,std::int8_t offset){
        std::int16_t idx;
        idx = note+offset+NOTE_DEFAULT_OFFSET;
        if(idx < 0)idx = 0;
        if(idx >= sizeof(delta_table))idx = sizeof(delta_table) - 1;
        return delta_table[note+offset+NOTE_DEFAULT_OFFSET];
    }

    bool is_wait(fm_tone &t){
        for(int i = 0;i < NUM_OPERATOR;i++){
            if(t.op[i].eg.is_wait() == false)return false;
        }
        return true;
    }

    void synth_controller::set_modulation(modulation_source_t source,std::uint8_t value,std::uint8_t ch){
        if(source == MOD_WHEEL)control_value[ch].modulation_wheel = value*256;
        else if(source == MOD_BREATH)control_value[ch].breath = value*256;
        else if(source == MOD_FOOT)control_value[ch].foot = value*256;
        calc_modulation_total(ch);
    }

    void synth_controller::calc_modulation_total(std::uint8_t ch){
        std::uint32_t tmp;
        //for amp
        tmp = (control_value[ch].modulation_wheel * ch_param_[ch].lfo_param.wheel_amount_amp) / 0x8000;
        tmp += (control_value[ch].breath * ch_param_[ch].lfo_param.breath_amount_amp) / 0x8000;
        tmp += (control_value[ch].foot * ch_param_[ch].lfo_param.foot_amount_amp) / 0x8000;
        if(tmp > 0x8000)tmp = 0x8000;
        control_value[ch].amp_modulation_total = tmp;
        //for pitch
        tmp = (control_value[ch].modulation_wheel * ch_param_[ch].lfo_param.wheel_amount_pitch) / 0x8000;
        tmp += (control_value[ch].breath * ch_param_[ch].lfo_param.breath_amount_pitch) / 0x8000;
        tmp += (control_value[ch].foot * ch_param_[ch].lfo_param.foot_amount_pitch) / 0x8000;
        if(tmp > 0x8000)tmp = 0x8000;
        control_value[ch].pitch_modulation_total = tmp;
    }

    //Currently this functon support only program change(bit0-6) and part of bank select LSB(bit7)
    void synth_controller::set_timbre(prog_change_type_t type,std::uint8_t value,std::uint8_t ch){
        std::uint16_t tmp = control_value[ch].timbre_number;
        if(type == PROGRAM_CHANGE){
            tmp = tmp & 0xff80;
            tmp = tmp | value;
        }
        else if(type == BANK_LSB){
            tmp = tmp & 0xc07f;
            tmp = tmp | ((std::uint32_t)value << 7);
        }
        else if(type == BANK_MSB){
            tmp = tmp & 0x3fff;
            tmp = tmp | (((std::uint32_t)value << 14) & 0xc000);
        }
        if(tmp > MAX_TIMBRE_PROGRAMS){
            tmp = tmp % MAX_TIMBRE_PROGRAMS;
        }
        control_value[ch].timbre_number = tmp;

        //Only if PC is coming actual timbre is changed
        if(type == PROGRAM_CHANGE){
            tm_->get_timbre(tmp,&ch_save_param_[ch]);
            tm_->parse_timbre(&ch_save_param_[ch],&ch_param_[ch]);
            for(int i = 0;i < MAX_TONES;i++){
                if(assign_info_[i].ch == ch){
                    tg_[i].set_param(&ch_param_[ch]);
                }
            }
        }
    }

    void synth_controller::set_pitchbend(std::int16_t value,std::uint8_t ch){
        control_value[ch].pitchbend = value;
        for(int i = 0;i < MAX_TONES;i++){
            if(assign_info_[i].ch == ch){
                tg_[i].set_pitchbend(value);
            }
        }
    }

    void synth_controller::set_volume(std::uint8_t value,std::uint8_t ch){
        control_value[ch].volume = att_table[value];
    }

    void synth_controller::set_hold(std::uint8_t value,std::uint8_t ch){
        control_value[ch].hold = (value < 64)?false:true;
    }

    void synth_controller::set_panpot(std::uint8_t value,std::uint8_t ch){
        if(value == 0)value = 1;
        control_value[ch].panning_left = pan_table[value];
        control_value[ch].panning_right = pan_table[128 - value];
    }

    void synth_controller::set_expression(std::uint8_t value,std::uint8_t ch){
        control_value[ch].expression = att_table[value];
    }

    void synth_controller::set_parameter_number(parameter_type_t type,std::uint8_t value,std::uint8_t ch){
        //if bit 15 is 1, it indicates (N)RPN MSB has not been received yet.
        //if bit 14 is 1, it indicates (N)RPN LSB has not been received yet.
        const std::uint16_t MSB_CLEAR_MASK = 0x407f;
        const std::uint16_t LSB_CLEAR_MASK = 0xbf80;
        
        value &= 0x7f;
        if(type == RPN_MSB){
            control_value[ch].RPN_value &= MSB_CLEAR_MASK;
            control_value[ch].RPN_value |= (value << 7);
            control_value[ch].is_NRPN = false;
        }
        if(type == RPN_LSB){
            control_value[ch].RPN_value &= LSB_CLEAR_MASK;
            control_value[ch].RPN_value |= (value);
            control_value[ch].is_NRPN = false;
        }
        if(type == NRPN_MSB){
            control_value[ch].NRPN_value &= MSB_CLEAR_MASK;
            control_value[ch].NRPN_value |= (value << 7);
            control_value[ch].is_NRPN = true;
        }
        if(type == NRPN_LSB){
            control_value[ch].NRPN_value &= LSB_CLEAR_MASK;
            control_value[ch].NRPN_value |= (value);
            control_value[ch].is_NRPN = true;
        }
    }

    void synth_controller::reset_parameter_number(uint8_t ch){
        control_value[ch].NRPN_value = RPN_NRPN_INVALID;
        control_value[ch].RPN_value = RPN_NRPN_INVALID;
    }

    void synth_controller::set_parameter_entry(bool is_MSB,std::uint8_t value,std::uint8_t ch){
        if(control_value[ch].is_NRPN == true){
            //Currently we don't use NRPN LSB
            if(is_MSB == true){
                timbre_manager::parse_NRPN(&ch_param_[ch],control_value[ch].NRPN_value,value);
                tm_->modify_timbre(&ch_save_param_[ch],control_value[ch].NRPN_value,value);
            }
        }
        else{
            //Currently we don't use RPN LSB
            if(is_MSB == true){
                timbre_manager::parse_RPN(&ch_param_[ch],control_value[ch].RPN_value,value);
            }
        }
    }

    int synth_controller::assign_tg(std::uint8_t note,std::uint8_t ch){
        int i;
        //For LRU selection algo.
        int last_idx = 0;
        int last_num = 0;
        int same_tone_idx = -1;
        int available_tone_idx = -1;

        //Update tone status
        for(i = 0;i < MAX_TONES;i++){
            if(is_wait(tg_[i]) == true){
                assign_info_[i].note = ASSIGN_INVALID;
                if(lru_[i] > 0){
                    for(int n = 0;n < MAX_TONES;n++){
                        if(lru_[n] > lru_[i]){
                            lru_[n]--;
                        }
                    }
                    lru_[i] = 0;
                }
            }
        }

        for(i = 0;i < MAX_TONES;i++){
            //Checking the same tone
            if(note == assign_info_[i].note && ch == assign_info_[i].ch){
                same_tone_idx = i;
            }
            //Checking available tone
            if(assign_info_[i].note == ASSIGN_INVALID){
                available_tone_idx = i;
            }
            if(last_num < lru_[i]){
                last_num = lru_[i];
                last_idx = i;
            }
        }
        if(same_tone_idx >= 0)return same_tone_idx;
        if(available_tone_idx >= 0)return available_tone_idx;
        return last_idx;
    }

    int synth_controller::search_tg(std::uint8_t note,std::uint8_t ch){
        int i;
        //Checking the same tone
        for(i = 0;i < MAX_TONES;i++){
            if(note == assign_info_[i].note && ch == assign_info_[i].ch){
                return i;
            }
        }
        return -1;
    }

    void synth_controller::assert_tg(std::uint8_t note,std::uint8_t ch,std::uint8_t velocity){
        int tg_idx = assign_tg(note,ch);
        //printf("%d\n",tg_idx);
        tg_[tg_idx].set_pitchbend(control_value[ch].pitchbend);
        tg_[tg_idx].set_param(&ch_param_[ch]);
        tg_[tg_idx].set_control(&control_value[ch]);
        tg_[tg_idx].trigger_on(note,lookup_velocity(velocity));
        //Update LRU entry
        //If the same tone is already assigned:
        if(note == assign_info_[tg_idx].note && ch == assign_info_[tg_idx].ch){
            int lru_tmp = lru_[tg_idx];
            for(int i = 0;i < MAX_TONES;i++){
                if(i != tg_idx && assign_info_[i].note != ASSIGN_INVALID){
                    if(lru_tmp > lru_[i]){
                        lru_[i]++;
                    }
                }
            }
        }
        //Use wait-state or LRU-selected tone:
        else{
            for(int i = 0;i < MAX_TONES;i++){
                if(i != tg_idx && assign_info_[i].note != ASSIGN_INVALID){
                    lru_[i]++;
                }
            }
        }
        //Set LRU entry
        lru_[tg_idx] = 1;
        assign_info_[tg_idx].note = note;
        assign_info_[tg_idx].ch = ch;

    }
    
    void synth_controller::negate_tg(std::uint8_t note,std::uint8_t ch){
        int tg_idx = search_tg(note,ch);
        if(tg_idx >= 0){
            tg_[tg_idx].trigger_off();
        }
    }
    
    void synth_controller::calc(std::int32_t* buf){
        std::int32_t sum_left = 0;
        std::int32_t sum_right = 0;
        std::int32_t tmp;
        //Process sample calculation
        for(int i = 0;i < MAX_TONES;i++){
            std::uint8_t ch;
            ch = assign_info_[i].ch;
            tmp = tg_[i].calc();
            tmp = tmp * control_value[ch].volume / 0x8000;
            tmp = tmp * control_value[ch].expression / 0x8000;
            sum_left += (tmp * control_value[ch].panning_left) / 0x8000;
            sum_right += (tmp * control_value[ch].panning_right) / 0x8000;
        }
        sum_left = sum_left * OUT_SCALE;//OUT_SCALE is defined in synth_param.h
        sum_right = sum_right * OUT_SCALE;
        buf[0] = sum_left;
        buf[1] = sum_right;
    }
}
