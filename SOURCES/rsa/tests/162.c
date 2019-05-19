#include "rsa.h"

char str1[] = "Here is the story";
char str2[] = "THE";
char str3[] = "my";

int main(void)
{
	printf("%s\n%s\n%s\n" , str1, str2, strstri(str1, str2));
	printf("%s\n%s\n%s\n" , str1, str3, strstri(str1, str3));
	printf("%s\n%s\n%s\n" , str2, str3, strstri(str2, str3));
	return 0;
}
