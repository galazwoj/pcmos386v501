#include "rsa.h"

int main(void)
{
#define BUFSZIE	80
	char buf[BUFSZIE+1];
	get_line(buf, BUFSZIE, stdin);
	puts(buf);
	return 0;
}
