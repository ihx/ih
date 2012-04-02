#ifndef ih_psql_result_h
#define ih_psql_result_h

#include "ih/case/map.h"
#include "ih/core/iobject.h"
#include "ih/core/standard.h"
#include "ih/psql/result_error.h"

struct ih_psql_result_t;
typedef struct ih_psql_result_t ih_psql_result_t;

ih_psql_result_t *ih_psql_result_create(PGresult *pg_result,
    ih_core_iobject_t *string_iobject, ih_psql_result_create_error_t *error);

void ih_psql_result_destroy(ih_psql_result_t *result);

ih_case_map_t *ih_psql_result_get_row(ih_psql_result_t *result,
    unsigned long row_index);

unsigned long ih_psql_result_get_row_count(ih_psql_result_t *result);

ih_case_map_t *ih_psql_result_iterate_next(ih_psql_result_t *result);

void ih_psql_result_iterate_start(ih_psql_result_t *result);

#endif
