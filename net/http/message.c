#include "ih/case/list.h"
#include "ih/case/set.h"
#include "ih/core/content.h"
#include "ih/core/imessage.h"
#include "ih/core/nameobject.h"
#include "ih/core/string.h"
#include "ih/core/tools.h"
#include "ih/net/http/message.h"
#include "ih/net/http/tools.h"

struct ih_net_http_message_t {
  int client_socket;

  ih_net_http_method_t http_method;
  ih_net_http_status_t http_status;
  char *resource_path;
  ih_net_http_version_t http_version;
  ih_case_set_t *http_headers;
  char *body;
  unsigned long body_size;

  ih_core_content_t content_type;
  char *resource_name;
  ih_case_set_t *uri_parameters;

  ih_core_iobject_t nameobject_iobject;
  ih_core_iobject_t uuid_iobject;
};

static ih_core_bool_t ih_net_http_message_create_uri
(ih_net_http_message_t *http_message);

static void ih_net_http_message_create_rollback
(ih_net_http_message_t *http_message);

/*
  TODO: simplify
*/
ih_net_http_message_t *ih_net_http_message_create(int client_socket,
    ih_net_http_method_t http_method, ih_net_http_status_t http_status,
    char *resource_path, ih_net_http_version_t http_version,
    ih_case_set_t *http_headers)
{
  ih_net_http_message_t *http_message;
  ih_core_bool_t so_far_so_good;

  http_message = malloc(sizeof *http_message);
  if (http_message) {
    http_message->client_socket = client_socket;
    http_message->http_method = http_method;
    http_message->http_status = http_status;
    http_message->http_version = http_version;
    http_message->body = NULL;
    http_message->body_size = 0;
    http_message->resource_name = NULL;
    http_message->uri_parameters = NULL;
    ih_core_uuid_init_iobject(&http_message->uuid_iobject);
    ih_core_nameobject_init_iobject(&http_message->nameobject_iobject);

    if (resource_path) {
      http_message->resource_path = strdup(resource_path);
      if (http_message->resource_path) {
        so_far_so_good = ih_core_bool_true;
      } else {
        ih_core_trace("strdup");
        so_far_so_good = ih_core_bool_false;
      }
    } else {
      http_message->resource_path = NULL;
      so_far_so_good = ih_core_bool_true;
    }

  } else {
    so_far_so_good = ih_core_bool_false;
    ih_core_trace("malloc");
  }

  if (so_far_so_good) {
    if (http_headers) {
      http_message->http_headers = ih_case_set_copy(http_headers);
    } else {
      ih_core_nameobject_init_iobject(&http_message->nameobject_iobject);
      http_message->http_headers
        = ih_case_set_create(&http_message->nameobject_iobject);
      if (!http_message->http_headers) {
        so_far_so_good = ih_core_bool_false;
        ih_core_trace("x_case_set_create");
      }
    }
  }

  if (so_far_so_good) {
    if (http_message->resource_path) {
      if (!ih_net_http_message_create_uri(http_message)) {
        so_far_so_good = ih_core_bool_false;
      }
    }
  }

  if (!so_far_so_good && http_message) {
    ih_net_http_message_create_rollback(http_message);
    http_message = NULL;
  }

  assert(!http_message || http_message->http_headers);
  return http_message;
}

ih_core_bool_t ih_net_http_message_create_uri
(ih_net_http_message_t *http_message)
{
  assert(http_message->resource_path);
  ih_core_bool_t success;
  char *parameters;
  char *parameter;
  char *name;
  char *value;
  char *parameter_context;
  char *nameobject_context;
  ih_core_nameobject_t *nameobject;
  char *resource_name;
  char *decoded_value;

  nameobject_context = NULL;

  resource_name = strtok(http_message->resource_path, "?");
  http_message->resource_name = strdup(resource_name);
  /*
    TODO: check the result of the strdup!
  */
  parameters = strtok(NULL, "?");
  if (parameters) {
    http_message->uri_parameters
      = ih_case_set_create(&http_message->nameobject_iobject);
    if (http_message->uri_parameters) {
      success = ih_core_bool_true;
      parameter = strtok_r(parameters, "&", &parameter_context);
      while (parameter) {
        name = strtok_r(parameter, "=", &nameobject_context);
        value = strtok_r(NULL, "=", &nameobject_context);
        if (name && value) {
          decoded_value = ih_net_http_decode_uri(value, strlen(value));
          if (decoded_value) {
            nameobject = ih_core_nameobject_create(name, decoded_value,
                ih_core_string_copy, ih_core_string_destroy,
                ih_core_string_get_as_string);
            if (nameobject) {
              if (!ih_case_set_add
                  (http_message->uri_parameters, nameobject)) {
                ih_core_nameobject_destroy(nameobject);
              }
            } else {
              ih_core_trace("x_core_nameobject_create");
              success = ih_core_bool_false;
            }
            ih_core_string_destroy(decoded_value);
          } else {
            ih_core_trace("ih_net_http_decode_uri");
          }
        }
        parameter = strtok_r(NULL, "&", &parameter_context);
      }
    } else {
      ih_core_trace("x_case_set_create");
      success = ih_core_bool_false;
    }
  } else {
    http_message->uri_parameters = NULL;
    success = ih_core_bool_true;
  }

  return success;
}

void ih_net_http_message_create_rollback(ih_net_http_message_t *http_message)
{
  assert(http_message);

  if (http_message->resource_path) {
    free(http_message->resource_path);
  }
  if (http_message->http_headers) {
    ih_case_set_destroy(http_message->http_headers);
  }
  if (http_message->body) {
    free(http_message->body);
  }
  free(http_message);
}

void ih_net_http_message_destroy(void *http_message_object)
{
  assert(http_message_object);
  ih_net_http_message_t *http_message;

  http_message = http_message_object;

  if (http_message->body) {
    free(http_message->body);
  }

  if (http_message->resource_path) {
    free(http_message->resource_path);
  }

  if (http_message->resource_name) {
    free(http_message->resource_name);
  }

  if (http_message->uri_parameters) {
    ih_case_set_destroy(http_message->uri_parameters);
  }

  ih_case_set_destroy(http_message->http_headers);

  free(http_message);
}

char *ih_net_http_message_get_body(ih_net_http_message_t *http_message)
{
  return http_message->body;
}

unsigned long ih_net_http_message_get_body_size
(ih_net_http_message_t *http_message)
{
  return http_message->body_size;
}

int ih_net_http_message_get_client_socket(void *http_message_object)
{
  assert(http_message_object);
  ih_net_http_message_t *http_message;

  http_message = http_message_object;

  return http_message->client_socket;
}

ih_core_engine_id_t ih_net_http_message_get_engine_id(void *message_object)
{
  return IH_CORE_ENGINE_HTTP;
}

ih_core_nameobject_t *ih_net_http_message_get_http_header
(ih_net_http_message_t *http_message, char *header_name)
{
  assert(http_message);
  assert(header_name);
  ih_core_nameobject_t *decoy_header;
  ih_core_nameobject_t *found_header;

  decoy_header = ih_core_nameobject_create_decoy(header_name);
  found_header = ih_case_set_find
    (http_message->http_headers, decoy_header);

  return found_header;
}

ih_case_set_t *ih_net_http_message_get_http_headers
(ih_net_http_message_t *http_message)
{
  return http_message->http_headers;
}

ih_net_http_method_t ih_net_http_message_get_http_method
(ih_net_http_message_t *http_message)
{
  return http_message->http_method;
}

ih_net_http_status_t ih_net_http_message_get_http_status
(ih_net_http_message_t *http_message)
{
  return http_message->http_status;
}

ih_net_http_version_t ih_net_http_message_get_http_version
(ih_net_http_message_t *http_message)
{
  return http_message->http_version;
}

char *ih_net_http_message_get_resource_name
(ih_net_http_message_t *http_message)
{
  return http_message->resource_name;
}

char *ih_net_http_message_get_uri_parameter
(ih_net_http_message_t *http_message, char *parameter_name)
{
  char *parameter_value;
  ih_core_nameobject_t *nameobject_decoy;
  ih_core_nameobject_t *nameobject;

  if (http_message->uri_parameters) {
    nameobject_decoy = ih_core_nameobject_create_decoy(parameter_name);
    if (nameobject_decoy) {
      nameobject
        = ih_case_set_find(http_message->uri_parameters, nameobject_decoy);
      if (nameobject) {
        parameter_value = ih_core_nameobject_get_object(nameobject);
      } else {
        parameter_value = NULL;
      }
      ih_core_nameobject_destroy_decoy(nameobject_decoy);
    } else {
      ih_core_trace("x_core_nameobject_create_decoy");
      parameter_value = NULL;
    }
  } else {
    parameter_value = NULL;
  }

  return parameter_value;
}

double ih_net_http_message_get_uri_parameter_as_double
(ih_net_http_message_t *http_message, char *parameter_name)
{
  assert(http_message);
  assert(parameter_name);
  char *value_string;
  double value_double;

  value_double = 0.0;

  value_string
    = ih_net_http_message_get_uri_parameter(http_message, parameter_name);
  if (value_string) {
    value_double = atof(value_string);
    free(value_string);
  } else {
    ih_core_trace("x_net_http_message_get_uri_parameter");
  }

  return value_double;
}

ih_core_bool_t ih_net_http_message_get_uri_parameter_as_unsigned_long
(ih_net_http_message_t *http_message, char *parameter_name,
    unsigned long *value)
{
  assert(http_message);
  assert(parameter_name);
  assert(value);
  char *value_string;
  ih_core_bool_t success;

  value_string
    = ih_net_http_message_get_uri_parameter(http_message, parameter_name);
  if (value_string) {
    success = ih_core_bool_true;
    *value = atol(value_string);
  } else {
    success = ih_core_bool_false;
    ih_core_trace("x_net_http_message_get_uri_parameter");
  }

  return success;
}

ih_core_uuid_t *ih_net_http_message_get_uri_parameter_as_uuid
(ih_net_http_message_t *http_message, char *parameter_name)
{
  assert(http_message);
  assert(parameter_name);
  ih_core_uuid_t *uuid;
  char *uuid_string;

  uuid = NULL;

  uuid_string
    = ih_net_http_message_get_uri_parameter(http_message, parameter_name);
  if (uuid_string) {
    uuid = ih_core_uuid_create_from_string(uuid_string);
    if (!uuid) {
      ih_core_trace("x_core_uuid_create_from_string");
    }
  } else {
    ih_core_trace("x_net_http_message_get_uri_parameter");
  }

  return uuid;
}

ih_case_set_t *ih_net_http_message_get_uri_parameter_as_uuid_set
(ih_net_http_message_t *http_message, char *parameter_name)
{
  assert(http_message);
  assert(parameter_name);
  ih_core_uuid_t *uuid;
  char *uuid_string;
  char *parameter_string;
  ih_case_list_t *uuid_strings;
  ih_case_set_t *uuid_set;

  uuid_set = ih_case_set_create(&http_message->uuid_iobject);
  if (uuid_set) {
    parameter_string
      = ih_net_http_message_get_uri_parameter(http_message, parameter_name);
    if (parameter_string) {
      uuid_strings
        = ih_case_list_create_strings_from_string(parameter_string, ",");
      if (uuid_strings) {
        ih_case_list_iterate_start(uuid_strings);
        while ((uuid_string = ih_case_list_iterate_next(uuid_strings))) {
          uuid = ih_core_uuid_create_from_string(uuid_string);
          if (uuid) {
            if (!ih_case_set_find(uuid_set, uuid)) {
              if (!ih_case_set_add(uuid_set, uuid)) {
                ih_core_uuid_destroy(uuid);
                ih_core_trace("x_case_set_add");
              }
            } else {
              ih_core_uuid_destroy(uuid);
            }
          } else {
            ih_core_trace("x_core_uuid_create_from_string");
          }
        }
        ih_case_list_destroy(uuid_strings);
      } else {
        ih_core_trace("x_case_list_create_string_from_strings");
      }
    } else {
      ih_core_trace("x_net_http_message_get_uri_parameter");
    }
  } else {
    ih_core_trace("x_case_set_create");
  }

  return uuid_set;
}

ih_case_set_t *ih_net_http_message_get_uri_parameters
(ih_net_http_message_t *http_message)
{
  return http_message->uri_parameters;
}

char *ih_net_http_message_get_resource_path(ih_net_http_message_t *http_message)
{
  return http_message->resource_path;
}

unsigned long ih_net_http_message_get_type(void *message_object)
{
  return IH_CORE_IMESSAGE_NO_TYPE;
}

ih_core_bool_t ih_net_http_message_set_body(ih_net_http_message_t *http_message,
    ih_core_content_t content_type, char *body, unsigned long body_size)
{
  assert(http_message);
  assert(body);
  assert(body_size > 0);
  ih_core_bool_t success;
  char *content_type_name;
  char *body_size_string;

  content_type_name = ih_core_content_get_name(content_type);
  success = ih_core_bool_true;

  if (!ih_net_http_message_set_http_header
      (http_message, "Content-Type", content_type_name)) {
    success = ih_core_bool_false;
  }

  if (asprintf(&body_size_string, "%lu", body_size) != -1) {
    if (!ih_net_http_message_set_http_header
        (http_message, "Content-Length", body_size_string)) {
      success = ih_core_bool_false;
    }
    free(body_size_string);
  } else {
    ih_core_trace("asprintf");
  }

  if (success) {
    http_message->body = malloc(body_size);
    if (http_message->body) {
      memcpy(http_message->body, body, body_size);
      http_message->body_size = body_size;
    } else {
      ih_core_trace("malloc");
      success = ih_core_bool_false;
    }
  }

  return success;
}

ih_core_bool_t ih_net_http_message_set_http_header
(ih_net_http_message_t *http_message, char *header_name, char *header_value)
{
  assert(http_message);
  assert(header_name);
  assert(header_value);
  ih_core_bool_t success;
  ih_core_nameobject_t *nameobject;

  nameobject = ih_core_nameobject_create(header_name, header_value,
      ih_core_string_copy, ih_core_string_destroy, ih_core_string_get_as_string);
  if (nameobject) {
    if (ih_case_set_add(http_message->http_headers, nameobject)) {
      success = ih_core_bool_true;
    } else {
      success = ih_core_bool_false;
    }
  } else {
    success = ih_core_bool_false;
  }

  return success;
}
