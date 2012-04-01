#ifndef ih_net_engine_h
#define ih_net_engine_h

#define IH_CORE_ENGINE_TYPE_COUNT 8
enum ih_core_engine_id_t {
  IH_CORE_ENGINE_UNKNOWN = 0,
  IH_CORE_ENGINE_TEST = 1,
  IH_CORE_ENGINE_PING = 2,
  IH_CORE_ENGINE_SHELL = 3,
  IH_CORE_ENGINE_HTTP = 4,
  IH_CORE_ENGINE_SEQ = 5,
  IH_CORE_ENGINE_LIB = 6,
  IH_CORE_ENGINE_CLASS = 7,
  IH_CORE_ENGINE_MAX = 31,
};
typedef enum ih_core_engine_id_t ih_core_engine_id_t;

char *ih_core_engine_get_name(unsigned long engine_id);

#endif
