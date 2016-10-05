#include <string.h>
#include <stdarg.h>
#include "fxlib/macros.h"
#include "fxlib/strfuncs.h"

string fx_substr(string source, int offset, int length)
{
	int size = strlen(source);
	if (offset < 0 || offset + length > size)
		return NULL;
	string dest = fx_alloc(length + 1, char);
	strncpy(dest, source + offset, length);
	dest[length] = '\0';
	return dest;
}

string fx_strdup(string source)
{
	if (source == NULL)
		return NULL;
	int size = strlen(source);
	string dest = fx_alloc(size + 1, char);
	strncpy(dest, source, size);
	dest[size] = '\0';
	return dest;
}

string fx_strcat(string str1, string str2)
{
	int size1 = strlen(str1);
	int size2 = strlen(str2);
	int size = size1 + size2;
	string dest = fx_alloc(size + 1, char);
	strcpy(dest, str1);
	strcpy(dest + size1, str2);
	dest[size] = '\0';
	return dest;
}

string fx_strjoin(string delim, string* array, int size)
{
	int delim_len = delim != NULL ? strlen(delim) : 0;
	int* lengths = fx_alloc(size, int);
	int total_length = 0;
	for (int i = 0; i < size; i++)
	{
		lengths[i] = strlen(array[i]);
		total_length += lengths[i];
	}
	if (delim_len > 0)
		total_length += (size - 1) * delim_len;
	
	string dest = fx_alloc(total_length + 1, char);
	int offset = 0;
	for (int i = 0; i < size; i++)
	{
		strcpy(dest + offset, array[i]);
		offset += lengths[i];
		if (delim_len && i < size - 1)
		{
			strcpy(dest + offset, delim);
			offset += delim_len;
		}
	}
	dest[total_length] = '\0';
	free(lengths);
	return dest;
}

string fx_strcatn(int n, ...)
{
	va_list va;
	va_start(va, n);
	string* array = fx_alloc(n, string);
	for (int i = 0; i < n; i++)
		array[i] = va_arg(va, string);
	string result = fx_strjoin(NULL, array, n);
	free(array);
	va_end(va);
	return result;
}
