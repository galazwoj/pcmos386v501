#include "rsa.h"
#include <string.h>

char str1[] = "Here is the story";
char str2[] = "   Here is the story";
char str3[] = "Here is the story   ";
               
int main(void)
{
	char buf[25];
	strcpy(buf, str1);
	squeezen(buf, ' ', strlen(str1));
	printf("'%s' ' '\n'%s'\n" , str1, buf);

	strcpy(buf, str2);
	squeezen(buf, ' ', strlen(str2));
	printf("'%s' ' '\n'%s'\n" , str2, buf);

	strcpy(buf, str3);
	squeezen(buf, ' ', strlen(str3) -12);
	printf("'%s' ' '\n'%s'\n" , str3, buf);

	strcpy(buf, str3);
	squeezen(buf, ' ', 7);
	printf("'%s' ' '\n'%s'\n" , str3, buf);

	strcpy(buf, str1);
	squeezen(buf, '?',strlen(str1));
	printf("'%s' '?'\n'%s'\n" , str1, buf);

	return 0;
}
