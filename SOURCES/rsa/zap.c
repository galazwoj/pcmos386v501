#include "rsa.h"

void zap(void *buf, unsigned size, char character)
{
	char *c = buf;
	while (size -- > 0)
		*c++ = character;
}
