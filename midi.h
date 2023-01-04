#ifndef _MIDI_H_
#define _MIDI_H_

#include <cstdint>
#include "synth_config.h"

namespace su_midi{
    const std::uint8_t MSG_STATUS_MASK = 0x80;
    const std::uint8_t MSG_CH_MASK = 0x0f;
    const std::uint8_t MSG_TYPE_MASK = 0xf0;

    const std::uint8_t MSG_NOTE_ON = 0x90;
    const std::uint8_t MSG_NOTE_OFF = 0x80;
    const std::uint8_t MSG_POLY_PRESSURE = 0xA0;
    const std::uint8_t MSG_CC = 0xB0;
    const std::uint8_t MSG_PC = 0xC0;
    const std::uint8_t MSG_CH_PRESSURE = 0xD0;
    const std::uint8_t MSG_PITCH_BEND = 0xE0;


    const std::uint8_t MSG_SYSTEM_MASK = 0xF0;
    const std::uint8_t MSG_SYSEX_START = 0xF0;
    
    //MIDI System Common Message
    const std::uint8_t MSG_QUARTER_FRAME = 0xF1;
    const std::uint8_t MSG_SONG_PTR = 0xF2;
    const std::uint8_t MSG_SONG_SELECT = 0xF3;
    const std::uint8_t MSG_TUNE_REQ = 0xF6;
    const std::uint8_t MSG_SYSEX_END = 0xF7;

    //MIDI System Realtime Message
    const std::uint8_t MSG_SYSTEM_REALTIME_MASK = 0xF8;
    const std::uint8_t MSG_TIMING_CLOCK = 0xF8;
    const std::uint8_t MSG_START = 0xFA;
    const std::uint8_t MSG_CONTINUE = 0xFB;
    const std::uint8_t MSG_STOP = 0xFC;
    const std::uint8_t MSG_ACTIVE_SENSING = 0xFE;
    const std::uint8_t MSG_SYSTEM_RESET = 0xFF;

    //CC Message
    const std::uint8_t CC_BANK_SELECT_MSB = 0;
    const std::uint8_t CC_MODULATION_MSB = 1;
    const std::uint8_t CC_BREATH_CONTROLLER_MSB = 2;
        //3: Reserved
    const std::uint8_t CC_FOOT_CONTROLLER_MSB = 4;
    const std::uint8_t CC_PORTAMENTO_TIME_MSB = 5;
    const std::uint8_t CC_DATA_ENRTY_MSB = 6;
    const std::uint8_t CC_CH_VOLUME_MSB = 7;
    const std::uint8_t CC_BALANCE_MSB = 8;
        //9: Reserved
    const std::uint8_t CC_PAN_MSB = 10;
    const std::uint8_t CC_EXPRESSION_MSB = 11;
    const std::uint8_t CC_FX_CONTROL_1_MSB = 12;
    const std::uint8_t CC_FX_CONTROL_2_MSB = 13;
        //14: Reserved
        //15: Reserved
    const std::uint8_t CC_GENERAL_CONTROLLER_1_MSB = 16;
    const std::uint8_t CC_GENERAL_CONTROLLER_2_MSB = 17;
    const std::uint8_t CC_GENERAL_CONTROLLER_3_MSB = 18;
    const std::uint8_t CC_GENERAL_CONTROLLER_4_MSB = 19;
        //20-31: Reserved
    const std::uint8_t CC_BANK_SELECT_LSB = 32;
    const std::uint8_t CC_MODULATION_LSB = 33;
    const std::uint8_t CC_BREATH_CONTROLLER_LSB = 34;
        //3: Reserved
    const std::uint8_t CC_FOOT_CONTROLLER_LSB = 36;
    const std::uint8_t CC_PORTAMENTO_TIME_LSB = 37;
    const std::uint8_t CC_DATA_ENRTY_LSB = 38;
    const std::uint8_t CC_CH_VOLUME_LSB = 39;
    const std::uint8_t CC_BALANCE_LSB = 40;
        //9: Reserved
    const std::uint8_t CC_PAN_LSB = 42;
    const std::uint8_t CC_EXPRESSION_LSB = 43;
    const std::uint8_t CC_FX_CONTROL_1_LSB = 44;
    const std::uint8_t CC_FX_CONTROL_2_LSB = 45;
        //14: Reserved
        //15: Reserved
    const std::uint8_t CC_GENERAL_CONTROLLER_1_LSB = 48;
    const std::uint8_t CC_GENERAL_CONTROLLER_2_LSB = 49;
    const std::uint8_t CC_GENERAL_CONTROLLER_3_LSB = 50;
    const std::uint8_t CC_GENERAL_CONTROLLER_4_LSB = 51;
        //52-63: Reserved
    const std::uint8_t CC_DUMPER_PEDAL = 64;
    const std::uint8_t CC_PORTAMENTO = 65;
    const std::uint8_t CC_SOSTENUTO_PEDAL = 66;
    const std::uint8_t CC_SOFT_PEDAL = 67;
    const std::uint8_t CC_LEGATO_FOOT_SW = 68;
    const std::uint8_t CC_HOLD_2 = 69;
    const std::uint8_t CC_SOUND_CONTROL_1 = 70;
    const std::uint8_t CC_SOUND_CONTROL_2 = 71;
    const std::uint8_t CC_SOUND_CONTROL_3 = 72;
    const std::uint8_t CC_SOUND_CONTROL_4 = 73;
    const std::uint8_t CC_SOUND_CONTROL_5 = 74; 
    const std::uint8_t CC_SOUND_CONTROL_6 = 75;
    const std::uint8_t CC_SOUND_CONTROL_7 = 76;
    const std::uint8_t CC_SOUND_CONTROL_8 = 77;
    const std::uint8_t CC_SOUND_CONTROL_9 = 78;
    const std::uint8_t CC_SOUND_CONTROL_10 = 79;
    const std::uint8_t CC_GENERAL_CONTROLLER_5 = 80;
    const std::uint8_t CC_GENERAL_CONTROLLER_6 = 81;
    const std::uint8_t CC_GENERAL_CONTROLLER_7 = 82;
    const std::uint8_t CC_GENERAL_CONTROLLER_8 = 83;
    const std::uint8_t CC_PORTAMENT_CONTROL = 84;
        //85-87: Reserved
    const std::uint8_t CC_VELOCITY_PREFIX = 88;
        //89-90: Reserved
    const std::uint8_t CC_FX_1_DEPTH = 91;
    const std::uint8_t CC_FX_2_DEPTH = 92;
    const std::uint8_t CC_FX_3_DEPTH = 93;
    const std::uint8_t CC_FX_4_DEPTH = 94;
    const std::uint8_t CC_FX_5_DEPTH = 95;
    const std::uint8_t CC_DATA_INCREMENT = 96;
    const std::uint8_t CC_DATA_DECREMENT = 97;
    const std::uint8_t CC_NRPN_LSB = 98;
    const std::uint8_t CC_NRPN_MSB = 99;
    const std::uint8_t CC_RPN_LSB = 100;
    const std::uint8_t CC_RPN_MSB = 101;
        //102-119: Reserved
    //Channel Mode Messeage
    const std::uint8_t CC_ALL_SOUND_OFF = 120;
    const std::uint8_t CC_RESET_ALL_CONTROLLER = 121;
    const std::uint8_t CC_LOCAL_CONTROL = 122;
    const std::uint8_t CC_ALL_NOTE_OFF = 123;
    const std::uint8_t CC_OMNI_OFF = 124;
    const std::uint8_t CC_OMNI_ON = 125;
    const std::uint8_t CC_MONO_MODE = 126;
    const std::uint8_t CC_POLY_MODE = 127;

    class midi_receiver_base{
        private:
            typedef enum{
                INIT_STATE,
                WAIT_2ND_ARG,
            }parse_state;
            parse_state state;
            std::uint8_t status_byte;
            std::uint8_t first_arg;
            std::uint8_t recieve_ch;
        protected:
            //Handler for Channel Message
            virtual void note_on_handler(std::uint8_t note_num,std::uint8_t velocity,std::uint8_t ch){
                return;
            }
            virtual void note_off_handler(std::uint8_t note_num,std::uint8_t velocity,std::uint8_t ch){
                return;
            }
            virtual void poly_pressure_handler(std::uint8_t note_num,std::uint8_t value,std::uint8_t ch){
                return;
            }
            virtual void cc_handler(std::uint8_t control_num,std::uint8_t value,std::uint8_t ch){
                return;
            }
            virtual void pc_handler(std::uint8_t prog_num,std::uint8_t ch){
                return;
            }
            virtual void ch_pressure_handler(std::uint8_t value,std::uint8_t ch){
                return;
            }
            virtual void pitchbend_handler(std::int16_t value,std::uint8_t ch){
                return;
            }
            //Handler for System Exclusive Message
            virtual void start_of_exclusive_handler(void){
                return;
            }
            virtual void data_of_exclusive_handler(std::uint8_t data){
                return;
            }
            virtual void end_of_exclusive_handler(void){
                return;
            }
            //Handler for System Common Message
            virtual void quarter_frame_handler(std::uint8_t frame_data){
                return;
            }
            virtual void song_pointer_handler(std::uint16_t song_position){
                return;
            }
            virtual void song_select_handler(std::uint8_t song_num){
                return;
            }
            virtual void tune_request_handler(void){
                return;
            }
            virtual void timing_clock_handler(void){
                return;
            }
            virtual void start_handler(void){
                return;
            }
            virtual void continue_handler(void){
                return;
            }
            virtual void stop_handler(void){
                return;
            }
            virtual void active_sensing_handler(void){
                return;
            }
            virtual void system_reset_handler(void){
                return;
            }
        public:
            midi_receiver_base();
            void parse_byte(std::uint8_t dat);
    };
}
#endif