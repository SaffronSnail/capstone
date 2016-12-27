#include "entrance-protocol.h"
#include "entrance-response.h"

#include <string.h>

int test(int ret)
{
  EntranceResponse er;
  memset(&er, 0, sizeof(er));
  er.port = ret;
  return get_port(&er);
}


