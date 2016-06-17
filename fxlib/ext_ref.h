#ifndef __FXLIB_EXT_REF_H__
#define __FXLIB_EXT_REF_H__

#include "fxlib/typedefs.h"

ptr_t fx_ext_ref_add(ptr_t data, fx_free_func* free_func);
ptr_t fx_ext_ref(ptr_t data);
ptr_t fx_ext_unref(ptr_t data);

#endif // __FXLIB_EXT_REF_H__
