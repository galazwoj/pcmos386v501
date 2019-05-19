#include "rsa.h"
#include <string.h>

int main(void)
{
	char *buf = "123456789012345678901234567890123456789012345678901234567890";
   	dump_buffer_to_screen(buf, strlen(buf));
	return 0;
}
