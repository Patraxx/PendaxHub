#include <stdio.h>
#include "includes.h"
#include "wifi_code.h"
#include "TCP.h"

#define GPIO_INPUT_IO_0    20

const char *device_1_ip = "192.168.10.101";  
const char *device_2_ip = "192.168.10.102";
const char *device_3_ip =  "192.168.10.103";

#define GPIO_INPUT_PIN_SEL  (1ULL<<GPIO_INPUT_IO_0)

#define DEBOUNCE_DELAY_MS 50 
 





void device_command(void *pvParameters)
{
    int socket;
   
    

    while (1)
    {
        ESP_LOGI("device_command", "Creating socket");
        socket = socket_create(TCP_SOCKET);
        if (socket < 0)
        {
            ESP_LOGE("device_command", "Error occurred during socket creation");
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            continue;
        }
        struct sockaddr_in server_address;
       int error = setup_address(&server_address, device_1_ip, DEVICE_PORT);    //PORT 1986
        if (error < 0)
        {
            ESP_LOGE("device_command", "Error occurred during address setup");
            close(socket);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            continue;
        }
        //server_address.sin_family = AF_INET;
       // server_address.sin_addr.s_addr = inet_addr(device_1_ip);
       // server_address.sin_port = htons(DEVICE_PORT);
        
      
        int err = connect(socket, (struct sockaddr *)&server_address, sizeof(server_address));
        if (err < 0)
        {
            ESP_LOGE("device_command", "Error occurred during connection to device 1");
            close(socket);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            continue;
        }
            char *message = "TOF\n";
            char *message2 = "TON\n";
        int err2 = 0;
        while(1)
        {
           
           
           err2 = send(socket, message, strlen(message), 0);
            if (err2 < 0)
            {
                ESP_LOGE("device_command", "Error occurred during sending message to device 1");
                close(socket);
                break;
            }
            ESP_LOGI("device_command", "Sent %d bytes to device 1", err2);
           // gpio_set_level(GPIO_OUTPUT_IO_0, 0);
            vTaskDelay(10000 / portTICK_PERIOD_MS);
        
        

           
            err2 =  send(socket, message2, strlen(message2), 0);
            if (err2 < 0)
            {
                ESP_LOGE("device_command", "Error occurred during sending message to device 1");
                close(socket);
                break;
            } 
          //  gpio_set_level(GPIO_OUTPUT_IO_0, 1);
            
            ESP_LOGI("device_command", "Sent %d bytes to device 1", err2);
            vTaskDelay(10000 / portTICK_PERIOD_MS);
        }
    }   
}

void button_monitor_task(void *pvParameters)
{
    while (1)
    {
        int button_state = gpio_get_level(GPIO_INPUT_IO_0);
        if (button_state == 1)
        {
            ESP_LOGI("button_monitor_task", "Button pressed");
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{

        gpio_config_t io_conf;
        io_conf.intr_type = GPIO_INTR_DISABLE;  // Disable interrupt
        io_conf.mode = GPIO_MODE_INPUT;         // Set as input mode
        io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;  // Bit mask of the pin
        io_conf.pull_down_en = 1;               // Disable pull-down mode
        io_conf.pull_up_en = 0;                 // Enable pull-up mode
        gpio_config(&io_conf);


  
        // Read the state of the button
        int button_state = gpio_get_level(GPIO_INPUT_IO_0);
    
       
        esp_log_level_set("wifi", ESP_LOG_ERROR);

        wifi_init_sta();
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        xTaskCreate(&device_command, "Device_1", 4096, NULL, 5, NULL);

     
     
}