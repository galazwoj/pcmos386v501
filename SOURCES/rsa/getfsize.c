#include "rsa.h"
#include <io.h>

long  	get_file_size(char *filename)
{
	long size;
	FILE *f;

#ifndef	ORIGINAL_CODE
	if (!filename)
		return 0;
#endif	

	if(access(filename, 0) != 0)
		return 0L;
	f = fopen(filename, "rb");

#ifndef	ORIGINAL_CODE
	if (!f)
		return 0;
#endif	

	fseek(f, 0L, 2);
	size = ftell(f);
	fclose(f);
	return size;
}
