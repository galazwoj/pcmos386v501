#include "rsa.h"

int main(void)
{
	char *filemask = "*.txt";
	printf("file mask %s, number %d\n", filemask, count_matching_files(filemask));
	return 0;
}
