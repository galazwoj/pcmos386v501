#include "_rsa.h"
#include "rsa.h"

int files_open;
char * file_pointer_map[MAX_FILES];
int file_record_size[MAX_FILES];

FILE  *da_open(char *filename, char *mode, int record_size)
{
	FILE *file;
	int i = 0;
	if (files_open == MAX_FILES)
		return NULL;
	if (!(file = fopen(filename, mode)))
		return NULL;

	while(file_pointer_map[i++] != 0)
		;
	file_pointer_map[i] = file->_ptr;
	file_record_size[i] = record_size;
	files_open--;
	return file;
}
