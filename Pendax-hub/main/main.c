#include <stdio.h>
#include "includes.h"
#include "wifi_code.h"
void app_main(void)
{
    esp_log_level_set("wifi", ESP_LOG_ERROR);
        wifi_init_sta();
     
}