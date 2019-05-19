#include "rsa.h"

int main(void)
{
	char *str = "A brown fox jumped over the fence";
	int key = 9;
	printf("'%s'\n", str);
	encrypt(str, key);
	printf("'%s'\n", str);
	decrypt(str, key);
	printf("'%s'\n", str);
	return 0;
}
