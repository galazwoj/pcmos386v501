#include "rsa.h"
#include <string.h>

char   *get_line(char *buf, int len, FILE *file)
{
	int i;
	char * str;

#ifndef	ORIGINAL_CODE
	if (!buf || !len || !file)
		return NULL;
#endif

	if (!(str = fgets(buf, len, file)))
		return NULL;

	i = strlen(buf) - 1;
	
	while (i >= 0 && (buf[i] == ' ' || buf[i]== 0xa))
		buf[i--] = '\0';
	return str;
}
