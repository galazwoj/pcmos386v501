#include "_rsa.h"
#include "rsa.h"

int  files_open = 0;
FILE * file_pointer_map[MAX_FILES] = {0,0,0,0,0,0,0,0,0,0};
int  file_record_size[MAX_FILES]   = {0,0,0,0,0,0,0,0,0,0};

FILE  *da_open(char *filename, char *mode, int record_size)
{
	FILE *file;
	int i = 0;

#ifndef ORIGINAL_CODE
	if (!filename || !mode || !record_size)
		return 0;
#endif

	if (files_open == MAX_FILES)
		return NULL;
	if (!(file = fopen(filename, mode)))
		return NULL;
	for(i=0; i < MAX_FILES; i++)
		if(file_pointer_map[i] == 0)
		{	
			file_pointer_map[i] = file;
			file_record_size[i] = record_size;
			files_open++;
			return file;
		}
#ifndef ORIGINAL_CODE
	fclose(file);
	return NULL;
#endif	
}
