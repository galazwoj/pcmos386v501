#include "rsa.h"

int main(void)
{
	int result = de_archive_file("dir.arc", "dir.out");
	printf ("result %d\n", result);
	return 0;
}

