#ifndef ih_inferno_computer_system_h
#define ih_inferno_computer_system_h

#include "ih/inferno/computer/output.h"

struct ih_inferno_computer_system_t;
typedef struct ih_inferno_computer_system_t ih_inferno_computer_system_t;

typedef void (*ih_inferno_computer_logic_f)(unsigned long input,
    ih_inferno_computer_output_t *output);

ih_inferno_computer_output_t *ih_inferno_computer_system_compute
(ih_inferno_computer_system_t *system, unsigned long input);

ih_inferno_computer_system_t *ih_inferno_computer_system_create
(unsigned long order, ih_inferno_computer_logic_f logic);

ih_inferno_computer_system_t *ih_inferno_computer_system_create_from_file
(char *filename);

void ih_inferno_computer_system_destroy(void *system_object);

char *ih_inferno_computer_system_get_as_string(void *system_object);

void ih_inferno_computer_system_print(ih_inferno_computer_system_t *system);

ih_core_bool_t ih_inferno_computer_system_save_as_file
(ih_inferno_computer_system_t *system, char *filename);

#endif
