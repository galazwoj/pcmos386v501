#include "rsa.h"
#include <string.h>

char str [] = "123456789";

int main(void)
{
	printf("%s crc16 is: %x' \n", str, crc16(str, strlen(str)));
	return 0;
}
