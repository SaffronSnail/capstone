#include "utils.h"

#include <stdio.h>

static const unsigned radix = 10;
char *utoa_aux(unsigned input, char *place)
{
  if (input < radix)
    *place = input + '0';
  else
  {
    int next_part = input / radix;
    place = utoa_aux(next_part, place);
    *place = (input - (next_part * radix)) + '0';
  }

  return place + 1;
}

void utoa(unsigned input, char *buffer)
{
  utoa_aux(input, buffer);
}

