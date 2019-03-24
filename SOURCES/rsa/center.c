#include "rsa.h"
#include <stdlib.h>
#include <string.h>

void   	center(char *buf, unsigned len)
{
	char *str = malloc(len + 1);
	int k, n;
	strcpy(str, buf);
	n = strlen(str);
	k = (len - n) /2 -1;
	zap(buf, len, ' ');
	strcpy(buf + k, str);
	free(str);
}
