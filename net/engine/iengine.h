#ifndef ih_net_engine_iengine_h
#define ih_net_engine_iengine_h

#include "ih/core/object.h"
#include "ih/net/tools.h"

typedef void *(*ih_net_engine_iengine_create_f)
  (ih_net_server_system_t *server, void *custom_server_context_object);

typedef void (*ih_net_engine_iengine_destroy_f)(void *engine_object);

typedef ih_net_server_system_handle_message_f
(*ih_net_engine_iengine_get_handler_for_message_f)
(void *engine_object, void *message_object);

typedef void (*ih_net_engine_iengine_maintain_f)
(void *engine_thread_context_object);

typedef void (*ih_net_engine_iengine_run_f)
(void *engine_thread_context_object);

typedef void (*ih_net_engine_iengine_start_f)
(void *engine_thread_context_object);

typedef void (*ih_net_engine_iengine_stop_f)
(void *engine_thread_context_object);

struct ih_net_engine_iengine_t {
  ih_net_engine_iengine_create_f create;
  ih_net_engine_iengine_destroy_f destroy;
  ih_net_engine_iengine_get_handler_for_message_f get_handler_for_message;
  ih_net_engine_iengine_maintain_f maintain;
  ih_net_engine_iengine_run_f run;
  ih_net_engine_iengine_start_f start;
  ih_net_engine_iengine_stop_f stop;
};
typedef struct ih_net_engine_iengine_t ih_net_engine_iengine_t;

void ih_net_engine_iengine_init(ih_net_engine_iengine_t *iengine,
    ih_net_engine_iengine_create_f create,
    ih_net_engine_iengine_destroy_f destroy,
    ih_net_engine_iengine_get_handler_for_message_f get_handler_for_message,
    ih_net_engine_iengine_maintain_f maintain, ih_net_engine_iengine_run_f run,
    ih_net_engine_iengine_start_f start, ih_net_engine_iengine_stop_f stop);

#endif
