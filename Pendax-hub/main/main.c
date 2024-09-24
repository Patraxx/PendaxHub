#include <stdio.h>
#include "includes.h"
#include "wifi_code.h"
#include "TCP.h"


void device_command(void *pvParameters)
{
    while (1)
    {
        int socket = socket_create(TCP_SOCKET);
        struct sockaddr_in server_address;
        setup_address(&server_address, device_1_ip, DEVICE_PORT);    //PORT 1986
        socket_bind(socket, &server_address, device_1_ip);

        int err = connect(socket, (struct sockaddr *)&server_address, sizeof(server_address));
        if (err < 0)
        {
            ESP_LOGE("device_command", "Error occurred during connection to device 1");
            close(socket);
        }
        else
        {
            ESP_LOGI("device_command", "Connected to device 1");
            char *message = "TOF";
            send(socket, message, strlen(message), 0);
            ESP_LOGI("device_command", "Message sent to device 1");
            close(socket);
        }
    }   
}

void app_main(void)
{
    esp_log_level_set("wifi", ESP_LOG_ERROR);
        wifi_init_sta();

        xTaskCreate(&device_command, "Device_1", 4096, NULL, 5, NULL);

        
     
}