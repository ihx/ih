#ifndef ih_net_client_socket_h
#define ih_net_client_socket_h

int ih_net_client_socket_create(char *server_ip_address,
    unsigned short server_port);

void ih_net_client_socket_destroy(int clientsocket);

#endif
