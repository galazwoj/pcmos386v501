#include "rsa.h"

int main(void)
{
	int drive = 3;
	printf("disc %c free %lu MB\n", drive + 'A' -1, diskfree(drive) / 1024);
	return 0;
}
