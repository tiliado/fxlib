#ifndef __FXLIB_STRFMT_H__
#define __FXLIB_STRFMT_H__

#include <stdarg.h>

char* fxstrfmt(char* format, ...);
#ifndef FXLIB_PEBBLE
void fxprintf(char* format, ...);
#endif
char* fxstrfmtva(char* format, va_list args);

#endif // __FXLIB_STRFMT_H__
