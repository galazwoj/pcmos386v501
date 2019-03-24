#include "rsa.h"

void    squeeze(char *buf, int character)
{       
	int i = 0;
	int j = 0;

	while (*(buf+i) != '\0')
	{
	 	if (*(buf+i) != (char)character)
		{
			*(buf+j) = *(buf+i);
			j++;
		}
		i++;
	}		
	*(buf+j) = '\0';
}
