#ifndef ih_oh_iword_h
#define ih_oh_iword_h

#include "ih/oh/form.h"

typedef ih_oh_form_t (*ih_oh_iword_get_form_f)(void *form_void);

struct ih_oh_iword_t {
  ih_oh_iword_get_form_f get_form;
};
typedef struct ih_oh_iword_t ih_oh_iword_t;

#endif
