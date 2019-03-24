#include "rsa.h"
#include <string.h>

char   *get_line(char *buf, int len, FILE *file)
{
	int i;
	char * str;
	int n;
	char c;
	if (!(str = fgets(buf, len, file)))
		return NULL;

	n = strlen(buf);
	
	i = n-1;
	
	while (i >=0)
	{
		c = *(buf + i);
	        if (c == ' ' || c == '\n' )
		{
			*(buf + i) = '\0';
			i --;
		}
		else 
			return str;
	}
	return str;
}
