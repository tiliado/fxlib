#ifndef __FXLIB_HT_H__
#define __FXLIB_HT_H__

#include "fxlib/typedefs.h"

typedef struct fxht_t fxht_t;

/**
 * Hash function for pointers.
 * 
 * @param pointer [unowned]    pointer to hash
 * @return hash of the pointer
 */
uint fxht_hash_pointer(ptr_t pointer);

/**
 * Hash function for strings.
 * 
 * @param pointer [unowned]    string to hash
 * @return hash of the string
 */
uint fxht_hash_string(string str);

/**
 * Test whether pointers equal.
 * 
 * @param value1 [unowned]    the first pointer
 * @param value2 [unowned]    the second pointer
 * @return true if pointers equal, false otherwise
 */
bool fxht_equal_pointer(ptr_t value1, ptr_t value2);

/**
 * Creates new hash table.
 * 
 * 
 * @param hash_func                  hash function for hash table keys
 * @param equal_func                 equality function for hash table keys
 * @param free_key_func [nullable]   function to free hash table keys
 * @param free_key_func [nullable]   function to free hash table values
 * @return [fx_ref] new hash table
 */
fxht_t* fxht_new(
	fx_hash_func hash_func, fx_equal_func equal_func,
	fx_free_func free_key_func, fx_free_func free_value_func);

/**
 * Gets value for key in hash table.
 * 
 * @param table [unowned]    hash table
 * @param key [unowned]      the key to look up
 * @return [unowned, null] value for given key or null if not found
 */
ptr_t fxht_get(fxht_t* table, ptr_t key);

/**
 * Sets value for key in hash table.
 * 
 * @param table [unowned]    hash table
 * @param key [owned]        the hastable key
 * @param value [owned]      the value for the key
 * @return true on success, false on failure (memory allocation)
 */
bool fxht_set(fxht_t* table, ptr_t key, ptr_t value);

/**
 * Removes key from hash table.
 * 
 * @param table [unowned]    hash table
 * @param key [unowned]      the hash table key
 * @return true on success, false if the key doesn't exist
 */
bool fxht_remove(fxht_t* table, ptr_t key);

/**
 * Removes all entries in hash table.
 * 
 * @param table [unowned]    hash table
 */
void fxht_clear(fxht_t* table);

#endif // __FXLIB_HT_H__
