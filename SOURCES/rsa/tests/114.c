#include "rsa.h"

int main(void)
{
	char *filename = "sample.txt";
	printf("file %s size %ld\n", filename, get_file_size(filename));
	return 0;
}
