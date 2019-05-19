#include "rsa.h"

int main(void)
{
	printf("bios disk status: %s\n", int13h_status(bios_disk_status(0x80)));
	return 0;
}

