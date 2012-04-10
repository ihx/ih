#ifndef ih_trace_h
#define ih_trace_h

#define ih_trace(message) fprintf(stderr, message "() in %s:%d\n",  \
      __FILE__, __LINE__)

#define ih_trace_exit(message) fprintf(stderr, message"() in %s:%d\n",  \
      __FILE__, __LINE__); exit(17);

#endif
