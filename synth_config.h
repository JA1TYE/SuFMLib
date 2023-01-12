#ifndef _SYNTH_CONFIG_H_
#define _SYNTH_CONFIG_H_

//If you want to use pre-calculated delta table,
//Please define USE_STATIC_DELTA_TABLE
//Otherwise, this library will use the delta table calculated in ctor of synth_controller
//#define USE_STATIC_DELTA_TABLE

#define SYNTH_FSAMPLE 47999.992f
#define SYNTH_EG_FREQ 1000
#define NUM_OPERATOR 4 
#define MAX_TONES 6
#define MAX_CHANNELS 16
#define MAX_TIMBRE_PROGRAMS 256

#endif