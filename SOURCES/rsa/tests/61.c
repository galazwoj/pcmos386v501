#include "rsa.h"

int main(void)
{
	int result = archive_file("dir.txt", "dir.arc", 1);
	printf ("result %d\n", result);
	return 0;
}

