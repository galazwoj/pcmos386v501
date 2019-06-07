#include "rsa.h"

int main(void)
{
	int result = expand_file("dir.cmp", "dir.out", 1);
	printf ("result %d\n", result);
	return 0;
}

