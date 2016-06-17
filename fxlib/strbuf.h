#ifndef __FXLIB_STRBUF_H__
#define __FXLIB_STRBUF_H__

#include "fxlib/typedefs.h"
#include "fxlib/ref.h"

typedef struct fxstrbuf fxstrbuf_t;

fxstrbuf_t* fxstrbuf_new(size_t size);
void fxstrbuf_reset(fxstrbuf_t* buf, size_t size);
void fxstrbuf_extend(fxstrbuf_t* buf, uint increment);
void fxstrbuf_append_c(fxstrbuf_t* buf, char value);
void fxstrbuf_append(fxstrbuf_t* buf, char* value);
void fxstrbuf_append_int(fxstrbuf_t* buf, int value);
void fxstrbuf_append_uint(fxstrbuf_t* buf, uint value);
void fxstrbuf_append_double(fxstrbuf_t* buf, double value, int precision);
void fxstrbuf_append_bool(fxstrbuf_t* buf, bool value);
int fxstrbuf_offset(fxstrbuf_t* buf);
size_t fxstrbuf_size(fxstrbuf_t* buf);
char* fxstrbuf_peek(fxstrbuf_t* buf);
char* fxstrbuf_end(fxstrbuf_t* buf);

#endif // __FXLIB_STRBUF_H__
