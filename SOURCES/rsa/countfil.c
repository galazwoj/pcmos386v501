#include "rsa.h"

int     count_matching_files(char *filespec)
{
	char filename[14];
	int attribute;	
 	int i = 0;
	int result;                                                               
	result = find_first_file(filespec, filename, &attribute);
	while ( result != 0)
	{
		i++;
		result = find_next_file(filename, &attribute);
	}
	return i;
}
