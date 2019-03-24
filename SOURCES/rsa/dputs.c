#include "rsa.h"

void dputs(char *s)
{
	int pos = rdcpos();
	int c;
	while ((c = *s++) != '\0')	
		dputchar(c);
	put_cpos(pos);		
}
