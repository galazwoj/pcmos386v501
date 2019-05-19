#include "rsa.h"
#include <string.h>

void 	strip_leading_blanks(char *buf)
{
	int k;
	int i = 0;
	int n = strlen(buf);

	if (n == 0)
		return;

	while ((i < n) && buf[i] == ' ')
		i++; 
		  	
	k = i;
	if (k == 0)
		return;
	
	for (i=0; i < n; i++) 
	{
		buf[i] = buf[i+k];
		buf[i+1] = '\0';
	}
}                                                                    

	