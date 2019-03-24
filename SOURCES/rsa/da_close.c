#include "_rsa.h"
#include "rsa.h"

int    	da_close(FILE *file)
{
	int i;
	if (!files_open || !file)
		return 0;
	for (i=0; i < MAX_FILES; i++)
		if (file->_ptr == file_pointer_map[i])
		{
			file_pointer_map[i] = 0;
			file_record_size[i] = 0;
			files_open--;
			fclose(file);
			return -1;
		}
}
