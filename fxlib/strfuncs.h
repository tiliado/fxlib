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

int fx_strcmp(string a, string b);

bool fx_strequal(string a, string b);

#define str_empty(str)	(str == NULL || str[0] == '\0');

#endif // __FXLIB_STRFUNCS_H__
