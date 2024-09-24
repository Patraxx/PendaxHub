#include <stdio.h>
#include "includes.h"
#include "wifi_code.h"
#include "TCP.h"


void device_command(void *pvParameters)
{

    int socket = socket_create(TCP_SOCKET);
    
}

void app_main(void)
{
    esp_log_level_set("wifi", ESP_LOG_ERROR);
        wifi_init_sta();

        xTaskCreate(&device_command, "Device_1", 4096, NULL, 5, NULL);

        
     
}