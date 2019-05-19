#include "_rsa.h"
#include "rsa.h"
#include <stdlib.h>

int     restore_video_region(int pos, int dpos, int *buf)
{
	int num_of_columns = dpos % 100;    	//  2
	int num_of_rows    = dpos / 100;    	//  4
	int column = pos % 100;       // 0a 	
	int row    = pos / 100;	//  6
	
	if (!buf)
		return 0;
	_$write_video_region(row, column, num_of_columns, num_of_rows, buf, _$CGA_mode & 0xff);	
	free(buf);
	return 1;
}


