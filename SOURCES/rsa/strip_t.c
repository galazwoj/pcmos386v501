#include "rsa.h"
#include <string.h>

void 	strip_trailing_blanks(char *buf)
{
	int n = strlen(buf);
	if (n == 0)
		return;
	while ((n-- >= 0) && *(buf+n) !=' ')
	 	*(buf+n) = '\0';
}
