#include "rsa.h"

void    squeezen(char *buf, int character, int count)
{       
	int i = 0;
	int j = 0;

	while (count -- > 0)
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
