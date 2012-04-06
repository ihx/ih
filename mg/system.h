#ifndef ih_mg_system_h
#define ih_mg_system_h

struct ih_mg_system_t;
typedef struct ih_mg_system_t ih_mg_system_t;

typedef double (*ih_mg_calculate_fitness_f)(uint32_t genome);

ih_mg_system_t *ih_mg_system_create
(ih_mg_calculate_fitness_f calculate_fitness);

void ih_mg_system_destroy(ih_mg_system_t *system);

uint32_t ih_mg_system_generate(ih_mg_system_t *system);

#endif
