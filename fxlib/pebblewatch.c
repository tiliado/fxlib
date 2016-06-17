#include "fxlib/pebblewatch.h"

char* fx_get_pebble_platform()
{
	#ifdef FXLIB_PEBBLE
	return (FXLIB_PEBBLE);
	#else
	return NULL;
	#endif
}
 
