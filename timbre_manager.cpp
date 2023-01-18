#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/stat.h>

#include "synth_param.h"
#include "synth_config.h"
#include "timbre_manager.h"
#include "table.h"

namespace su_synth::fm{

    //Constructor
    timbre_manager::timbre_manager(std::uint16_t num_timbres){
        NUM_TIMBRE_PROGRAMS_ = num_timbres;
        timbre_memory_ = new save_param_t[NUM_TIMBRE_PROGRAMS_];
        if(timbre_memory_ == NULL)printf("err on timbre manager\n");
    }

    //Destructor
    timbre_manager::~timbre_manager(){
        delete[] timbre_memory_;
    }

    //Export timbre parameter from timbre_manager
    //export_timbre is get_timbre with boundary check
    void timbre_manager::export_timbre(std::uint16_t num,save_param_t *dst){
        if(num >= NUM_TIMBRE_PROGRAMS_){
            return;
        }
        get_timbre(num,dst);
    }

    //Import timbre parameter to timbre_manager 
    void timbre_manager::import_timbre(std::uint16_t num,save_param_t *src){
        if(num >= NUM_TIMBRE_PROGRAMS_){
            return;
        }
        memcpy(&(timbre_memory_[num]),src,sizeof(save_param_t));
    }

    void timbre_manager::modify_timbre(save_param_t *dst,std::uint16_t num,std::uint8_t value){
        //Currently we only use NRPN #0-#127
        if(num < (sizeof(nrpn_to_save_param_offset)/sizeof(*nrpn_to_save_param_offset))){
            int ofs = nrpn_to_save_param_offset[num];
            if(ofs > -1){
                (*dst)[ofs] = value;
            }
        }
    }

    void timbre_manager::get_timbre(std::uint16_t num,save_param_t* dst){
        if(num >= NUM_TIMBRE_PROGRAMS_)num = NUM_TIMBRE_PROGRAMS_ - 1;
        memcpy(dst,timbre_memory_[num],sizeof(*timbre_memory_));
    }

    void timbre_manager::parse_timbre(save_param_t* src,synth_param_t* dst){
        //Program Name
        memcpy(&(dst->program_name),(void*)src,BYTES_OF_PROGRAM_NAME);
        dst->program_name[16] = '\0';//Terminate Program name
        //NRPN parameters
        for(int i = 0;i < SAVE_PARAM_NUM - 1;i++){
            parse_NRPN(dst,save_param_offset_to_nrpn[i + 1],(*src)[BYTES_OF_PROGRAM_NAME+i]);
        }
    }

    std::uint16_t timbre_manager::get_timbre_memory_size(void){
        return NUM_TIMBRE_PROGRAMS_;
    }

    /*--- Static member functions ---*/
    void timbre_manager::parse_RPN(synth_param_t* target,std::uint16_t num,std::uint8_t value){
        //General Parameters(as same as NRPN)
        if(num == NRPN_PITCHBEND_SENS){
            if(value > NRPN_PITCHBEND_SENS_MAX){
                value = NRPN_PITCHBEND_SENS_MAX;
            }
            target->pitchbend_sensitivity = value;
        }
        else if(num == NRPN_NOTE_OFFSET){
            std::int8_t tmp = value - 64;
            if(tmp > NRPN_NOTE_OFFSET_MAX){
                tmp = NRPN_NOTE_OFFSET_MAX;
            }
            else if(tmp < NRPN_NOTE_OFFSET_MIN){
                tmp = NRPN_NOTE_OFFSET_MIN;
            }
            target->note_offset = tmp;
        }
    }

    void timbre_manager::parse_NRPN(synth_param_t* target,std::uint16_t num,std::uint8_t value){
        //General Parameters
        if(num == NRPN_PITCHBEND_SENS){
            if(value > NRPN_PITCHBEND_SENS_MAX){
                value = NRPN_PITCHBEND_SENS_MAX;
            }
            target->pitchbend_sensitivity = value;
        }
        else if(num == NRPN_NOTE_OFFSET){
            std::int8_t tmp = value - 64;
            if(tmp > NRPN_NOTE_OFFSET_MAX){
                tmp = NRPN_NOTE_OFFSET_MAX;
            }
            else if(tmp < NRPN_NOTE_OFFSET_MIN){
                tmp = NRPN_NOTE_OFFSET_MIN;
            }
            target->note_offset = tmp;
        }
        //LFO Parameters
        else if(num == NRPN_LFO_AMP_DEPTH){
            target->lfo_param.amp_modulation_depth = cc_exp_table[value];
        }
        else if(num == NRPN_LFO_PITCH_DEPTH){
            target->lfo_param.pitch_modulation_depth = cc_lin_table[value];
        }
        else if(num == NRPN_LFO_WHEEL_AMP){
            target->lfo_param.wheel_amount_amp = cc_exp_table[value];
        }
        else if(num == NRPN_LFO_WHEEL_PITCH){
            target->lfo_param.wheel_amount_pitch = cc_lin_table[value];
        }
        else if(num == NRPN_LFO_BREATH_AMP){
            target->lfo_param.breath_amount_amp = cc_exp_table[value];
        }
        else if(num == NRPN_LFO_BREATH_PITCH){
            target->lfo_param.breath_amount_pitch = cc_lin_table[value];
        }
        else if(num == NRPN_LFO_FOOT_AMP){
            target->lfo_param.foot_amount_amp = cc_exp_table[value];
        }
        else if(num == NRPN_LFO_FOOT_PITCH){
            target->lfo_param.foot_amount_pitch = cc_lin_table[value];
        }
        else if(num == NRPN_LFO_SPEED){
            target->lfo_param.speed = cc_lin_table[value];
        }
        else if(num == NRPN_LFO_WAVEFORM){
            if(value > NRPN_LFO_WAVEFORM_MAX){
                value = NRPN_LFO_WAVEFORM_MAX;
            }
            target->lfo_param.waveform = (lfo_waveform_t)value;
        }
        else if(num == NRPN_LFO_DELAY){
            target->lfo_param.delay = cc_lin_table[value];
        }
        //FM Tone generator general settings
        else if(num == NRPN_FM_ALGO){
            if(value > NRPN_FM_ALGO_MAX){
                value = NRPN_FM_ALGO_MAX;
            }
            target->fm_algorithm = (tone_algo_t)value;
        }
        else if(num == NRPN_FM_FEEDBACK){
            target->feedback_amount = cc_exp_table[value];
        }
        //Operator Parameters
        else if((num & NRPN_FM_SETTING_MASK) != 0){
            std::uint8_t op_num = (num & NRPN_FM_OP_NUM_MASK) >> NRPN_FM_OP_NUM_SHIFT;
            std::uint8_t op_setting_num = num & NRPN_FM_OP_PARAM_MASK;
            
            if(op_setting_num == NRPN_ATTACK_RATE){
                std::uint16_t tmp = cc_time_table[value];
                tmp = tmp + 1;
                if(tmp > 0x8000)tmp = 0x8000;
                target->op_params[op_num].attack_rate = tmp;
            }
            else if(op_setting_num == NRPN_DECAY_RATE){
                std::uint16_t tmp = cc_time_table[value];
                tmp = tmp + 1;
                if(tmp > 0x8000)tmp = 0x8000;
                target->op_params[op_num].decay_rate = tmp;
            }
            else if(op_setting_num == NRPN_SUSTAIN_LEVEL){
                target->op_params[op_num].sustain_level = cc_exp_table[value];
            }
            else if(op_setting_num == NRPN_SUSTAIN_RATE){ 
                target->op_params[op_num].sustain_rate = cc_time_table[value];
            }
            else if(op_setting_num == NRPN_RELEASE_RATE){
                std::uint16_t tmp = cc_time_table[value];
                tmp = tmp + 1;
                if(tmp > 0x8000)tmp = 0x8000;
                target->op_params[op_num].release_rate = tmp;
            }
            else if(op_setting_num == NRPN_TOTAL_LEVEL){
                target->op_params[op_num].total_level = cc_exp_table[value];
            }
            else if(op_setting_num == NRPN_VELOCITY_SENS){
                if(value > NRPN_VELOCITY_SENS_MAX){
                    value = NRPN_VELOCITY_SENS_MAX;
                }
                target->op_params[op_num].velocity_sensitivity = value;
            }
            else if(op_setting_num == NRPN_KEY_RATE){
                std::uint16_t tmp = cc_lin_table[value] >> 7;
                if(value >= NRPN_GENERAL_MAX)tmp = tmp - 1;
                target->op_params[op_num].key_rate_scale = tmp;
            }
            else if(op_setting_num == NRPN_KEY_LEVEL){
                target->op_params[op_num].key_level_scale = cc_lin_table[value];
            }
            else if(op_setting_num == NRPN_MUL_INT){
                std::uint16_t tmp = target->op_params[op_num].mul;
                if(value > NRPN_MUL_INT_MAX){
                    value = NRPN_MUL_INT_MAX;
                }
                tmp &= 0x03ff;
                tmp |= (value << 10);
                target->op_params[op_num].mul = tmp;
            }
            else if(op_setting_num == NRPN_MUL_FRAC){
                std::uint16_t tmp = target->op_params[op_num].mul;
                tmp &= 0xfc00;
                tmp |= mul_frac_table[value];
                target->op_params[op_num].mul = tmp;
            }
            else if(op_setting_num == NRPN_DETUNE){
                std::int8_t tmp = value - 64;
                if(tmp < NRPN_DETUNE_MIN){
                    tmp = NRPN_DETUNE_MIN;
                }
                if(tmp > NRPN_DETUNE_MAX){
                    tmp = NRPN_DETUNE_MAX;
                }
                target->op_params[op_num].detune = tmp;
            }
            else if(op_setting_num == NRPN_WAVEFORM){
                if(value > NRPN_WAVEFORM_MAX){
                    value = NRPN_WAVEFORM_MAX;
                }
                target->op_params[op_num].waveform = (waveform_t)value;
            }
            else if(op_setting_num == NRPN_LFO_AMP_SENS){
                target->op_params[op_num].lfo_amp_sensitivity = cc_exp_table[value];
            }
            else if(op_setting_num == NRPN_LFO_PITCH_SENS){
                target->op_params[op_num].lfo_pitch_sensitivity = cc_lin_table[value];
            }
        }
    }

    void timbre_manager::tone_dump(synth_param_t *param){
        //Program name
        printf("--Name:%s--\n",param->program_name);
        //Common parameter
        printf("--common--\n");
        printf("0x%04x,",param->pitchbend_sensitivity);
        printf("0x%04x,",param->note_offset);
        printf("\n");

        //LFO parameter
        printf("--LFO--\n");
        printf("0x%04x,",param->lfo_param.amp_modulation_depth);
        printf("0x%04x,",param->lfo_param.pitch_modulation_depth);
        printf("0x%04x,",param->lfo_param.wheel_amount_amp);
        printf("0x%04x,",param->lfo_param.wheel_amount_pitch);
        printf("0x%04x,",param->lfo_param.breath_amount_amp);
        printf("0x%04x,",param->lfo_param.breath_amount_pitch);
        printf("0x%04x,",param->lfo_param.foot_amount_amp);
        printf("0x%04x,",param->lfo_param.foot_amount_pitch);
        printf("\n");
        printf("0x%04x,",param->lfo_param.speed);
        printf("0x%04x,",(int)param->lfo_param.waveform);
        printf("0x%04x,",param->lfo_param.delay);
        printf("\n");

        //FM common parameter
        printf("--FM common--\n");
        printf("0x%04x,",(int)param->fm_algorithm);
        printf("0x%04x,",param->feedback_amount);
        printf("\n");
        //FM operator parameter
        for(int i = 0;i < 4;i++){
            printf("--FM OP%d--\n",i);
            printf("0x%04x,",param->op_params[i].attack_rate);
            printf("0x%04x,",param->op_params[i].decay_rate);
            printf("0x%04x,",param->op_params[i].sustain_level);
            printf("0x%04x,",param->op_params[i].sustain_rate);
            printf("0x%04x,",param->op_params[i].release_rate);
            printf("0x%04x,",param->op_params[i].total_level);
            printf("0x%04x,",param->op_params[i].velocity_sensitivity);
            printf("0x%04x,",param->op_params[i].key_rate_scale);
            printf("\n");
            printf("0x%04x,",param->op_params[i].key_level_scale);
            printf("0x%04x,",param->op_params[i].mul);
            printf("0x%04x,",(int)param->op_params[i].waveform);
            printf("0x%04x,",param->op_params[i].lfo_amp_sensitivity);
            printf("0x%04x,",param->op_params[i].lfo_pitch_sensitivity);
            printf("\n");
        }
    }

    void timbre_manager::save_tone_dump(save_param_t* param){
        //Program name
        char buf[17];
        memcpy(buf,*param,16);
        buf[16] = '\0';
        printf("--Name:%s--\n",buf);
        //Common parameter
        printf("--common--\n");
        printf("%d,",(*param)[16]);
        printf("%d,",(*param)[17]);
        printf("\n");

        //LFO parameter
        printf("--LFO--\n");
        for(int i = 0;i < 8;i++){
            printf("%d,",(*param)[18+i]);
        }
        printf("\n");
        for(int i = 0;i < 3;i++){
            printf("%d,",(*param)[26+i]);
        }
        printf("\n");

        //FM common parameter
        printf("--FM common--\n");
        printf("%d,",(*param)[29]);
        printf("%d,",(*param)[30]);
        printf("\n");
        //FM operator parameter
        for(int i = 0;i < 4;i++){
            printf("--FM OP%d--\n",i);
            for(int n = 0;n < 8;n++){
                printf("%d,",(*param)[31+i*SAVE_OP_PARAM_NUM+n]);
            }
            printf("\n");
            for(int n = 0;n < 7;n++){
                printf("%d,",(*param)[39+i*SAVE_OP_PARAM_NUM+n]);
            }
            printf("\n");
        }
    }
}
