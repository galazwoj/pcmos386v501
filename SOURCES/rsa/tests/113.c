#include "rsa.h"

int main(void)
{
	char *filename = "sample.txt";
	int attributes = 0;
	int error = 0;	
 	if (!( error = get_file_attributes(filename, &attributes)))
		printf("filename: %s attributes: %x\n", filename, attributes);
	else
	{
		printf("error get: %d\n", error);
		return 1;
	}
	attributes = 0x20;	//ARCHIVE only
	if (( error = set_file_attributes(filename, attributes)))
	{
		printf("error set: %d\n", error);
		return 2;
	}
 	if (!( error = get_file_attributes(filename, &attributes)))
	{
		printf("filename: %s attributes: %x\n", filename, attributes);
		return 0;
	}
	else
	{
		printf("error get: %d\n", error);
		return 1;
	}
}
