#include "_rsa.h"
#include "rsa.h"

int     da_write(FILE *file, void *buf, unsigned record_pos)
{
	long record_offset; 	
	long file_size;
	int i;
	int fs;

#ifndef ORIGINAL_CODE
	if (!buf)
		return 0;
#endif

	if (!file || !files_open)
		return 0;
	for (i=0; i< MAX_FILES; i++)
		if (file_pointer_map[i] == file)
		{	
			fs = file_record_size[i];
			break;
		}
	if (i == MAX_FILES)
		return 0;
	record_offset = (long)fs * record_pos;
	fseek(file, 0L, 2);
	file_size = ftell(file);
	if (record_offset > file_size)
		return 0;
	fseek(file, record_offset, 0);
#ifdef ORIGINAL_CODE
	fwrite(buf, 1, fs, file);
#else
	if (fwrite(buf, fs, 1, file) != 1)
		return 0;
#endif
	fflush(file);
	return -1;
}
