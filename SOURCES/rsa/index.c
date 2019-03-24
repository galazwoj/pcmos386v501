#include "rsa.h"
#include <string.h>

int 	index(char character, char *buf)
{
	int i;
	int n = strlen(buf);
	if (n == 0)
		return -1;
	
	for (i=0; i < n; i ++)
		if (*(buf+i) == character)			
			return i;
	return -1;
}
