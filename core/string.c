#include "ih/core/message.h"
#include "ih/core/string.h"
#include "ih/core/tools.h"

ih_core_bool_t ih_core_string_add_to_message(void *string_object,
    ih_core_message_t *message)
{
  return ih_core_message_add_string(message, string_object);
}

int ih_core_string_compare(void *string_object_a, void *string_object_b)
{
  const char *string_a;
  const char *string_b;
  int compare;

  string_a = string_object_a;
  string_b = string_object_b;
  compare = strcmp(string_a, string_b);

  return compare;
}

ih_core_bool_t ih_core_string_compare_equal(void *string_a_object,
    void *string_b_object)
{
  return (0 == ih_core_string_compare(string_a_object, string_b_object));
}

void *ih_core_string_copy(void *string_object)
{
  assert(string_object);
  char *string_copy;

  string_copy = strdup(string_object);
  if (!string_copy) {
    ih_core_trace("strdup");
  }

  return string_copy;
}

void *ih_core_string_create_from_message(ih_core_message_t *message)
{
  return ih_core_message_take_string(message);
}

void ih_core_string_destroy(void *string_object)
{
  free(string_object);
}

char *ih_core_string_get_as_string(void *string_object)
{
  assert(string_object);
  char *string_copy;

  string_copy = strdup(string_object);
  if (!string_copy) {
    ih_core_trace("strdup");
  }

  return string_copy;
}

unsigned long ih_core_string_hash(void *string_object)
{
  return ih_core_hash(string_object);
}

void ih_core_string_init_iobject(ih_core_iobject_t *iobject)
{
  assert(iobject);
  ih_core_iobject_init(iobject, ih_core_string_compare,
      ih_core_string_compare_equal, ih_core_string_copy,
      ih_core_string_destroy, ih_core_string_get_as_string,
      ih_core_string_mod);
}

unsigned long ih_core_string_mod(void *string_object, unsigned long divisor)
{
  assert(string_object);
  char *string = string_object;
  unsigned long dividend = 0;
  unsigned char i;
  char c;
  unsigned long place_value = 1;

  for (i = 0; i < 4; i++) {
    c = *(string + i);
    if (c) {
      dividend += (c * place_value);
    } else {
      break;
    }
    place_value *= 256;
  }

  return dividend % divisor;
}

void ih_core_string_print(void *string_object)
{
  char *string;
  string = string_object;
  printf("%s", string);
}

ih_core_string_t ih_core_string_substring(ih_core_string_t string,
    unsigned long start, unsigned long length)
{
  assert(string);
  ih_core_string_t substring;
  unsigned long string_length;

  string_length = strlen(string);
  if ((start + length) > string_length) {
    length = string_length - start;
  }
  substring = malloc(length + 1);
  if (substring) {
    memcpy(substring, string + start, length);
    *(substring + length) = '\0';
  } else {
    ih_core_trace("malloc");
  }

  return substring;
}
