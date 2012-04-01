#ifndef ih_net_test_message_h
#define ih_net_test_message_h

#include "ih/net/ping.h"

#define IH_NET_TEST_MESSAGE_TYPE_COUNT 3
enum ih_net_test_message_t {
  IH_NET_TEST_MESSAGE_UNKNOWN = 0,
  IH_NET_TEST_MESSAGE_PING = 1,
  IH_NET_TEST_MESSAGE_PONG = 2
};
typedef enum ih_net_test_message_t ih_net_test_message_t;

ih_core_message_t *ih_net_test_message_create(int client_socket,
    unsigned long message_type);

#endif
