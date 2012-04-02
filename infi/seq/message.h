#ifndef ih_infi_seq_message_h
#define ih_infi_seq_message_h

#define IH_INFI_SEQ_MESSAGE_TYPE_COUNT 5
enum ih_infi_seq_message_t {
  IH_INFI_SEQ_MESSAGE_UNKNOWN = 0,

  IH_INFI_SEQ_MESSAGE_REQUEST_GET_LAST_N = 1,
  IH_INFI_SEQ_MESSAGE_RESPONSE_GET_LAST_N = 2,

  IH_INFI_SEQ_MESSAGE_REQUEST_GET_SINCE_TIMESTAMP = 3,
  IH_INFI_SEQ_MESSAGE_RESPONSE_GET_SINCE_TIMESTAMP = 4,
};
typedef enum ih_infi_seq_message_t ih_infi_seq_message_t;

ih_core_message_t *ih_infi_seq_message_create(int client_socket,
    unsigned long message_type);

#endif
