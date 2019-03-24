#include "_rsa.h"
#include "rsa.h"
#include <stdlib.h>

void    *save_video_region(int pos1, int pos2)
{
	int column2 = pos2 % 100;
	int row2    = pos2 / 100;
	int column1 = pos1 % 100;
	int row1    = pos1 / 100;	
	void *buf;

	if (!(buf = calloc(sizeof(int), row2 * column2)))
		return buf;

	_$read_video_region(column1, row1, column2, row2, buf, _$CGA_mode);
//	_$read_video_region(row1, column1, column2, row2, buf, _$CGA_mode);
	return buf;
}


