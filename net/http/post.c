#include "ih/case/list.h"
#include "ih/core/nameobject.h"
#include "ih/core/string.h"
#include "ih/core/tools.h"
#include "ih/net/http/message.h"
#include "ih/net/http/post.h"
#include "ih/net/socket.h"

#define IN_BUFFER_SIZE 4096
#define STATUS_STRING_OK "200 OK"
#define STATUS_STRING_NOT_FOUND "404 Not Found"

struct ih_net_http_post_t {
  int socket;

  ih_case_list_t *inbox;
  ih_case_list_t *outbox;

  char *out_buffer;
  unsigned long out_buffer_size;
  ih_core_bool_t currently_sending_out_buffer;
  unsigned long out_buffer_send_position;

  char in_buffer[IN_BUFFER_SIZE];
  ih_core_bool_t in_buffer_have_status_line;
  ih_core_bool_t in_buffer_have_headers;
  ih_core_bool_t in_buffer_expecting_body;
  ih_core_bool_t in_buffer_have_body;
  ih_core_bool_t in_buffer_have_complete_message;
  unsigned long in_buffer_receive_position;
  unsigned long in_buffer_parse_position;
  ih_net_http_method_t in_http_method;
  char *in_resource_path;
  ih_net_http_version_t in_http_version;
  ih_case_set_t *in_http_headers;
  char *in_body;

  time_t last_receive_activity_time;
  ih_core_bool_t socket_closed;

  ih_net_post_stats_t stats;

  ih_core_iobject_t nameobject_iobject;
};

static char *get_header_lines(ih_net_http_message_t *http_message,
    unsigned short *header_lines_size);

static char *get_outgoing_status_line(ih_net_http_message_t *http_message,
    unsigned short *status_line_size);

static const char *get_outgoing_status_line_status_string
(ih_net_http_status_t http_status, unsigned short *status_string_size);

static void ih_net_http_post_create_rollback(ih_net_http_post_t *http_post);

static ih_net_http_method_t parse_http_method(char *http_method_string);

static ih_net_http_version_t parse_http_version(char *http_version_string);

static void parse_incoming_message(ih_net_http_post_t *http_post);

static void parse_incoming_message_status_line(ih_net_http_post_t *http_post);

static void parse_incoming_message_headers(ih_net_http_post_t *http_post);

static void parse_incoming_message_body(ih_net_http_post_t *http_post);

static ih_core_bool_t put_message_into_out_buffer(ih_net_http_post_t *http_post,
    ih_net_http_message_t *http_message);

static ih_core_bool_t put_received_message_in_inbox
(ih_net_http_post_t *http_post);

static ih_core_bool_t receive_messages(ih_net_http_post_t *http_post);

static void reset_for_next_receive(ih_net_http_post_t *http_post);

static void reset_for_next_send(ih_net_http_post_t *http_post);

static void send_messages_get_new_message(ih_net_http_post_t *http_post);

static ih_core_bool_t send_messages_send_current_message
(ih_net_http_post_t *http_post);

char *get_header_lines(ih_net_http_message_t *http_message,
    unsigned short *header_lines_size)
{
  assert(http_message);
  assert(header_lines_size);
  ih_case_set_t *http_headers;
  char *header_lines;
  ih_core_nameobject_t *header;
  char *header_name;
  char *header_value;
  unsigned short line_size;
  unsigned short header_lines_position;
  unsigned short header_name_size;
  unsigned short header_value_size;

  header_lines = NULL;
  header_lines_position = 0;
  *header_lines_size = 0;
  http_headers = ih_net_http_message_get_http_headers(http_message);

  ih_case_set_iterate_start(http_headers);

  while ((header = ih_case_set_iterate_next(http_headers))) {

    header_name = ih_core_nameobject_get_name(header);
    header_value = ih_core_nameobject_get_object(header);
    header_name_size = strlen(header_name);
    header_value_size = strlen(header_value);
    line_size = header_name_size + 2 + header_value_size;

    *header_lines_size += line_size + 2;
    header_lines = realloc(header_lines, *header_lines_size);
    if (!header_lines) {
      ih_core_trace("realloc");
      break;
    }

    memcpy(header_lines + header_lines_position, header_name,
        header_name_size);
    header_lines_position += header_name_size;

    memcpy(header_lines + header_lines_position, ": ", 2);
    header_lines_position += 2;

    memcpy(header_lines + header_lines_position, header_value,
        header_value_size);
    header_lines_position += header_value_size;

    memcpy(header_lines + header_lines_position, "\r\n", 2);
    header_lines_position += 2;

  }

  return header_lines;
}

char *get_outgoing_status_line(ih_net_http_message_t *http_message,
    unsigned short *status_line_size)
{
  assert(http_message);
  assert(status_line_size);
  char *status_line;
  const char *http_version_name;
  ih_net_http_version_t http_version;
  unsigned short http_version_name_size;
  const char *status_string;
  unsigned short status_string_size;
  ih_net_http_status_t http_status;

  http_status = ih_net_http_message_get_http_status(http_message);
  http_version = ih_net_http_message_get_http_version(http_message);
  http_version_name = ih_net_http_version_get_name(http_version);
  http_version_name_size = strlen(http_version_name);

  status_string = get_outgoing_status_line_status_string(http_status,
      &status_string_size);

  *status_line_size = http_version_name_size + 1 + status_string_size + 2;
  status_line = malloc(*status_line_size);
  if (status_line) {
    memcpy(status_line, http_version_name, http_version_name_size);
    *(status_line + http_version_name_size) = ' ';
    memcpy(status_line + http_version_name_size + 1, status_string,
        status_string_size);
    memcpy(status_line + http_version_name_size + 1 + status_string_size,
        "\r\n", 2);
  } else {
    ih_core_trace("malloc");
  }

  return status_line;
}

const char *get_outgoing_status_line_status_string
(ih_net_http_status_t http_status, unsigned short *status_string_size)
{
  assert(status_string_size);
  const char *status_string;

  switch (http_status) {

    case IH_NET_HTTP_STATUS_OK:
      status_string = STATUS_STRING_OK;
      *status_string_size = strlen(STATUS_STRING_OK);
      break;

    case IH_NET_HTTP_STATUS_NOT_FOUND:
      status_string = STATUS_STRING_NOT_FOUND;
      *status_string_size = strlen(STATUS_STRING_NOT_FOUND);
      break;

    default:
    case IH_NET_HTTP_STATUS_UNKNOWN:
      ih_core_trace("invalid http status");
      status_string = "";
      *status_string_size = 0;
      break;

  }

  assert(status_string);
  return status_string;
}

int ih_net_http_post_compare(void *http_post_object_a,
    void *http_post_object_b)
{
  assert(http_post_object_a);
  assert(http_post_object_b);
  ih_net_http_post_t *http_post_a;
  ih_net_http_post_t *http_post_b;
  int compare;

  http_post_a = http_post_object_a;
  http_post_b = http_post_object_b;

  if (http_post_a->socket < http_post_b->socket) {
    compare = -1;
  } else if (http_post_a->socket > http_post_b->socket) {
    compare = 1;
  } else {
    compare = 0;
  }

  return compare;
}

ih_core_bool_t ih_net_http_post_compare_equal(void *http_post_object_a,
    void *http_post_object_b)
{
  assert(http_post_object_a);
  assert(http_post_object_b);
  ih_net_http_post_t *http_post_a = http_post_object_a;
  ih_net_http_post_t *http_post_b = http_post_object_b;
  ih_core_bool_t compare;

  if (http_post_a->socket == http_post_b->socket) {
    compare = ih_core_bool_true;
  } else {
    compare = ih_core_bool_false;
  }

  return compare;
}

void *ih_net_http_post_create(int socket)
{
  ih_net_http_post_t *http_post;
  ih_core_bool_t so_far_so_good;

  http_post = malloc(sizeof *http_post);
  if (http_post) {
    http_post->socket = socket;
    http_post->last_receive_activity_time = time(NULL);
    http_post->socket_closed = ih_core_bool_false;

    http_post->in_buffer_have_status_line = ih_core_bool_false;
    http_post->in_buffer_have_headers = ih_core_bool_false;
    http_post->in_buffer_have_body = ih_core_bool_false;
    http_post->in_buffer_have_complete_message = ih_core_bool_false;
    http_post->in_buffer_receive_position = 0;
    http_post->in_buffer_parse_position = 0;
    http_post->in_resource_path = NULL;
    http_post->in_body = NULL;

    http_post->out_buffer = NULL;
    http_post->out_buffer_size = 0;
    http_post->currently_sending_out_buffer = ih_core_bool_false;
    http_post->out_buffer_send_position = 0;

    ih_net_post_stats_init(&http_post->stats);

    so_far_so_good = ih_core_bool_true;
  } else {
    so_far_so_good = ih_core_bool_false;
    ih_core_trace("malloc");
  }

  if (so_far_so_good) {
    ih_core_nameobject_init_iobject(&http_post->nameobject_iobject);
    http_post->in_http_headers
      = ih_case_set_create(&http_post->nameobject_iobject);
    if (!http_post->in_http_headers) {
      ih_core_trace("x_case_set_create");
      so_far_so_good = ih_core_bool_false;
    }
  }

  if (so_far_so_good) {
    http_post->inbox = ih_case_list_create(IH_CORE_OBJECT_NO_COMPARE_F,
        IH_CORE_OBJECT_NO_COPY_F, IH_CORE_OBJECT_NO_DESTROY_F);
    if (!http_post->inbox) {
      so_far_so_good = ih_core_bool_false;
    }
  }

  if (so_far_so_good) {
    http_post->outbox = ih_case_list_create(IH_CORE_OBJECT_NO_COMPARE_F,
        IH_CORE_OBJECT_NO_COPY_F, ih_net_http_message_destroy);
    if (!http_post->outbox) {
      so_far_so_good = ih_core_bool_false;
    }
  }

  if (!so_far_so_good && http_post) {
    ih_net_http_post_create_rollback(http_post);
    http_post = NULL;
  }

  return http_post;
}

void *ih_net_http_post_create_decoy(int socket)
{
  ih_net_http_post_t *http_post;

  http_post = malloc(sizeof *http_post);
  if (http_post) {
    http_post->socket = socket;
  } else {
    ih_core_trace("malloc() failed\n");
  }

  return http_post;
}

void ih_net_http_post_create_rollback(ih_net_http_post_t *http_post)
{
  assert(http_post);

  if (http_post->inbox) {
    ih_case_list_destroy(http_post->inbox);
  }
  if (http_post->outbox) {
    ih_case_list_destroy(http_post->outbox);
  }
  free(http_post);
}

void ih_net_http_post_destroy(void *http_post_object)
{
  assert(http_post_object);
  ih_net_http_post_t *http_post;
  ih_net_http_message_t *http_message;

  http_post = http_post_object;

  ih_case_list_iterate_start(http_post->inbox);
  while ((http_message = ih_case_list_iterate_next(http_post->inbox))) {
    ih_net_http_message_destroy(http_message);
  }
  ih_case_list_destroy(http_post->inbox);

  ih_case_list_destroy(http_post->outbox);

  ih_case_set_destroy(http_post->in_http_headers);

  if (http_post->in_resource_path) {
    free(http_post->in_resource_path);
  }

  free(http_post);
}

void ih_net_http_post_destroy_decoy(void *http_post_object)
{
  free(http_post_object);
}

time_t ih_net_http_post_get_last_receive_activity_time
(void *http_post_object)
{
  assert(http_post_object);
  ih_net_http_post_t *http_post;

  http_post = http_post_object;

  return http_post->last_receive_activity_time;
}

int ih_net_http_post_get_socket(void *http_post_object)
{
  assert(http_post_object);
  ih_net_http_post_t *http_post;

  http_post = http_post_object;

  return http_post->socket;
}

void ih_net_http_post_get_stats(void *http_post_object,
    ih_net_post_stats_t *post_stats)
{
  assert(http_post_object);
  assert(post_stats);
  ih_net_http_post_t *http_post;

  http_post = http_post_object;

  post_stats->messages_sent = http_post->stats.messages_sent;
  post_stats->messages_received = http_post->stats.messages_received;
  post_stats->messages_in_inbox = http_post->stats.messages_in_inbox;
  post_stats->messages_in_outbox = http_post->stats.messages_in_outbox;
  post_stats->most_messages_ever_in_inbox
    = http_post->stats.most_messages_ever_in_inbox;
  post_stats->most_messages_ever_in_outbox
    = http_post->stats.most_messages_ever_in_outbox;
  post_stats->send_message_failures = http_post->stats.send_message_failures;
  post_stats->receive_message_failures
    = http_post->stats.receive_message_failures;
  post_stats->messages_not_sent_due_to_socket_send_failures
    = http_post->stats.messages_not_sent_due_to_socket_send_failures;
}

unsigned long ih_net_http_post_hash(void *post_object)
{
  assert(post_object);
  ih_net_http_post_t *post = post_object;
  return post->socket;
}

ih_core_bool_t ih_net_http_post_is_socket_closed(void *http_post_object)
{
  assert(http_post_object);
  ih_net_http_post_t *http_post;

  http_post = http_post_object;

  return http_post->socket_closed;
}

void *ih_net_http_post_receive_message(void *http_post_object)
{
  assert(http_post_object);
  ih_net_http_post_t *http_post;
  ih_net_http_message_t *http_message;

  http_post = http_post_object;

  http_message = ih_case_list_find_first(http_post->inbox);
  if (http_message) {
    ih_case_list_remove_first(http_post->inbox);
  }

  return http_message;
}

void ih_net_http_post_receive_messages(void *http_post_object)
{
  assert(http_post_object);
  ih_net_http_post_t *http_post;

  http_post = http_post_object;

  http_post->last_receive_activity_time = time(NULL);

  if (receive_messages(http_post)) {
    reset_for_next_receive(http_post);
  }
}

ih_core_bool_t ih_net_http_post_send_message(void *http_post_object,
    void *http_message_object)
{
  assert(http_post_object);
  assert(http_message_object);
  ih_core_bool_t success;
  ih_net_http_post_t *http_post;

  http_post = http_post_object;

  success = ih_case_list_add_last(http_post->outbox, http_message_object);

  return success;
}

void ih_net_http_post_send_messages(void *http_post_object)
{
  assert(http_post_object);
  ih_net_http_post_t *http_post;

  http_post = http_post_object;

  if (!http_post->currently_sending_out_buffer) {
    send_messages_get_new_message(http_post);
  }
  if (http_post->currently_sending_out_buffer) {
    if (send_messages_send_current_message(http_post)) {
      reset_for_next_send(http_post);
    }
  }
}

ih_net_http_method_t parse_http_method(char *resource_path_string)
{
  assert(resource_path_string);
  ih_net_http_method_t http_method;

  if (0 == strcmp(resource_path_string, "GET")) {
    http_method = IH_NET_HTTP_METHOD_GET;

  } else if (0 == strcmp(resource_path_string, "HEAD")) {
    http_method = IH_NET_HTTP_METHOD_HEAD;

  } else if (0 == strcmp(resource_path_string, "POST")) {
    http_method = IH_NET_HTTP_METHOD_POST;

  } else {
    http_method = IH_NET_HTTP_METHOD_UNKNOWN;

  }

  return http_method;
}

ih_net_http_version_t parse_http_version(char *http_version_string)
{
  assert(http_version_string);
  ih_net_http_version_t http_version;

  if (0 == strcmp(http_version_string, "HTTP/1.1")) {
    http_version = IH_NET_HTTP_VERSION_1_1;

  } else if (0 == strcmp(http_version_string, "HTTP/1.0")) {
    http_version = IH_NET_HTTP_VERSION_1_0;

  } else {
    http_version = IH_NET_HTTP_VERSION_UNKNOWN;

  }

  return http_version;
}

void parse_incoming_message(ih_net_http_post_t *http_post)
{
  assert(http_post);
  assert(!http_post->in_buffer_have_complete_message);

  if (!http_post->in_buffer_have_status_line) {
    parse_incoming_message_status_line(http_post);
  }

  if (http_post->in_buffer_have_status_line
      && !http_post->in_buffer_have_headers) {
    parse_incoming_message_headers(http_post);
  }

  if (http_post->in_buffer_have_status_line
      && http_post->in_buffer_have_headers
      && http_post->in_buffer_expecting_body
      && !http_post->in_buffer_have_body) {
    parse_incoming_message_body(http_post);
  }
}

void parse_incoming_message_status_line(ih_net_http_post_t *http_post)
{
  assert(http_post);
  char *first_newline;
  char *remaining_message;
  unsigned short line_size;
  char *line;
  char *http_method_string;
  char *resource_path_string;
  char *http_version_string;
  char *strtok_r_char;

  strtok_r_char = NULL;

  remaining_message = http_post->in_buffer
    + http_post->in_buffer_parse_position;

  first_newline = strstr(remaining_message, "\r\n");
  if (first_newline) {
    line_size = first_newline - http_post->in_buffer;
    line = malloc(line_size + 1);
    if (line) {
      memcpy(line, http_post->in_buffer, line_size);
      *(line + line_size) = '\0';

      http_method_string = strtok_r(line, " ", &strtok_r_char);
      resource_path_string = strtok_r(NULL, " ", &strtok_r_char);
      http_version_string = strtok_r(NULL, " ", &strtok_r_char);

      if (http_method_string && resource_path_string && http_version_string) {
        http_post->in_http_method = parse_http_method(http_method_string);
        http_post->in_resource_path = strdup(resource_path_string);
        http_post->in_http_version = parse_http_version(http_version_string);
        http_post->in_buffer_have_status_line = ih_core_bool_true;
        http_post->in_buffer_parse_position += line_size + 2;
      } else {
        printf("http_post received malformed http status line from "
            "client %i\n", http_post->socket);
      }

      free(line);
    } else {
      ih_core_trace("malloc");
    }
  }
}

void parse_incoming_message_headers(ih_net_http_post_t *http_post)
{
  char *double_newline_char;
  char *start_char;
  char *line;
  char *name;
  char *value;
  char *line_context;
  char *nameobject_context;
  ih_core_nameobject_t *nameobject;

  start_char = http_post->in_buffer + http_post->in_buffer_parse_position;
  double_newline_char = strstr(start_char, "\r\n\r\n");
  if (double_newline_char) {
    http_post->in_buffer_expecting_body = ih_core_bool_false;
    line = strtok_r(start_char, "\r\n", &line_context);
    while (line) {
      name = strtok_r(line, ": ", &nameobject_context);
      value = strtok_r(NULL, ": ", &nameobject_context);
      if (name && value) {
        if ((0 == strcmp(name, "Content-Length"))
            || (0 == strcmp(name, "Transfer-Encoding"))) {
          http_post->in_buffer_expecting_body = ih_core_bool_true;
        }
        nameobject = ih_core_nameobject_create(name, value, ih_core_string_copy,
            ih_core_string_destroy, ih_core_string_get_as_string);
        if (nameobject) {
          if (!ih_case_set_add(http_post->in_http_headers, nameobject)) {
            ih_core_nameobject_destroy(nameobject);
          }
        }
      }
      line = strtok_r(NULL, "\r\n", &line_context);
    }

    if (!http_post->in_buffer_expecting_body) {
      http_post->in_buffer_have_complete_message = ih_core_bool_true;
    }

    http_post->in_buffer_have_headers = ih_core_bool_true;
    http_post->in_buffer_parse_position
      += (double_newline_char - start_char) + 2;
  }
}

void parse_incoming_message_body(ih_net_http_post_t *http_post)
{
  /*
    TODO: if that works, set http_post->in_buffer_have_complete_message
  */
}

ih_core_bool_t put_message_into_out_buffer(ih_net_http_post_t *http_post,
    ih_net_http_message_t *http_message)
{
  assert(http_post);
  assert(http_message);
  ih_core_bool_t success;
  unsigned long message_body_size;
  char *message_body;
  char *status_line;
  unsigned short status_line_size;
  char *headers;
  unsigned short headers_size;
  unsigned long message_size;
  unsigned long buffer_write_position;

  status_line = get_outgoing_status_line(http_message, &status_line_size);
  if (status_line) {
    headers = get_header_lines(http_message, &headers_size);

    message_body = ih_net_http_message_get_body(http_message);
    message_body_size = ih_net_http_message_get_body_size(http_message);

    message_size = status_line_size + headers_size + 2 + message_body_size;

    http_post->out_buffer = malloc(message_size);
    if (http_post->out_buffer) {
      success = ih_core_bool_true;
      buffer_write_position = 0;

      memcpy(http_post->out_buffer + buffer_write_position, status_line,
          status_line_size);
      buffer_write_position += status_line_size;

      memcpy(http_post->out_buffer + buffer_write_position, headers,
          headers_size);
      buffer_write_position += headers_size;
      memcpy(http_post->out_buffer + buffer_write_position, "\r\n", 2);
      buffer_write_position += 2;

      memcpy(http_post->out_buffer + buffer_write_position, message_body,
          message_body_size);

      http_post->out_buffer_size = message_size;
      http_post->out_buffer_send_position = 0;
    } else {
      ih_core_trace("malloc");
      success = ih_core_bool_false;
    }

    free(status_line);
    if (headers) {
      free(headers);
    }
  } else {
    ih_core_trace("get_outgoing_status_line");
    success = ih_core_bool_false;
  }

  return success;
}

ih_core_bool_t put_received_message_in_inbox(ih_net_http_post_t *http_post)
{
  ih_core_bool_t success;
  ih_net_http_message_t *http_message;

  http_message = ih_net_http_message_create(http_post->socket,
      http_post->in_http_method, IH_NET_HTTP_STATUS_UNKNOWN,
      http_post->in_resource_path, http_post->in_http_version,
      http_post->in_http_headers);
  if (http_message) {
    if (ih_case_list_add_last(http_post->inbox, http_message)) {
      success = ih_core_bool_true;
    } else {
      ih_core_trace("x_case_list_add_last");
      success = ih_core_bool_false;
    }
  } else {
    ih_core_trace("x_net_http_message_create");
    success = ih_core_bool_false;
  }

  return success;
}

ih_core_bool_t receive_messages(ih_net_http_post_t *http_post)
{
  assert(http_post);
  ih_core_bool_t received_complete_message;
  int actual_bytes_read;
  int max_bytes_to_read;

  received_complete_message = ih_core_bool_false;

  max_bytes_to_read = IN_BUFFER_SIZE - http_post->in_buffer_receive_position;
  actual_bytes_read = ih_net_socket_receive(http_post->socket,
      http_post->in_buffer + http_post->in_buffer_receive_position,
      max_bytes_to_read);
  if (actual_bytes_read > 0) {
    http_post->in_buffer_receive_position += actual_bytes_read;
    parse_incoming_message(http_post);
    if (http_post->in_buffer_have_complete_message) {
      received_complete_message = ih_core_bool_true;
      if (!put_received_message_in_inbox(http_post)) {
        ih_core_trace("put_received_message_in_inbox");
      }
    }
  } else {
    http_post->socket_closed = ih_core_bool_true;
    received_complete_message = ih_core_bool_true;
  }

  return received_complete_message;
}

void reset_for_next_receive(ih_net_http_post_t *http_post)
{
  http_post->in_buffer_have_status_line = ih_core_bool_false;
  http_post->in_buffer_have_headers = ih_core_bool_false;
  http_post->in_buffer_have_body = ih_core_bool_false;
  http_post->in_buffer_have_complete_message = ih_core_bool_false;
  http_post->in_buffer_receive_position = 0;
  http_post->in_buffer_parse_position = 0;
  if (http_post->in_resource_path) {
    free(http_post->in_resource_path);
    http_post->in_resource_path = NULL;
  }
  ih_case_set_clear(http_post->in_http_headers);
  if (http_post->in_body) {
    free(http_post->in_body);
    http_post->in_body = NULL;
  }
}

void reset_for_next_send(ih_net_http_post_t *http_post)
{
  free(http_post->out_buffer);
  http_post->out_buffer = NULL;
  http_post->out_buffer_size = 0;
  http_post->currently_sending_out_buffer = ih_core_bool_false;
  http_post->out_buffer_send_position = 0;
}

void send_messages_get_new_message(ih_net_http_post_t *http_post)
{
  ih_net_http_message_t *http_message;

  http_message = ih_case_list_find_first(http_post->outbox);
  if (http_message) {
    if (put_message_into_out_buffer(http_post, http_message)) {
      ih_case_list_remove_first(http_post->outbox);
      http_post->currently_sending_out_buffer = ih_core_bool_true;
    } else {
      ih_core_trace("put_message_into_out_buffer");
    }
  }
}

ih_core_bool_t send_messages_send_current_message(ih_net_http_post_t *http_post)
{
  assert(http_post);
  ih_core_bool_t sent_complete_message;
  int actual_bytes_sent;
  int bytes_remaining_to_send;

  bytes_remaining_to_send = http_post->out_buffer_size
    - http_post->out_buffer_send_position;
  if (bytes_remaining_to_send > 0) {
    actual_bytes_sent = ih_net_socket_send(http_post->socket,
        http_post->out_buffer, bytes_remaining_to_send);
    if (actual_bytes_sent > 0) {
      http_post->out_buffer_send_position += actual_bytes_sent;
      if (http_post->out_buffer_send_position == http_post->out_buffer_size) {
        sent_complete_message = ih_core_bool_true;
      } else {
        sent_complete_message = ih_core_bool_false;
      }
    } else {
      http_post->socket_closed = ih_core_bool_true;
      sent_complete_message = ih_core_bool_false;
    }
  } else {
    sent_complete_message = ih_core_bool_true;
  }

  return sent_complete_message;
}
