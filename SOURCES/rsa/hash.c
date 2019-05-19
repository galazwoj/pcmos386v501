#include "rsa.h"
#include <string.h>

unsigned  hash(char *buf)
{
	int i;
 	int k;
	int len;

#ifndef	ORIGINAL_CODE
	if (!buf)
		return 1;
#endif
	
	k = 0;
	len = strlen(buf);

#ifndef	ORIGINAL_CODE
	if (!len)
		return 1;
#endif

	for (i=0; i < len; i++)
		k += (*buf++ << (i % 8));
	return ((k == 0) ? 1 : k); 
}
