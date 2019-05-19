#include "rsa.h"

int main(void)
{
 	char *str = "Here it is";
	printf("%s, %d\n", str, index('t', str));
	printf("%s, %d\n", str, index('a', str));
	return 0;
}
