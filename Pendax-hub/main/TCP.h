#ifndef TCP_H
#define TCP_H

#include "includes.h"

int socket_create(int socket_type);
void setup_address(struct sockaddr_in *server_address, const char *ip, int port);
void socket_bind(int socket, struct sockaddr_in *server_address);
void socket_broadcast(int socket);

#endif