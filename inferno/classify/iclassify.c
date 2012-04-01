#include "ih/inferno/classify/iclassify.h"
#include "ih/core/tools.h"

void ih_inferno_classify_iclassify_free
(ih_inferno_classify_iclassify_t *iclassify) {}

void ih_inferno_classify_iclassify_init
(ih_inferno_classify_iclassify_t *iclassify,
    ih_inferno_classify_iclassify_create_f create,
    ih_inferno_classify_iclassify_destroy_f destroy,
    ih_inferno_classify_iclassify_classify_object_f classify_object,
    ih_inferno_classify_iclassify_learn_f learn,
    ih_inferno_classify_iclassify_observe_object_f observe_object)
{
  assert(iclassify);
  assert(create);
  assert(destroy);
  assert(classify_object);
  assert(learn);
  assert(observe_object);

  iclassify->create = create;
  iclassify->destroy = destroy;
  iclassify->classify_object = classify_object;
  iclassify->learn = learn;
  iclassify->observe_object = observe_object;
}
