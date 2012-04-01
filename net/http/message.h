#ifndef ih_net_http_message_h
#define ih_net_http_message_h

#include "ih/case/set.h"
#include "ih/core/content.h"
#include "ih/core/engine.h"
#include "ih/core/nameobject.h"
#include "ih/core/object.h"
#include "ih/core/uuid.h"
#include "ih/net/http/version.h"

#define IH_NET_HTTP_MESSAGE_NO_HEADERS NULL
#define IH_NET_HTTP_MESSAGE_NO_RESOURCE_PATH NULL

enum ih_net_http_method_t {
  IH_NET_HTTP_METHOD_UNKNOWN,
  IH_NET_HTTP_METHOD_GET,
  IH_NET_HTTP_METHOD_HEAD,
  IH_NET_HTTP_METHOD_POST,
};
typedef enum ih_net_http_method_t ih_net_http_method_t;

enum ih_net_http_status_t {
  IH_NET_HTTP_STATUS_UNKNOWN,
  IH_NET_HTTP_STATUS_OK,
  IH_NET_HTTP_STATUS_NOT_FOUND,
};
typedef enum ih_net_http_status_t ih_net_http_status_t;

struct ih_net_http_message_t;
typedef struct ih_net_http_message_t ih_net_http_message_t;

ih_net_http_message_t *ih_net_http_message_create(int client_socket,
    ih_net_http_method_t http_method, ih_net_http_status_t http_status,
    char *resource_path, ih_net_http_version_t http_version,
    ih_case_set_t *http_headers);

void ih_net_http_message_destroy(void *http_message_object);

char *ih_net_http_message_get_body(ih_net_http_message_t *http_message);

unsigned long ih_net_http_message_get_body_size
(ih_net_http_message_t *http_message);

int ih_net_http_message_get_client_socket(void *http_message_object);

ih_core_engine_id_t ih_net_http_message_get_engine_id(void *message_object);

ih_core_nameobject_t *ih_net_http_message_get_http_header
(ih_net_http_message_t *http_message, char *header_name);

ih_case_set_t *ih_net_http_message_get_http_headers
(ih_net_http_message_t *http_message);

ih_net_http_method_t ih_net_http_message_get_http_method
(ih_net_http_message_t *http_message);

ih_net_http_status_t ih_net_http_message_get_http_status
(ih_net_http_message_t *http_message);

ih_net_http_version_t ih_net_http_message_get_http_version
(ih_net_http_message_t *http_message);

char *ih_net_http_message_get_resource_name
(ih_net_http_message_t *http_message);

char *ih_net_http_message_get_uri_parameter
(ih_net_http_message_t *http_message, char *parameter_name);

double ih_net_http_message_get_uri_parameter_as_double
(ih_net_http_message_t *http_message, char *parameter_name);

ih_core_bool_t ih_net_http_message_get_uri_parameter_as_unsigned_long
(ih_net_http_message_t *http_message, char *parameter_name,
    unsigned long *value);

ih_core_uuid_t *ih_net_http_message_get_uri_parameter_as_uuid
(ih_net_http_message_t *http_message, char *parameter_name);

ih_case_set_t *ih_net_http_message_get_uri_parameter_as_uuid_set
(ih_net_http_message_t *http_message, char *parameter_name);

ih_case_set_t *ih_net_http_message_get_uri_parameters
(ih_net_http_message_t *http_message);

char *ih_net_http_message_get_resource_path
(ih_net_http_message_t *http_message);

unsigned long ih_net_http_message_get_type(void *message_object);

ih_core_bool_t ih_net_http_message_set_body
(ih_net_http_message_t *http_message, ih_core_content_t content_type,
    char *body, unsigned long body_size);

ih_core_bool_t ih_net_http_message_set_http_header
(ih_net_http_message_t *http_message, char *header_name, char *header_value);

#endif
