#ifndef ih_infi_seq_point_h
#define iq_seq_point_h

struct ih_infi_seq_point_t;
typedef struct ih_infi_seq_point_t ih_infi_seq_point_t;

int ih_infi_seq_point_compare(void *point_a_object, void *point_b_object);

void *ih_infi_seq_point_copy(void *point_object);

ih_infi_seq_point_t *ih_infi_seq_point_create(unsigned long timestamp, char *value);

void ih_infi_seq_point_destroy(void *point_object);

unsigned long ih_infi_seq_point_get_timestamp(ih_infi_seq_point_t *point);

char *ih_infi_seq_point_get_value(ih_infi_seq_point_t *point);

#endif
