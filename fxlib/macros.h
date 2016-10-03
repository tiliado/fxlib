#ifndef __FXLIB_MACROS_H__
#define __FXLIB_MACROS_H__

#include "fxlib/pebblewatch.h"
#include "fxlib/typedefs.h"

#ifdef __x86_64__
#define pointer_to_uint(pointer) ((uint) (ulong) pointer)
#else
#define pointer_to_uint(pointer) ((uint) pointer)
#endif

#ifndef FXLIB_PEBBLE
#include <stdio.h>  // fprintf, fputs
#define fx_debug(filename, line, format, ...)                                                     \
	fprintf(stderr, "*** Debug *** %s:%d: ", filename, line);                                     \
	fprintf(stderr, format, ##__VA_ARGS__);                                                       \
	fputs(stderr, "\n");
#define fx_log_err(filename, line, format, ...)                                                   \
	fprintf(stderr, "*** Error *** %s:%d: ", filename, line);                                     \
	fprintf(stderr, format, ##__VA_ARGS__);                                                       \
	fputs(stderr, "\n");
#else
#define fx_debug(filename, line, format, ...)                                                     \
  app_log(APP_LOG_LEVEL_DEBUG, filename, line, format, ##__VA_ARGS__)
#define fx_log_err(filename, line, format, ...)                                                   \
  app_log(APP_LOG_LEVEL_ERROR, filename, line, format, ##__VA_ARGS__)
#endif

#define FX_DEBUG(format, ...)   fx_debug(__FILE__, __LINE__, format, ##__VA_ARGS__)  

#define fx_malloc(type) ((type*) malloc(sizeof(type)))
#define fx_alloc(n, type) ((type*) malloc((n) * sizeof(type)))
#define fx_calloc(n, type) ((type*) calloc((n), sizeof(type)))

#define fx_return_if_fail(expr)                                                                   \
	do{ if (!(expr)) {fx_log_err(__FILE__, __LINE__, "Expression %s failed.", #expr); return;}} while(0)
#define fx_return_if_null(expr)                                                                   \
	do{ if ((expr) == NULL) {fx_log_err(__FILE__, __LINE__, "Expression %s is NULL.", #expr); return;}} while(0)
#define fx_return_val_if_fail(expr, val)                                                          \
	do{ if (!(expr)) {fx_log_err(__FILE__, __LINE__, "Expression %s failed.", #expr); return (val);}} while(0)
#define fx_return_val_if_null(expr, val)                                                          \
	do{ if ((expr) == NULL) {fx_log_err(__FILE__, __LINE__, "Expression %s  is NULL.", #expr); return (val);}} while(0)
#define fx_return_null_if_null(expr)                                                              \
    do{ if ((expr) == NULL) {fx_log_err(__FILE__, __LINE__, "Expression %s is NULL.", #expr); return NULL;}} while(0)

#endif // __FXLIB_MACROS_H__
