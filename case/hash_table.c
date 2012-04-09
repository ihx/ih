#include "ih/case/hash_table.h"

#define NODE_COUNT 4096

struct node_t;
typedef struct node_t node_t;

struct node_t {
  void *object;
  node_t *previous;
  node_t *next;
};

static node_t *node_create(void *object, node_t *previous, node_t *next,
    ih_case_hash_table_t *hash_table);
static void node_destroy(node_t *node, ih_case_hash_table_t *hash_table);

struct ih_case_hash_table_t {
  node_t **nodes;
  unsigned long size;
  ih_core_iobject_t *iobject;
  node_t *iterator;
  unsigned long iterate_node;
  ih_core_bool_t iterate_remove;
  pthread_mutex_t mutex;
};

ih_core_bool_t ih_case_hash_table_add(ih_case_hash_table_t *hash_table,
    void *object)
{
  unsigned long hash = hash_table->iobject->hash(object) % NODE_COUNT;
  node_t *node = *(hash_table->nodes + hash);
  ih_core_bool_t success = ih_core_bool_true;

  if (!node) {
    node = node_create(object, NULL, NULL, hash_table);
    if (!node) {
      ih_core_trace("node_create");
      success = ih_core_bool_false;
    }
  } else {
    while (node->next) {
      node = node->next;
    }
    node->next = node_create(object, NULL, NULL, hash_table);
    if (!node) {
      ih_core_trace("node_create");
      success = ih_core_bool_false;
    }
  }

  return success;
}

void ih_case_hash_table_clear(ih_case_hash_table_t *hash_table)
{
  unsigned long i;
  node_t *node;
  node_t *next_node;

  for (i = 0; i < NODE_COUNT; i++) {
    node = *(hash_table->nodes + i);
    while (node) {
      next_node = node->next;
      node_destroy(node, hash_table);
      node = next_node;
    }
  }
}

ih_case_hash_table_t *ih_case_hash_table_create(ih_core_iobject_t *iobject)
{
  ih_case_hash_table_t *hash_table;
  unsigned long i;
  ih_core_bool_t so_far_so_good = ih_core_bool_true;

  hash_table = malloc(sizeof *hash_table);
  if (hash_table) {
    hash_table->iobject = iobject;
    hash_table->nodes = malloc((sizeof *hash_table->nodes) * NODE_COUNT);
    if (hash_table->nodes) {
      for (i = 0; i < NODE_COUNT; i++) {
        *(hash_table->nodes + i) = NULL;
      }
    } else {
      ih_core_trace("malloc");
      so_far_so_good = ih_core_bool_false;
    }
  } else {
    ih_core_trace("malloc");
  }

  if (so_far_so_good) {
    if (0 != pthread_mutex_init(&hash_table->mutex, NULL)) {
      ih_core_trace("pthread_mutex_init");
      so_far_so_good = ih_core_bool_false;
    }
  }

  if (!so_far_so_good && hash_table) {
    if (hash_table->nodes) {
      free(hash_table->nodes);
    }
    free(hash_table);
    hash_table = NULL;
  }

  return hash_table;
}

void ih_case_hash_table_destroy(ih_case_hash_table_t *hash_table)
{
  ih_case_hash_table_clear(hash_table);
  if (0 != pthread_mutex_destroy(&hash_table->mutex)) {
    ih_core_trace("pthread_mutex_destroy");
  }
  free(hash_table);
}

void ih_case_hash_table_dont_destroy_objects(ih_case_hash_table_t *hash_table)
{
  hash_table->iobject->destroy = NULL;
}

void *ih_case_hash_table_find(ih_case_hash_table_t *hash_table,
    void *decoy_object)
{
  assert(hash_table);
  assert(decoy_object);
  unsigned long hash = hash_table->iobject->hash(decoy_object) % NODE_COUNT;
  node_t *node = *(hash_table->nodes + hash);
  void *object;
  ih_core_bool_t found = ih_core_bool_false;

  while (!found && node) {
    object = node->object;
    if (hash_table->iobject->compare_equal(decoy_object, object)) {
      found = ih_core_bool_true;
    } else {
      node = node->next;
    }
  }

  return object;
}

ih_core_iobject_t *ih_case_hash_table_get_iobject
(ih_case_hash_table_t *hash_table)
{
  return hash_table->iobject;
}

unsigned long ih_case_hash_table_get_size(ih_case_hash_table_t *hash_table)
{
  return hash_table->size;
}

void ih_case_hash_table_iterate_remove(ih_case_hash_table_t *hash_table)
{
  hash_table->iterate_remove = ih_core_bool_true;
}

void ih_case_hash_table_iterate_start(ih_case_hash_table_t *hash_table)
{
  hash_table->iterator = NULL;
  hash_table->iterate_node = 0;
  hash_table->iterate_remove = ih_core_bool_false;
}

void *ih_case_hash_table_iterate_next(ih_case_hash_table_t *hash_table)
{
  assert(hash_table);
  void *next_object;

  if (hash_table->iterator && hash_table->iterator->next) {
    hash_table->iterator = hash_table->iterator->next;
  } else {
    while ((hash_table->iterate_node < NODE_COUNT)
        && (!*(hash_table->nodes + hash_table->iterate_node))) {
      hash_table->iterate_node++;
    }
    hash_table->iterator = *(hash_table->nodes + hash_table->iterate_node);
  }

  if (hash_table->iterate_remove && hash_table->iterator) {
    /*  fz  */
  }

  if (hash_table->iterator) {
    next_object = hash_table->iterator->object;
  } else {
    next_object = NULL;
  }

  return next_object;
}

void ih_case_hash_table_lock(ih_case_hash_table_t *hash_table) {
  pthread_mutex_lock(&hash_table->mutex);
}

ih_core_bool_t ih_case_hash_table_remove(ih_case_hash_table_t *hash_table,
    void *decoy_object)
{
  /*  fz  */
  return ih_core_bool_false;
}

void ih_case_hash_table_unlock(ih_case_hash_table_t *hash_table) {
  pthread_mutex_unlock(&hash_table->mutex);
}

node_t *node_create(void *object, node_t *previous, node_t *next,
    ih_case_hash_table_t *hash_table)
{
  assert(object);
  node_t *node;

  node = malloc(sizeof *node);
  if (node) {
    node->object = object;
    node->next = next;
    hash_table->size++;
  } else {
    ih_core_trace("malloc");
  }

  return node;
}

void node_destroy(node_t *node, ih_case_hash_table_t *hash_table)
{
  assert(node);
  assert(hash_table);

  if (hash_table->iobject->destroy) {
    hash_table->iobject->destroy(node->object);
  }
  free(node);
  hash_table->size--;
}
