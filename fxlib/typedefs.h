#ifndef __FXLIB_TYPEDEFS_H__
#define __FXLIB_TYPEDEFS_H__

#include <stdlib.h>
#include <stdbool.h> // bool type
#include <stdint.h> // integer types

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef signed char int8;
typedef unsigned char uint8;
typedef char* string;
typedef void* ptr_t;

typedef void (fx_free_func)(ptr_t data);
typedef uint (fx_hash_func)(ptr_t value);
typedef bool (fx_equal_func)(ptr_t value1, ptr_t value2);

#endif // __FXLIB_TYPEDEFS_H__
