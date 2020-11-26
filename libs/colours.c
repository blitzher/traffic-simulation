#include <stdio.h>
#include <stdarg.h>
#include "colours.h"

void c_printf(const char *string, char clr[8], ...)
{
    va_list args;
    va_start(args, clr);
    printf("%s", clr);
    vprintf(string, args);
    printf(CLR_RESET);
    va_end(args);
}
