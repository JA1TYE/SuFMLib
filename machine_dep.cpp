//Machine Dependent Constants & Functions
//If you port this library to another platform, please modify this file and "synth_config.h"

#include "esp_spiffs.h"
#include "esp_log.h"
#include "esp_spiffs.h"
#include "timbre_manager.h"

/*---Debug Print Utilities---*/
#define FM_DEBUG_INFO( tag, format, ... ) ESP_LOGI(tag,format __VA_OPT__(,) __VA_ARGS__)
#define FM_DEBUG_ERROR( tag, format, ... ) ESP_LOGE(tag,format __VA_OPT__(,) __VA_ARGS__)

namespace su_synth{

/*---Timbre Manager---*/
    //Constants
    const char fs_base_path = "/spiffs"; //Base path of configuration files
    const char program_file_path = "/spiffs/program.bin"; //Path for program data

    //Initialize filesystem
    void timbre_manager::fs_init(void){
        esp_vfs_spiffs_conf_t fs_config;
        fs_config.base_path = fs_base_path,
        fs_config.partition_label = NULL;
        fs_config.max_files = 5;
        fs_config.format_if_mount_failed = false;

        esp_err_t ret = esp_vfs_spiffs_register(&fs_config);

        if (ret != ESP_OK) {
            if (ret == ESP_FAIL) {
                FM_DEBUG_ERROR(TAG, "Failed to mount or format filesystem");
            } else if (ret == ESP_ERR_NOT_FOUND) {
                FM_DEBUG_ERROR(TAG, "Failed to find SPIFFS partition");
            } else {
                FM_DEBUG_ERROR(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
            }
            return;
        }
        
        size_t total = 0, used = 0;
        ret = esp_spiffs_info(NULL, &total, &used);
        if (ret != ESP_OK) {
            FM_DEBUG_ERROR(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
        } else {
            FM_DEBUG_INFO(TAG, "Partition size: total: %d, used: %d", total, used);
        }
    }

    //Deinitialize filesystem
    void timbre_manager::de_init(){
        if(timbre_memory_ != NULL){
            free(timbre_memory_);
        }
        esp_vfs_spiffs_unregister(NULL);
    }
