#ifndef ih_chage_tools_h
#define ih_chage_tools_h

#define IH_CHAGE_CONTAINED_ATOMS 256
#define IH_CHAGE_INTERVAL_MICROSECONDS (1000000.0 / 24)
#define IH_CHAGE_INTERVAL_VOID 255

typedef unsigned char ih_chage_distance_t;
typedef unsigned char ih_chage_interval_t;
typedef unsigned char ih_chage_scale_t;

ih_chage_interval_t ih_chage_determine_interval();

#endif
