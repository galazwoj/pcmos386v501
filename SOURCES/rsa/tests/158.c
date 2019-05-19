#include "rsa.h"
#include <string.h>

char str1[] = "Here is the story";
char str2[] = "   Here is the story";
char str3[] = "Here is the story   ";
               
int main(void)
{
	char buf[25];
	strcpy(buf, str1);
	squeeze(buf, ' ');
	printf("'%s' ' '\n'%s'\n" , str1, buf);

	strcpy(buf, str2);
	squeeze(buf, ' ');
	printf("'%s' ' '\n'%s'\n" , str2, buf);

	strcpy(buf, str3);
	squeeze(buf, ' ');
	printf("'%s' ' '\n'%s'\n" , str3, buf);

	strcpy(buf, str1);
	squeeze(buf, '?');
	printf("'%s' '?'\n'%s'\n" , str1, buf);

	return 0;
}
