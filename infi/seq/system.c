#include "ih/case/set.h"
#include "ih/core/standard.h"
#include "ih/core/tools.h"
#include "ih/infi/seq/system.h"

struct ih_infi_seq_system_t {
  ih_case_set_t *sequences;
  ih_core_log_t *log;
};

ih_core_bool_t ih_infi_seq_system_add_sequence(ih_infi_seq_system_t *system,
    char *subject, ih_infi_seq_sequence_get_data_f get_data)
{
  assert(system);
  assert(subject);
  assert(get_data);
  ih_infi_seq_sequence_t *sequence;
  ih_core_bool_t success = ih_core_bool_false;

  sequence = ih_infi_seq_sequence_create(subject, get_data);
  if (sequence) {
    ih_case_set_lock(system->sequences);
    if (!ih_case_set_find(system->sequences, sequence)) {
      if (ih_case_set_add(system->sequences, sequence)) {
        success = ih_core_bool_true;
      } else {
        ih_core_trace("ih_case_set_add");
      }
    } else {
      ih_core_log_trace(system->log, "seqx",
          "seq system already contains sequence %s", subject);
    }
    ih_case_set_unlock(system->sequences);
  } else {
    ih_core_trace("ih_infi_seq_sequence_create");
  }

  if (!success && sequence) {
    ih_infi_seq_sequence_destroy(sequence);
  }

  return success;
}

ih_infi_seq_system_t *ih_infi_seq_system_create(ih_core_log_t *log)
{
  ih_infi_seq_system_t *system;

  system = malloc(sizeof *system);
  if (system) {
    system->log = log;
  } else {
    ih_core_trace("malloc");
  }

  return system;
}

void ih_infi_seq_system_destroy(ih_infi_seq_system_t *system)
{
  free(system);
}

ih_case_list_t *ih_infi_seq_system_get_last_n(ih_infi_seq_system_t *system,
    char *subject, unsigned long n)
{
  return NULL;
}

ih_case_list_t *ih_infi_seq_system_get_since_timestamp
(ih_infi_seq_system_t *system, char *subject, unsigned long timestamp)
{
  return NULL;
}
