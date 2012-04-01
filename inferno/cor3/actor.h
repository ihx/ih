#ifndef ih_inferno_cor3_actor_h
#define ih_inferno_cor3_actor_h

#include "ih/inferno/cor3/tools.h"
#include "ih/inferno/core/iactor.h"

void ih_inferno_cor3_actor_act(ih_inferno_cor3_actor_t *actor);

int ih_inferno_cor3_actor_compare_maximize(void *actor_a_void, void *actor_b_void);

int ih_inferno_cor3_actor_compare_minimize(void *actor_a_void, void *actor_b_void);

void *ih_inferno_cor3_actor_copy(void *actor_void);

void *ih_inferno_cor3_actor_create(void *system_void, ih_core_bitarray_t *solution);

void *ih_inferno_cor3_actor_create_random(void *system_void);

void ih_inferno_cor3_actor_destroy(void *actor_void);

void *ih_inferno_cor3_actor_get_box_cell(void *actor_void);

ih_core_bitarray_t *ih_inferno_cor3_actor_get_solution(void *actor_void);

void ih_inferno_cor3_actor_init_iactor(ih_inferno_core_iactor_t *iactor);

void ih_inferno_cor3_actor_set_box_cell(void *actor_void, void *box_cell);

#endif
