#include "rsa.h"

int main(void)
{
	printf("bios disk reset: %s\n", int13h_status(bios_disk_reset(0x80)));
	return 0;
}
