#ifndef __FXLIB_MACROS_H__
#define __FXLIB_MACROS_H__

#include <stdio.h>  // perror
#include "fxlib/typedefs.h"

#ifdef __x86_64__
#define pointer_to_uint(pointer) ((uint) (ulong) pointer)
#else
#define pointer_to_uint(pointer) ((uint) pointer)
#endif

#define fx_malloc(type) ((type*) malloc(sizeof(type)))
#define fx_alloc(n, type) ((type*) malloc((n) * sizeof(type)))
#define fx_calloc(n, type) ((type*) calloc((n), sizeof(type)))

#define fx_return_if_fail(expr)    do{ if (!(expr)) {perror("*** " __FILE__ ":" ": Expression " #expr " failed.\n"); return;}} while(0)
#define fx_return_if_null(expr)    do{ if ((expr) == NULL) {perror("*** " __FILE__ ":" ": Expression " #expr " is NULL.\n"); return;}} while(0)
#define fx_return_val_if_fail(expr, val)    do{ if (!(expr)) {perror("*** " __FILE__ ":"  ": Expression " #expr " failed.\n"); return (val);}} while(0)
#define fx_return_val_if_null(expr, val)    do{ if ((expr) == NULL) {perror("*** " __FILE__ ":"  ": Expression " #expr "  is NULL.\n"); return (val);}} while(0)
#define fx_return_null_if_null(expr)    do{ if ((expr) == NULL) {perror("*** " __FILE__ ":"  ": Expression " #expr " is NULL.\n"); return NULL;}} while(0)

#endif // __FXLIB_MACROS_H__
