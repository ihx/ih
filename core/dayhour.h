#ifndef ih_core_dayhour_h
#define ih_core_dayhour_h

struct ih_core_dayhour_t {
  unsigned short days;
  unsigned short hours;
  unsigned short minutes;
  unsigned short seconds;
};
typedef struct ih_core_dayhour_t ih_core_dayhour_t;

char *create_string_from_dayhour(ih_core_dayhour_t *dayhour);

#endif
