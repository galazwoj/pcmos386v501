#include "rsa.h"

void    squeezen(char *buf, int character, int count)
{       
	int i = 0;
	int j = 0;

#ifndef	ORIGINAL_CODE
	if (!buf || !count)
		return;
#endif

	while (count -- > 0)
	{
	 	if ((int)buf[i] != character)
			buf[j++] = buf[i];
		i++;
	}		
	buf[j] = '\0';
}
