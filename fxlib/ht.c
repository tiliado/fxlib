//~ #include <stdio.h>
#include "fxlib/ref.h"
#include "fxlib/ht.h"
#include "fxlib/macros.h"

typedef struct fxht_entry_t fxht_entry_t;

struct fxht_entry_t{
	fxht_entry_t* next;
	ptr_t key;
	ptr_t value;
};

#define FXHT_SIZE 64

struct fxht_t
{
	fx_hash_func* hash_func;
	fx_equal_func* equal;
	fx_free_func* free_key;
	fx_free_func* free_value;
	fxht_entry_t* entries[FXHT_SIZE];
};

static void fxht_free(fxht_t* table);
static fxht_entry_t* fxht_free_entry(fxht_t* table, fxht_entry_t* entry);

uint fxht_hash_pointer(ptr_t pointer) 
{
	return pointer_to_uint(pointer);
}

bool fxht_equal_pointer(ptr_t value1, ptr_t value2)
{
	return value1 == value2;
}

uint fxht_hash_key(fxht_t* table, ptr_t key)
{
	return table->hash_func(key) % FXHT_SIZE;
}

fxht_t* fxht_new(
	fx_hash_func hash_func, fx_equal_func equal_func,
	fx_free_func free_key_func, fx_free_func free_value_func)
{
	fxht_t* table = NULL;
	table = fx_new(fxht_t, (fx_free_func*) fxht_free);
	table->hash_func = hash_func;
	table->equal = equal_func;
	table->free_key = free_key_func;
	table->free_value = free_value_func;
	return table;
}

fxht_entry_t* fxht_get_entry(fxht_t* table, ptr_t key)
{
	fxht_entry_t* entry;
	uint key_hash;
	key_hash = fxht_hash_key(table, key);
	for (entry = table->entries[key_hash]; entry != NULL; entry = entry->next)
		if (table->equal(key, entry->key))
			return entry;
	return NULL;
}

ptr_t fxht_get(fxht_t* table, ptr_t key)
{
	fxht_entry_t* entry;
	entry = fxht_get_entry(table, key); 
	return entry != NULL ? entry->value : NULL;
}

bool fxht_set(fxht_t* table, ptr_t key, ptr_t value)
{
	fxht_entry_t* entry;
	uint key_hash;
	
	entry = fxht_get_entry(table, key);
	if (entry != NULL)
	{
		table->free_value(entry->value);
		entry->value = value;
		if (table->free_key != NULL)
			table->free_key(key);
		return true;
	}
	else
	{
		key_hash = fxht_hash_key(table, key);
		entry = fx_malloc(fxht_entry_t);
		if (entry == NULL)
			return false;
		entry->key = key;
		entry->value = value;
		entry->next = table->entries[key_hash];
		table->entries[key_hash] = entry;
		return true;
	}
}

bool fxht_remove(fxht_t* table, ptr_t key)
{
	fxht_entry_t* entry;
	fxht_entry_t* prev_entry = NULL;
	uint key_hash;
	
	key_hash = fxht_hash_key(table, key);
	for (entry = table->entries[key_hash]; entry != NULL; prev_entry = entry, entry = entry->next)
	{	if (table->equal(key, entry->key))
		{
			if (prev_entry == NULL)
				table->entries[key_hash] = entry->next;
			else
				prev_entry->next = fxht_free_entry(table, entry);
			return true;
		}
	}
	return false;
}

fxht_entry_t* fxht_free_entry(fxht_t* table, fxht_entry_t* entry)
{
	fxht_entry_t* next = NULL;
	
	if (entry != NULL)
	{
		next = entry->next;
		if (table->free_key != NULL)
		table->free_key(entry->key);
		if (table->free_value != NULL)
			table->free_value(entry->value);
		free(entry);
	}
	return next;
}

void fxht_clear(fxht_t* table)
{
	fxht_entry_t* entry;
	
	for (int i = 0; i < FXHT_SIZE; i++)
	{
		entry = table->entries[i];
		table->entries[i] = NULL;
		while (entry != NULL)
			entry = fxht_free_entry(table, entry);
	}
}

void fxht_free(fxht_t* table)
{
	fxht_clear(table);
}

