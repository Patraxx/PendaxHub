#ifndef TCP_H
#define TCP_H

#include "includes.h"

#define UDP_SOCKET 0
#define TCP_SOCKET 1
#define DEVICE_PORT 1986 //specifikt för dessa skärmar

const char *device_1_ip = "192.168.10.101";  
const char *device_2_ip = "192.168.10.102";
const char *device_3_ip =  "192.168.10l.103";


int socket_create(int socket_type);
void setup_address(struct sockaddr_in *server_address, const char *device_ip, int port);

void socket_bind(int socket, struct sockaddr_in *server_address, const char *device_ip);

void socket_broadcast(int socket); //ej färdig


#endif