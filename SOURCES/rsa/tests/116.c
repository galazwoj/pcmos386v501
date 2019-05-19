#include "rsa.h"

int main(void)
{
#define BUFSZIE	80
	char buf[BUFSZIE+1];
	int n = get_string(buf, BUFSZIE, 1);
	printf("\n%x '%s'\n", n, buf);
	return 0;
}
