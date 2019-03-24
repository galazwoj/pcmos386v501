#include "rsa.h"
#include <stdlib.h>

#define BUF_SIZE 0x1000

int    	copy_file(char *source_file, char *dest_file)
{
	int bytes_read;
	FILE *sf;
	char *buf;
	FILE *df;

	if (!(sf = fopen(source_file, "rb")))
		return 1;
	if (!(df = fopen(dest_file, "wb")))
	{
		fclose(sf);
		return 2;
	}
	if (!(buf = malloc(BUF_SIZE)))
	{
		fclose(sf);
		fclose(df);
		return 3;
	}

	while (!feof(sf))
	{
		bytes_read = fread(buf, 1, BUF_SIZE, sf);
                fwrite(buf, 1, bytes_read, df);
	}

	fclose(sf);
	fclose(df);
	free(buf);
	return 0;
}
