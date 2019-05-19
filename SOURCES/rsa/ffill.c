#include "rsa.h"

void    ffill(FILE *file, char character, unsigned count)
{
	while(count -- > 0)
#if 1
		putc(character, file);
#else
		if (--(file)->_cnt >= 0)
			*(file)->_ptr++ = character;
		else
			_flsbuf(character, file);
#endif
}

