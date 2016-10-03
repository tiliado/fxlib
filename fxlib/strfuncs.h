#ifndef __FXLIB_STRFUNCS_H__
#define __FXLIB_STRFUNCS_H__

#include <stdarg.h>
#include <string.h>
#include "fxlib/typedefs.h"

string fx_substr(string source, int offset, int length);

string fx_strdup(string source);

string fx_strcat(string str1, string str2);

string fx_strjoin(string delim, string* array, int size);

string fx_strcatn(int n, ...);

#endif // __FXLIB_STRFUNCS_H__
