#include "rsa.h"
#include <string.h>

int 	index(char character, char *buf)
{
	int i;
	int n;
#ifndef	ORIGINAL_CODE
	if (!buf)
		return -1;
#endif
	if (!(n = strlen(buf)))
		return -1;
	
	for (i=0; i < n; i ++)
		if (buf[i] == character)			
			return i;
	return -1;
}
