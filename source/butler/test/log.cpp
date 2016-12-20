#include "log.h"

#include <stdarg.h>
#include <stdio.h>

void log(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  fprintf(stderr, "\n");
}

