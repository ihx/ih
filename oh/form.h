#ifndef ih_oh_form_h
#define ih_oh_form_h

enum ih_oh_form_t {
  ih_oh_form_fluid = 0,
  ih_oh_form_description = 1,
};
typedef enum ih_oh_form_t ih_oh_form_t;

#define IH_OH_FORM_COUNT 2

const char *ih_oh_form[IH_OH_FORM_COUNT][2];

#endif
