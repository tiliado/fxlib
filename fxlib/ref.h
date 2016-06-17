#ifndef __FXLIB_REF_H__
#define __FXLIB_REF_H__

#include "fxlib/typedefs.h"


ptr_t fx_ref_new(size_t size, fx_free_func* free_func);
#define fx_new(type, free_func)    ((type*) fx_ref_new(sizeof(type), free_func))
ptr_t fx_ref(ptr_t data);
ptr_t fx_unref(ptr_t data);
uint fx_ref_count(ptr_t data);

#endif // __FXLIB_REF_H__d
