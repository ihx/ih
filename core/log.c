#include "ih/core/log.h"
#include "ih/case/set.h"
#include "ih/core/basic/unsigned_long.h"

#define MAX_ENTRY_SIZE 1024
#define MAX_LINE_LENGTH 79
#define SPACE_CUTOFF 64
#define SPACE_CHAR ' '

struct ih_core_log_t {
  ih_case_set_t *files;
  pthread_mutex_t mutex;
  ih_core_iobject_t files_iobject;
};

static int compare_files(void *a_file_object, void *b_file_object);

static ih_core_bool_t enter_file(char *formatted_entry, FILE *file);

static unsigned short find_line_end(char *entry,
    unsigned short max_line_length);

static char *format_entry(char *entry);

static ih_core_bool_t write_entry_to_all_files(ih_core_log_t *log,
    char *formatted_entry);

int compare_files(void *a_file_object, void *b_file_object)
{
  assert(a_file_object);
  assert(b_file_object);
  int compare_result;
  FILE *a_file;
  FILE *b_file;

  a_file = a_file_object;
  b_file = b_file_object;

  if (a_file < b_file) {
    compare_result = -1;
  } else if (a_file > b_file) {
    compare_result = 1;
  } else {
    compare_result = 0;
  }

  return compare_result;
}

ih_core_bool_t ih_core_log_add_file(ih_core_log_t *log, FILE *file)
{
  assert(log);
  assert(file);
  ih_core_bool_t success;

  pthread_mutex_lock(&log->mutex);
  success = ih_case_set_add(log->files, file);
  pthread_mutex_unlock(&log->mutex);

  return success;
}

ih_core_log_t *ih_core_log_create(FILE *file)
{
  ih_core_log_t *log;
  ih_core_bool_t so_far_so_good;

  log = malloc(sizeof *log);
  if (log) {
    so_far_so_good = ih_core_bool_true;
  } else {
    ih_core_trace("malloc");
    so_far_so_good = ih_core_bool_false;
  }

  if (so_far_so_good) {
    ih_core_iobject_init(&log->files_iobject, compare_files,
        ih_core_basic_unsigned_long_compare_equal,
        IH_CORE_OBJECT_NO_COPY_F, IH_CORE_OBJECT_NO_DESTROY_F,
        IH_CORE_OBJECT_NO_GET_AS_STRING_F,
        ih_core_basic_unsigned_long_mod);
    log->files = ih_case_set_create(&log->files_iobject);
    if (log->files) {
      if (file) {
        if (ih_case_set_add(log->files, file)) {
          so_far_so_good = ih_core_bool_true;
        } else {
          so_far_so_good = ih_core_bool_false;
        }
      } else {
        so_far_so_good = ih_core_bool_true;
      }
    } else {
      so_far_so_good = ih_core_bool_false;
    }
  }

  if (so_far_so_good) {
    if (0 != pthread_mutex_init(&log->mutex, NULL)) {
      so_far_so_good = ih_core_bool_false;
    }
  }

  if (!so_far_so_good && log) {
    if (log->files) {
      ih_case_set_destroy(log->files);
    }
  }

  assert(!log || (log->files));
  return log;
}

void ih_core_log_destroy(ih_core_log_t *log)
{
  assert(log);

  ih_case_set_destroy(log->files);
  pthread_mutex_destroy(&log->mutex);
  free(log);
}

ih_core_bool_t ih_core_log_enter(ih_core_log_t *log, const char *system,
    const char *entry, ...)
{
  assert(log);
  assert(system);
  assert(entry);
  char *timed_entry;
  char interpolated_entry[MAX_ENTRY_SIZE];
  char *formatted_entry;
  va_list ap;
  ih_core_bool_t success;
  ih_core_time_string_t time_string;

  success = ih_core_bool_false;

  if (ih_core_get_current_time_string(time_string)) {
    if (asprintf(&timed_entry, "%s [%4s]   %s", time_string, system, entry)
        != -1) {
      va_start(ap, entry);
      if (vsnprintf(interpolated_entry, MAX_ENTRY_SIZE, timed_entry, ap)
          != -1) {
        formatted_entry = format_entry(interpolated_entry);
        if (formatted_entry) {
          if (write_entry_to_all_files(log, formatted_entry)) {
            success = ih_core_bool_true;
          } else {
            ih_core_trace("write_entry_to_all_files");
          }
          free(formatted_entry);
        } else {
          ih_core_trace("format_entry");
        }
      } else {
        ih_core_trace("asprintf");
      }
      free(timed_entry);
    } else {
      ih_core_trace("asprintf");
    }
  } else {
    ih_core_trace("x_core_get_current_time_string");
  }

  return success;
}

ih_core_bool_t ih_core_log_remove_file(ih_core_log_t *log, FILE *file)
{
  assert(log);
  assert(file);
  ih_core_bool_t success;

  pthread_mutex_lock(&log->mutex);
  success = ih_case_set_remove(log->files, file);
  pthread_mutex_unlock(&log->mutex);

  return success;
}

ih_core_bool_t _x_audit_log_trace(ih_core_log_t *log, const char *system,
    const char *entry, const char *file, unsigned long line, ...)
{
  assert(log);
  assert(system);
  assert(entry);
  assert(file);
  char *traced_entry;
  char interpolated_entry[MAX_ENTRY_SIZE];
  char *formatted_entry;
  va_list ap;
  ih_core_bool_t success;
  ih_core_time_string_t time_string;

  success = ih_core_bool_false;

  if (ih_core_get_current_time_string(time_string)) {
    if (asprintf(&traced_entry, "%s [%4s] X %s() in %s:%lu", time_string,
            system, entry, file, line) != -1) {
      va_start(ap, line);
      if (vsnprintf(interpolated_entry, MAX_ENTRY_SIZE, traced_entry, ap)
          != -1) {
        formatted_entry = format_entry(interpolated_entry);
        if (formatted_entry) {
          if (write_entry_to_all_files(log, formatted_entry)) {
            success = ih_core_bool_true;
          } else {
            ih_core_trace("write_entry_to_all_files");
          }
          free(formatted_entry);
        } else {
          ih_core_trace("format_entry");
        }
      } else {
        ih_core_trace("asprintf");
      }
      va_end(ap);
      free(traced_entry);
    } else {
      ih_core_trace("asprintf");
    }
  } else {
    ih_core_trace("x_core_get_current_time_string");
  }

  return success;
}

ih_core_bool_t enter_file(char *formatted_entry, FILE *file)
{
  assert(formatted_entry);
  assert(file);
  ih_core_bool_t success;

  if (fprintf(file, "%s", formatted_entry) >= 0) {
    if (0 == fflush(file)) {
      success = ih_core_bool_true;
    } else {
      success = ih_core_bool_false;
      ih_core_trace("fflush");
    }
  } else {
    success = ih_core_bool_false;
    ih_core_trace("fprintf");
  }

  return success;
}

unsigned short find_line_end(char *entry, unsigned short max_line_length)
{
  /*
    TODO (rainy day): make this support other whitespace chars
  */

  assert(entry);
  unsigned short line_end;
  unsigned long entry_size;

  entry_size = strlen(entry);
  if (entry_size <= max_line_length) {
    line_end = entry_size;
  } else {
    line_end = max_line_length - 1;
    while (line_end > SPACE_CUTOFF && (*(entry + line_end) != SPACE_CHAR)) {
      line_end--;
    }
    if (*(entry + line_end) != SPACE_CHAR) {
      line_end = max_line_length;
    } else {
      line_end++;
    }
  }

  return line_end;
}

/*
  TODO: test return codes
*/
char *format_entry(char *entry)
{
  assert(entry);
  char *formatted_entry;
  unsigned short line_end;
  char *entry_start;

  formatted_entry = NULL;
  entry_start = entry;

  line_end = find_line_end(entry_start, MAX_LINE_LENGTH);
  while (line_end > 0) {
    formatted_entry = ih_core_string_append_n(formatted_entry,
        entry_start, line_end);
    formatted_entry = ih_core_string_append_char(formatted_entry, '\n');
    entry_start += line_end;
    line_end = find_line_end(entry_start, MAX_LINE_LENGTH
        - (IH_CORE_TIME_STRING_LENGTH + 1 + 1 + 4 + 1 + 3));
    if (line_end > 0) {
      formatted_entry = ih_core_string_append
        (formatted_entry, "                         ");
    }
  }

  return formatted_entry;
}

ih_core_bool_t write_entry_to_all_files(ih_core_log_t *log,
    char *formatted_entry)
{
  assert(log);
  assert(formatted_entry);
  ih_core_bool_t success;
  FILE *file;

  success = ih_core_bool_true;

  pthread_mutex_lock(&log->mutex);
  {
    ih_case_set_iterate_start(log->files);
    while ((file = ih_case_set_iterate_next(log->files))) {
      if (!enter_file(formatted_entry, file)) {
        ih_core_trace("enter_file");
        success = ih_core_bool_false;
      }
    }
  }
  pthread_mutex_unlock(&log->mutex);

  return success;
}
