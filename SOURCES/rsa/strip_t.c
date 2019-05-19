#include "rsa.h"
#include <string.h>

void 	strip_trailing_blanks(char *buf)
{
	int i;
	int n = strlen(buf);
	if (n == 0)
		return;
	i = n-1;
	while ((i >= 0) && buf[i] == ' ')
	 	buf[i--] = '\0';
}
