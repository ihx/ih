#include "ih/core/uuid.h"

/*
ih_core_bool_t ih_core_uuid_compare_equal(void *uuid_a_object, void *uuid_b_object)
{
  assert(uuid_a_object);
  assert(uuid_b_object);
  unsigned char *uuid_a = uuid_a_object;
  unsigned char *uuid_b = uuid_b_object;
  ih_core_bool_t equal = ih_core_bool_true;
  unsigned char i;

  for (i = 0; i < 16; i++) {
    if (*(uuid_a + i) != *(uuid_b + i)) {
      equal = ih_core_bool_false;
      break;
    }
  }

  return equal;
}
*/

unsigned long ih_core_uuid_hash(void *uuid_object, unsigned long divisor)
{
  assert(uuid_object);
  unsigned char *uuid = uuid_object;
  unsigned long dividend;
  unsigned long remainder;

  dividend = *((unsigned long *) (uuid + 12));
  remainder = dividend % divisor;
  /*  printf("%lu::%lu\n", dividend, remainder);  */

  return remainder;
}
