#ifndef _TIMBRE_MANAGER_H_
#define _TIMBRE_MANAGER_H_

#include<cstdint>

#include "synth_param.h"
namespace su_synth::fm{
    
    //General upper bound value of NRPNs
    const std::uint8_t NRPN_GENERAL_MAX     = 99;

    //General NRPNs (compatible with RPNs)
    const std::uint8_t NRPN_PITCHBEND_SENS  = 0x00;
    const std::uint8_t NRPN_NOTE_OFFSET     = 0x02;

    //Auxiliary values of NRPNs for general settings
    const std::uint8_t NRPN_PITCHBEND_SENS_MAX  = 12;
    const std::int8_t NRPN_NOTE_OFFSET_MIN  = -12;
    const std::int8_t NRPN_NOTE_OFFSET_MAX  = 12;

    //LFO NRPNs
    const std::uint8_t NRPN_LFO_AMP_DEPTH       = 0x10;
    const std::uint8_t NRPN_LFO_PITCH_DEPTH     = 0x11;
    const std::uint8_t NRPN_LFO_WHEEL_AMP       = 0x12;
    const std::uint8_t NRPN_LFO_WHEEL_PITCH     = 0x13;
    const std::uint8_t NRPN_LFO_BREATH_AMP      = 0x14;
    const std::uint8_t NRPN_LFO_BREATH_PITCH    = 0x15;
    const std::uint8_t NRPN_LFO_FOOT_AMP        = 0x16;
    const std::uint8_t NRPN_LFO_FOOT_PITCH      = 0x17;
    const std::uint8_t NRPN_LFO_SPEED           = 0x18;
    const std::uint8_t NRPN_LFO_WAVEFORM        = 0x19;
    const std::uint8_t NRPN_LFO_DELAY           = 0x1a;

    //Boundary value of NRPN_LFO_WAVEFORM
    const std::uint8_t NRPN_LFO_WAVEFORM_MAX    = 3;

    //NRPNs for FM Tone generator general settings
    const std::uint8_t NRPN_FM_ALGO             = 0x20;
    const std::uint8_t NRPN_FM_FEEDBACK         = 0x21;

    //Boundary value of NRPN_FM_ALGO
    const std::uint8_t NRPN_FM_ALGO_MAX         = 7;

    //NRPNs for FM Operators settings
    const std::uint8_t NRPN_ATTACK_RATE         = 0x40;
    const std::uint8_t NRPN_DECAY_RATE          = 0x41;
    const std::uint8_t NRPN_SUSTAIN_LEVEL       = 0x42;
    const std::uint8_t NRPN_SUSTAIN_RATE        = 0x43;
    const std::uint8_t NRPN_RELEASE_RATE        = 0x44;
    const std::uint8_t NRPN_TOTAL_LEVEL         = 0x45;
    const std::uint8_t NRPN_VELOCITY_SENS       = 0x46;
    const std::uint8_t NRPN_KEY_RATE            = 0x47;
    const std::uint8_t NRPN_KEY_LEVEL           = 0x48;
    const std::uint8_t NRPN_MUL_INT             = 0x49;
    const std::uint8_t NRPN_MUL_FRAC            = 0x4a;
    const std::uint8_t NRPN_DETUNE              = 0x4b;
    const std::uint8_t NRPN_WAVEFORM            = 0x4c;
    const std::uint8_t NRPN_LFO_AMP_SENS        = 0x4d;
    const std::uint8_t NRPN_LFO_PITCH_SENS      = 0x4e;

    //Auxiliary values of NRPNs for FM Operators
    const std::uint8_t NRPN_FM_SETTING_MASK     = 0x40;
    const std::uint8_t NRPN_FM_OP_NUM_MASK      = 0x30;
    const std::uint8_t NRPN_FM_OP_NUM_SHIFT     = 4;
    const std::uint8_t NRPN_FM_OP_PARAM_MASK    = 0x4f;
    const std::uint8_t NRPN_VELOCITY_SENS_MAX   = 7;
    const std::uint8_t NRPN_MUL_INT_MAX         = 31;
    const std::int8_t  NRPN_DETUNE_MAX          = 7;
    const std::int8_t  NRPN_DETUNE_MIN          = -7;
    const std::uint8_t NRPN_WAVEFORM_MAX        = 7;

    const int save_param_offset_to_nrpn[SAVE_PARAM_NUM]={
        -1,0,2,16,17,18,19,20,
        21,22,23,24,25,26,32,33,
        64,65,66,67,68,69,70,71,
        72,73,74,75,76,77,78,80,
        81,82,83,84,85,86,87,88,
        89,90,91,92,93,94,96,97,
        98,99,100,101,102,103,104,105,
        106,107,108,109,110,112,113,114,
        115,116,117,118,119,120,121,122,
        123,124,125,126,
    };

    const int nrpn_to_save_param_offset[128]={
        //Common param
        16,-1,17,-1,-1,-1,-1,-1,//7
        -1,-1,-1,-1,-1,-1,-1,-1,//15
        //LFO param
        18,19,20,21,22,23,24,25,//23
        26,27,28,-1,-1,-1,-1,-1,//31
        //FM param
        29,30,-1,-1,-1,-1,-1,-1,//47
        -1,-1,-1,-1,-1,-1,-1,-1,//63
        //OP1 param
        31,32,33,34,35,36,37,38,//71
        39,40,41,42,43,44,45,-1,//79
        //OP2 param
        46,47,48,49,50,51,52,53,//87
        54,55,56,57,58,59,60,-1,//95
        //OP3 param
        61,62,63,64,65,66,67,68,//103
        69,70,71,72,73,74,75,-1,//111
        //OP4 param
        76,77,78,79,80,81,82,83,//119
        84,85,86,87,88,89,90,-1 //127
    };

    class timbre_manager{
        private:
            save_param_t* timbre_memory_;
        public:
            timbre_manager();
            ~timbre_manager();
            void get_timbre(std::uint16_t num,save_param_t* dst);
            void parse_timbre(save_param_t* src,synth_param_t* dst);
            void modify_timbre(save_param_t *dst,std::uint16_t num,std::uint8_t value);
            void export_timbre(std::uint16_t num,save_param_t *dst);
            void import_timbre(std::uint16_t num,save_param_t *src);
            static void parse_RPN(synth_param_t* target,std::uint16_t num,std::uint8_t value);
            static void parse_NRPN(synth_param_t* target,std::uint16_t num,std::uint8_t value);
            //Debug function
            static void tone_dump(synth_param_t *param);
            static void save_tone_dump(save_param_t* param);

    };
}
#endif
