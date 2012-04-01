#ifndef ih_inferno_ccsv_system_h
#define ih_inferno_ccsv_system_h

struct ih_inferno_ccsv_system_t;
typedef struct ih_inferno_ccsv_system_t ih_inferno_ccsv_system_t;

ih_inferno_ccsv_system_t *ih_inferno_ccsv_system_create();

void ih_inferno_ccsv_system_destroy(void *system_void);

#endif
