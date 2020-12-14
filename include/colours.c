#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
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

void warn(const char *string, ...)
{
    va_list args;
    va_start(args, string);
    printf("%s", MAG);
    printf("WARNING: ");
    printf(CLR_RESET);
    vprintf(string, args);
    va_end(args);
}
void error(const char *string, ...)
{
    va_list args;
    va_start(args, string);
    printf("%s", RED);
    printf("ERROR:   ");
    printf(CLR_RESET);
    vprintf(string, args);
    va_end(args);
    exit(1);
}
