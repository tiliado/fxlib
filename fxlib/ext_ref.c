#include <assert.h>
#include "fxlib/typedefs.h"
#include "fxlib/macros.h"
#include "fxlib/ext_ref.h"
#include "fxlib/ht.h"

static fxht_t* __extern_refs = NULL;

typedef struct{
  fx_free_func* free_func;
  unsigned ref_count;
} fx_extern_ref_t;


fxht_t* fx_ext_refs_get()
{
	if (__extern_refs == NULL)
		__extern_refs = fxht_new(fxht_hash_pointer, fxht_equal_pointer, NULL, free);
	return __extern_refs;
}

ptr_t fx_ext_ref_add(ptr_t data, fx_free_func* free_func)
{
	fxht_t* refs;
	fx_extern_ref_t* extern_ref;
	refs = fx_ext_refs_get();
	extern_ref = (fx_extern_ref_t*) fxht_get(refs, data);
	if (extern_ref != NULL)
		return fx_ext_ref(data);
	extern_ref = fx_malloc(fx_extern_ref_t);
	extern_ref->ref_count = 1;
	extern_ref->free_func = free_func;
	fxht_set(refs, data, extern_ref);
	return data;
}

ptr_t fx_ext_ref(ptr_t data)
{
	fxht_t* refs;
	fx_extern_ref_t* extern_ref;
	
	refs = fx_ext_refs_get();
	extern_ref = (fx_extern_ref_t*) fxht_get(refs, data);
	assert(extern_ref != NULL && extern_ref->ref_count > 0);
	extern_ref->ref_count++;
	return data;
}

ptr_t fx_ext_unref(ptr_t data)
{
	fxht_t* refs;
	fx_extern_ref_t* extern_ref;
	refs = fx_ext_refs_get();
	extern_ref = (fx_extern_ref_t*) fxht_get(refs, data);
	assert(extern_ref != NULL && extern_ref->ref_count > 0);
	extern_ref->ref_count--;
	if (extern_ref->ref_count == 0)
	{
		if (extern_ref->free_func != NULL)
			extern_ref->free_func(data);
		fxht_remove(refs, data);
	}
	return NULL;
}
