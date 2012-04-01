#ifndef ih_net_server_socket_h
#define ih_net_server_socket_h

#include "ih/core/standard.h"

int ih_net_server_socket_accept(int serversocket,
    struct sockaddr_in *client_address, socklen_t *client_address_size);

int ih_net_server_socket_create(unsigned short port);

void ih_net_server_socket_destroy(int serversocket);

#endif
