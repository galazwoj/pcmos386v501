#include "rsa.h"

int main(void)
{
	int result = compress_file("dir.txt", "dir.cmp", 1);
	printf("result %d\n", result);
	return 0;
}

