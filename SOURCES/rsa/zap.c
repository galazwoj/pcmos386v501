#include "rsa.h"

void zap(void *buf, unsigned size, char character)
{
	char *c = buf;
#ifndef	ORIGINAL_CODE
	if (!buf || !size)
		return;
#endif
	while (size -- > 0)
		*c++ = character;
}
