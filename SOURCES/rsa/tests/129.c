#include "rsa.h"
#include <string.h>

int main(void)
{
	char str1[21];
	char str2[21];
	char str3[9];
	strcpy(str1, "          here it is");                   
	strcpy(str2, "          here it is");  
	strcpy(str3, "DEADBEEF");  

	just(str2, 20, -1);
	printf(" %d '%s'\n    '%s'\n'%s'\n\n", -1, str1, str2, str3);

	strcpy(str1, "          here it is");                   
	strcpy(str2, "          here it is");  
	strcpy(str3, "DEADBEEF");  
	just(str2, 20, 1);
	printf("  %d '%s'\n    '%s'\n'%s'\n\n",  1, str1, str2, str3);
//	              12345678901234567890
	strcpy(str1, "here it is          ");                   
	strcpy(str2, "here it is          ");  
	strcpy(str3, "DEADBEEF");  

	just(str2, 20, -1);
	printf(" %d '%s'\n    '%s'\n'%s'\n\n", -1, str1, str2, str3);

	strcpy(str1, "here it is          ");                   
	strcpy(str2, "here it is          ");  
	strcpy(str3, "DEADBEEF");  
	just(str2, 20, 1);
	printf("  %d '%s'\n    '%s'\n'%s'\n\n",  1, str1, str2, str3);

	return 0;
}
