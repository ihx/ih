#include "ih/core/standard.h"
#include "ih/net/engine/iengine.h"

void ih_net_engine_iengine_init(ih_net_engine_iengine_t *iengine,
    ih_net_engine_iengine_create_f create,
    ih_net_engine_iengine_destroy_f destroy,
    ih_net_engine_iengine_get_handler_for_message_f get_handler_for_message,
    ih_net_engine_iengine_maintain_f maintain,
    ih_net_engine_iengine_run_f run, ih_net_engine_iengine_start_f start,
    ih_net_engine_iengine_stop_f stop)
{
  assert(iengine);

  iengine->create = create;
  iengine->destroy = destroy;
  iengine->get_handler_for_message = get_handler_for_message;
  iengine->maintain = maintain;
  iengine->run = run;
  iengine->start = start;
  iengine->stop = stop;
}
