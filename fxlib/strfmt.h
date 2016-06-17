#ifndef __FXLIB_STRFMT_H__
#define __FXLIB_STRFMT_H__

#include <stdarg.h>

char* fxstrfmt(char* format, ...);
void fxprintf(char* format, ...);
char* fxstrfmtva(char* format, va_list args);

#endif // __FXLIB_STRFMT_H__
