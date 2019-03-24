#include "_rsa.h"
#include "rsa.h"
#include <stdlib.h>

int     restore_video_region(int pos1, int pos2, void *buf)
{
	int column2 = pos2 % 100;
	int row2    = pos2 / 100;
	int column1 = pos1 % 100;
	int row1    = pos1 / 100;	
	
	if (!buf)
		return 0;
	_$write_video_region(column1, row1, column2, row2, buf, _$CGA_mode);
//	_$write_video_region(row1, column1, column2, row2, buf, _$CGA_mode);	???
	free(buf);
	return 1;
}


