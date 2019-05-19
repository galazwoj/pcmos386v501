#include "rsa.h"

int main(void)
{
	char *str = "A brown fox jumped over the fence";
	char c;
	while ((c = *str++))
		dputchar(c);
	return 0;
}
