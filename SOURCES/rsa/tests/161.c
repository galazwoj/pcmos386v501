#include "rsa.h"
#include <string.h>

char str1[] = "Here is the story";
char str2[] = "   Here is the story";
char str3[] = "Here is the story   ";
               
int main(void)
{
	char buf[25];
	strcpy(buf, str1);
	strip_trailing_blanks(buf);
	printf("'%s'\n'%s'\n\n" , str1, buf);

	strcpy(buf, str2);
	strip_trailing_blanks(buf);
	printf("'%s'\n'%s'\n\n" , str2, buf);

	strcpy(buf, str3);
	strip_trailing_blanks(buf);
	printf("'%s'\n'%s'\n\n" , str3, buf);

	return 0;
}
