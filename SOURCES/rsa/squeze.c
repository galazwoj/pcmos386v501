#include "rsa.h"

void    squeeze(char *buf, int character)
{       
	int i = 0;
	int j = 0;

#ifndef	ORIGINAL_CODE
	if (!buf)
		return;
#endif

	while (buf[i] != '\0')
	{
	 	if ((int)buf[i] != character)
			buf[j++] = buf[i];
		i++;
	}		
	buf[j] = '\0';
}
