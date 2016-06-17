#include "fxlib/ref.h"
#include "fxlib/macros.h"

typedef struct{
  ptr_t data;
  fx_free_func* free_func;
  unsigned ref_count;
} fx_ref_t;

ptr_t fx_ref_new(size_t size, fx_free_func* free_func)
{
	fx_ref_t* ref_object;
	char* pointer;
	ref_object = (fx_ref_t*) calloc(size + sizeof(fx_ref_t), 1);
	if (ref_object == NULL)
		return NULL;
	ref_object->ref_count = 1;
	pointer = (char*) ref_object;
	pointer += sizeof(fx_ref_t);
	ref_object->data = (void*) pointer;
	ref_object->free_func = free_func;
	return (ptr_t) pointer;
}

ptr_t fx_ref(ptr_t data)
{
	fx_return_null_if_null(data);
	fx_ref_t* ref_object;
	char* pointer = (char*) data;
	pointer -= sizeof(fx_ref_t);
	ref_object = (fx_ref_t*) pointer;
	ref_object->ref_count++;
	return data;
}

ptr_t fx_unref(ptr_t data)
{
	fx_return_null_if_null(data);
	fx_ref_t* ref_object;
	char* pointer = (char*) data;
	pointer -= sizeof(fx_ref_t);
	ref_object = (fx_ref_t*) pointer;
	ref_object->ref_count--;
	if (ref_object->ref_count == 0)
	{
		if (ref_object->free_func != NULL)
			ref_object->free_func(data);
		free(ref_object);
	}
	return NULL;
}

uint fx_ref_count(ptr_t data)
{
	fx_return_val_if_null(data, 0);
	fx_ref_t* ref_object;
	char* pointer = (char*) data;
	pointer -= sizeof(fx_ref_t);
	ref_object = (fx_ref_t*) pointer;
	return ref_object->ref_count;
}
