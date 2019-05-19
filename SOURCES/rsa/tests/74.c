#include "rsa.h"

int main(void)
{
	char *source_file = "orig.txt";
	char *dest_file = "copy.txt";	
	char *result[4]; 

	result[0] = "copied successfully";	
	result[1] = "source file error";	
	result[2] = "dest file error";	
	result[3] = "not enough memory";	
	printf("%s -> %s = %s\n",source_file, dest_file, result[copy_file(source_file, dest_file)]);
	return 0;
}
