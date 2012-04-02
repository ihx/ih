#ifndef ih_chage_system_h
#define ih_chage_system_h

struct ih_chage_system_t;
typedef struct ih_chage_system_t ih_chage_system_t;

ih_chage_system_t *ih_chage_system_create();

void ih_chage_system_destroy(ih_chage_system_t *system);

void ih_chage_system_spark(ih_chage_system_t *system);

#endif
