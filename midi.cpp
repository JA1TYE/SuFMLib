#include <cstdint>
#include "synth_config.h"
#include "midi.h"

namespace su_midi{
    midi_receiver_base::midi_receiver_base(){
        state = INIT_STATE;
        status_byte = 0x00;
        first_arg = 0x00;        
    }
    void midi_receiver_base::parse_byte(std::uint8_t dat){
        if(state == INIT_STATE){
            if((dat & MSG_STATUS_MASK) == MSG_STATUS_MASK){//If it is a status byte
                if((dat & MSG_SYSTEM_REALTIME_MASK) == MSG_SYSTEM_REALTIME_MASK){//And if it's a realtime msg
                    if(dat == MSG_TIMING_CLOCK){
                        timing_clock_handler();
                    }
                    else if(dat == MSG_START){
                        start_handler();
                    }
                    else if(dat == MSG_CONTINUE){
                        continue_handler();
                    }
                    else if(dat == MSG_STOP){
                        stop_handler();
                    }
                    else if(dat == MSG_ACTIVE_SENSING){
                        active_sensing_handler();
                    }
                    else if(dat == MSG_SYSTEM_RESET){
                        system_reset_handler();
                    }
                }
                else{
                    //In case of unintended end of exclusive by recieving another message except realtime message.
                    if(status_byte == MSG_SYSEX_START){
                        end_of_exclusive_handler();
                    }

                    status_byte = dat;//set status byte
                    recieve_ch = dat & MSG_CH_MASK;
                    if((status_byte & MSG_TYPE_MASK) != 0xf0)status_byte &= MSG_TYPE_MASK;
                    
                    if(status_byte == MSG_TUNE_REQ){
                        tune_request_handler();
                    }
                    else if(status_byte == MSG_SYSEX_START){
                        start_of_exclusive_handler();
                    }
                    else if(status_byte == MSG_SYSEX_END){
                        end_of_exclusive_handler();
                    }
                }
            }
            else{//Then it is 1st arg. of msg.
                first_arg = dat;
                if(status_byte == MSG_PC){
                    pc_handler(first_arg,recieve_ch);
                }
                else if(status_byte == MSG_CH_PRESSURE){
                    ch_pressure_handler(first_arg,recieve_ch);
                }
                else if(status_byte == MSG_QUARTER_FRAME){
                    quarter_frame_handler(first_arg);
                }
                else if(status_byte == MSG_SONG_SELECT){
                    song_select_handler(first_arg);
                }
                else if(status_byte == MSG_SYSEX_START){
                    //Data of SYSEX Message
                    data_of_exclusive_handler(first_arg);
                }
                else{//Msg that have 2 args
                    state = WAIT_2ND_ARG;
                }
            }
        }
        else if(state == WAIT_2ND_ARG){
            if(status_byte == MSG_NOTE_OFF){
                note_off_handler(first_arg,dat,recieve_ch);
            }
            else if(status_byte == MSG_NOTE_ON){
                note_on_handler(first_arg,dat,recieve_ch);
            }
            else if(status_byte == MSG_POLY_PRESSURE){
                poly_pressure_handler(first_arg,dat,recieve_ch);
            }
            else if(status_byte == MSG_CC){
                cc_handler(first_arg,dat,recieve_ch);
            }
            else if(status_byte == MSG_PITCH_BEND){
                std::uint16_t tmp;
                tmp = first_arg | (dat << 7);
                pitchbend_handler(tmp - 8192,recieve_ch);
            }
            else if(status_byte == MSG_SONG_PTR){
                std::uint16_t tmp;
                tmp = first_arg | (dat << 7);
                song_pointer_handler(tmp);
            }
            state = INIT_STATE;
        }
    }
}