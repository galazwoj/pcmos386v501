#include "rsa.h"
#include <string.h>

int main(void)
{
	char str1[21];
	char str2[21];
	char str3[9];
	strcpy(str1, "here it is");                   
	strcpy(str2, "here it is");  
	strcpy(str3, "DEADBEEF");  
	center(str2, 20);
	printf("'%s''%s''%s'\n", str1, str2, str3);
	return 0;
}
