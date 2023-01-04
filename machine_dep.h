#ifndef _MACHINE_DEP_H_
#define _MACHINE_DEP_H_

/*---Debug Print Utilities---*/
#include "esp_log.h"

#define FM_DEBUG_INFO( tag, format, ... ) ESP_LOGI(tag,format __VA_OPT__(,) __VA_ARGS__)
#define FM_DEBUG_ERROR( tag, format, ... ) ESP_LOGE(tag,format __VA_OPT__(,) __VA_ARGS__)
//Constants
const char fs_base_path[] = "/spiffs"; //Base path of configuration files
const char program_file_path[] = "/spiffs/program.bin"; //Path for program data

#endif