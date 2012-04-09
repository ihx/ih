#include "ih/core/object.h"
#include "ih/core/pair.h"
#include "ih/core/tools.h"

struct ih_core_pair_t {
  void *left;
  ih_core_iobject_t *left_iobject;

  void *right;
  ih_core_iobject_t *right_iobject;

  ih_core_bool_t destroy;
};

int ih_core_pair_compare(void *pair_object_a, void *pair_object_b)
{
  ih_core_trace_exit("TODO: implement");
  return 0;
}

int ih_core_pair_compare_left(void *pair_object_a, void *pair_object_b)
{
  assert(pair_object_a);
  assert(pair_object_b);
  ih_core_pair_t *pair_a;
  ih_core_pair_t *pair_b;
  int compare_result;
  ih_core_object_compare_f compare;

  pair_a = pair_object_a;
  pair_b = pair_object_b;

  compare = pair_a->left_iobject->compare;
  compare_result = compare(pair_a->left, pair_b->left);

  return compare_result;
}

int ih_core_pair_compare_right(void *pair_object_a, void *pair_object_b)
{
  assert(pair_object_a);
  assert(pair_object_b);
  ih_core_pair_t *pair_a;
  ih_core_pair_t *pair_b;
  int compare_result;
  ih_core_object_compare_f compare;

  pair_a = pair_object_a;
  pair_b = pair_object_b;

  compare = pair_a->right_iobject->compare;
  compare_result = compare(pair_a->right, pair_b->right);

  return compare_result;
}

void *ih_core_pair_copy(void *pair_object)
{
  ih_core_trace_exit("TODO: implement");
  return NULL;
}

ih_core_pair_t *ih_core_pair_create(void *left, ih_core_iobject_t *left_iobject,
    void *right, ih_core_iobject_t *right_iobject, ih_core_bool_t destroy)
{
  assert(left);
  assert(left_iobject);
  assert(right);
  assert(right_iobject);
  ih_core_pair_t *pair;

  pair = malloc(sizeof *pair);
  if (pair) {
    pair->left = left;
    pair->left_iobject = left_iobject;
    pair->right = right;
    pair->right_iobject = right_iobject;
    pair->destroy = destroy;
  } else {
    ih_core_trace("malloc");
  }

  return pair;
}

ih_core_pair_t *ih_core_pair_create_decoy(void *left,
    ih_core_iobject_t *left_iobject)
{
  assert(left);
  assert(left_iobject);
  ih_core_pair_t *pair;

  pair = malloc(sizeof *pair);
  if (pair) {
    pair->left = left;
    pair->left_iobject = left_iobject;
  } else {
    ih_core_trace("malloc");
  }

  return pair;
}

void ih_core_pair_destroy(void *pair_object)
{
  assert(pair_object);
  ih_core_pair_t *pair;

  pair = pair_object;

  if (pair->destroy) {
    if (pair->left_iobject->destroy) {
      pair->left_iobject->destroy(pair->left);
    }
    if (pair->right_iobject->destroy) {
      pair->right_iobject->destroy(pair->right);
    }
  }

  free(pair);
}

void ih_core_pair_destroy_decoy(ih_core_pair_t *pair)
{
  free(pair);
}

ih_core_bool_t ih_core_pair_equal_left(void *pair_a_object, void *pair_b_object)
{
  return (0 == ih_core_pair_compare_left(pair_a_object, pair_b_object));
}

char *ih_core_pair_get_as_string(void *pair_object)
{
  assert(pair_object);
  ih_core_pair_t *pair;
  char *string;
  ih_core_object_get_as_string_f left_get_as_string;
  ih_core_object_get_as_string_f right_get_as_string;
  char *left_string;
  char *right_string;

  pair = pair_object;

  left_get_as_string = pair->left_iobject->get_as_string;
  right_get_as_string = pair->right_iobject->get_as_string;

  left_string = left_get_as_string(pair->left);
  right_string = right_get_as_string(pair->right);

  string = ih_core_string_append(NULL, right_string);
  string = ih_core_string_append(string, ":");
  string = ih_core_string_append(string, right_string);

  free(left_string);
  free(right_string);

  return string;
}

void *ih_core_pair_get_left(ih_core_pair_t *pair)
{
  return pair->left;
}

ih_core_iobject_t *ih_core_pair_get_left_iobject(ih_core_pair_t *pair)
{
  return pair->left_iobject;
}

void *ih_core_pair_get_right(ih_core_pair_t *pair)
{
  return pair->right;
}

ih_core_iobject_t *ih_core_pair_get_right_iobject(ih_core_pair_t *pair)
{
  return pair->right_iobject;
}

unsigned long ih_core_pair_hash_left(void *pair_object)
{
  assert(pair_object);
  ih_core_pair_t *pair = pair_object;
  return pair->left_iobject->hash(pair->left);
}

void ih_core_pair_init_iobject(ih_core_iobject_t *iobject)
{
  assert(iobject);

  iobject->compare = ih_core_pair_compare;
  iobject->copy = ih_core_pair_copy;
  iobject->destroy = ih_core_pair_destroy;
  iobject->get_as_string = ih_core_pair_get_as_string;
}
