#ifndef ih_core_scratch_h
#define ih_core_scratch_h

struct ih_core_scratch_t;
typedef struct ih_core_scratch_t ih_core_scratch_t;

ih_core_scratch_t *ih_core_scratch_create();

void ih_core_scratch_destroy(ih_core_scratch_t *ih_core_scratch);

#endif
