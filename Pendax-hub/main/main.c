#include <stdio.h>
#include "includes.h"
#include "wifi_code.h"
#include "TCP.h"


void device_command(void *pvParameters)
{
    int socket;


    while (1)
    {
        socket = socket_create(TCP_SOCKET);
        if (socket < 0)
        {
            ESP_LOGE("device_command", "Error occurred during socket creation");
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            continue;
        }
        struct sockaddr_in server_address;
        setup_address(&server_address, device_1_ip, DEVICE_PORT);    //PORT 1986
        socket_bind(socket, &server_address, device_1_ip);

        int err = connect(socket, (struct sockaddr *)&server_address, sizeof(server_address));
        if (err < 0)
        {
            ESP_LOGE("device_command", "Error occurred during connection to device 1");
            close(socket);
        }

        while(1)
        {
            ESP_LOGI("device_command", "Connected to device 1");
            char *message = "TOF";
            send(socket, message, strlen(message), 0);
            ESP_LOGI("device_command", "Message sent to device 1");
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }   
}

void app_main(void)
{
    esp_log_level_set("wifi", ESP_LOG_ERROR);
        wifi_init_sta();

        xTaskCreate(&device_command, "Device_1", 4096, NULL, 5, NULL);

        
     
}