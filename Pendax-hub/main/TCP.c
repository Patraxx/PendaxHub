#include "TCP.h"

#define UDP_SOCKET 0
#define TCP_SOCKET 1


void socket_create(int socket_type){
    int socket = socket(AF_INET, socket_type == UDP_SOCKET ? SOCK_DGRAM : SOCK_STREAM, 0);
    if(socket < 0){
        ESP_LOGE("socket_create", "Failed to create socket");
        return -1;
    }
    return socket;
}

void setup_adress(struct sockaddr_in *server_address, const char *ip, int port){
   memset(server_address, 0, sizeof(*server_address));
    server_address->sin_family = AF_INET;
    server_address->sin_port = htons(port);

    if (ip == NULL || inet_pton(AF_INET, ip, &server_address->sin_addr) <= 0){
        if(ip != NULL){
            ESP_LOGE("setup_adress", "Invalid address/ Address not supported: %s", ip);
        } 
        server_address->sin_addr.s_addr = htonl(INADDR_ANY);
    } 
}
