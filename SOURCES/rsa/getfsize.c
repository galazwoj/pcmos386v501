#include "rsa.h"
#include <io.h>

long        get_file_size(char *filename)
{
	long size;
	FILE *f;
	if(access(filename, 0) != 0)
		return 0L;
	f = fopen(filename, "rb");
	fseek(f, 0L, 2);
	size = ftell(f);
	fclose(f);
	return size;
}
