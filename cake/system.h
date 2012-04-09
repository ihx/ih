#ifndef ih_cake_system_h
#define ih_cake_system_h

struct ih_cake_system_t;
typedef struct ih_cake_system_t ih_cake_system_t;

ih_core_bit_t ih_cake_system
ih_cake_system_t *ih_cake_system_create(unsigned char rule, uint32_t input);
void ih_cake_system_destroy(ih_cake_system_t *system);

#endif
