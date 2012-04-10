#ifndef ih_tools_h
#define ih_tools_h

#define ih_tools_get_bit(value, bit_index) ((value >> bit_index) & 1)

#define ih_tools_set_bit(value, bit_index, bit_value) \
  if (bit_value) { *value |= (1 << bit_index); }      \
  else { *value &= ~(1 << bit_index); }

#define ih_tools_trace(message) fprintf(stderr, message "() in %s:%d\n", \
      __FILE__, __LINE__)

#define ih_tools_trace_exit(message) fprintf(stderr, message"() in %s:%d\n", \
      __FILE__, __LINE__); exit(17);

#endif
