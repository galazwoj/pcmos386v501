#include "rsa.h"
#include <string.h>

char str[] = "1234567890";

int main(void)
{
	char buf[21];
	memset(buf, 0, 21);
	puts(str);
	zap(str, 4, '#');
	puts(str);	
	zap(buf, 20, ' ');
	printf("'%s'\n", buf);
	return 0;
}
