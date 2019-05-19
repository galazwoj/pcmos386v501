#include "rsa.h"
#include <ctype.h>

int     htoi(char *buf)
{
	int number = 0;
	unsigned char c;

#ifndef	ORIGINAL_CODE
	if (!buf)
		return 0;
#endif

	while(*buf == ' ')
		*buf++;
	while(1)
	{	
		c = *buf;
		if (!c || !isxdigit(c))
			return number;
		number <<= 4;

		if (c < '0' || c > '9')
		{
		 	if(c < 'A' || c > 'F')
				c -= 'a' - 10;			
			else
				c -= 'A' - 10;
		}		
		else
			c -= '0';
		
		number += (int)c;
		buf++;
	}	
}

