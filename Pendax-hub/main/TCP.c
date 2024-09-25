#include "TCP.h"


int socket_create(int socket_type){
    if(socket_type != UDP_SOCKET && socket_type != TCP_SOCKET){
        ESP_LOGE("socket_create", "Invalid socket type");
        return -1;
    }
    int sock = socket(AF_INET, socket_type == UDP_SOCKET ? SOCK_DGRAM : SOCK_STREAM, 0);
    if(sock < 0){
        ESP_LOGE("socket_create", "Failed to create socket");
        return -1;
    }

    ESP_LOGI("socket_create", "Socket created: %d", sock);
    return sock;
}

int setup_address(struct sockaddr_in *server_address, const char *ip, int port){
   memset(server_address, 0, sizeof(*server_address));
    server_address->sin_family = AF_INET;
    server_address->sin_port = htons(port);
   // inet_ntoa(server_address->sin_addr, addr.str, sizeof(addr.str) -1);

    if (ip == NULL || inet_pton(AF_INET, ip, &server_address->sin_addr) <= 0){
        if(ip != NULL){
            ESP_LOGE("setup_address", "Invalid address/ Address not supported: %s", ip);
            return -1;
        } 
        server_address->sin_addr.s_addr = htonl(INADDR_ANY);
        return 0;
    } 
    return 0;
}

void socket_bind(int socket, struct sockaddr_in *server_address, const char *device_ip){
    if(bind(socket, (struct sockaddr *)server_address, sizeof(*server_address)) < 0){
        ESP_LOGE("socket_bind", "Failed to bind socket");
        close(socket);      
    }
}
