#ifndef ih_inferno_mind_system_h
#define ih_inferno_mind_system_h

struct ih_inferno_mind_system_t;
typedef struct ih_inferno_mind_system_t ih_inferno_mind_system_t;

ih_inferno_mind_system_t *ih_inferno_mind_system_create();

void ih_inferno_mind_system_destroy(ih_inferno_mind_system_t *system);

#endif
