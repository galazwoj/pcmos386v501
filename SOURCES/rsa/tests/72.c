#include "rsa.h"
#include <string.h>

int main(void)
{
	char *str1 = "A brown fox\tjumped\tover the fence";
	char str2[60];
	int key = 9;
	printf("'%s'\n", str1);
	convert_tabs(str1, str2, strlen(str1), 8);
	printf("'%s'\n", str2);
	return 0;
}
