#ifndef ih_inferno_box_coordinate_h
#define ih_inferno_box_coordinate_h

struct ih_inferno_box_coordinate_t {
  unsigned short x;
  unsigned short y;
  unsigned short z;
};
typedef struct ih_inferno_box_coordinate_t ih_inferno_box_coordinate_t;

void ih_inferno_box_coordinate_copy(ih_inferno_box_coordinate_t *destination,
    ih_inferno_box_coordinate_t *source);

void ih_inferno_box_coordinate_free(ih_inferno_box_coordinate_t *coordinate);

void ih_inferno_box_coordinate_init_with_coordinate(ih_inferno_box_coordinate_t *coordinate,
    ih_inferno_box_coordinate_t *initial_coordinate);

void ih_inferno_box_coordinate_init_with_random(ih_inferno_box_coordinate_t *coordinate,
    ih_inferno_box_coordinate_t *dimension_coordinate);

void ih_inferno_box_coordinate_init_with_xyz(ih_inferno_box_coordinate_t *coordinate,
    unsigned short x, unsigned short y, unsigned short z);

#endif
