#include "_rsa.h"
#include "rsa.h"
#include <stdlib.h>

int     *save_video_region(int pos, int dpos)
{
	int num_of_columns = dpos % 100;    	//  2
	int num_of_rows    = dpos / 100;    	//  4
	int column = pos % 100;     	// 0c
	int row    = pos / 100;	//  6
	int *buf;               	// 0a	

	if (!(buf = calloc(sizeof(int), num_of_rows * num_of_columns)))
		return buf;

	_$read_video_region(row, column, num_of_columns, num_of_rows, buf, _$CGA_mode & 0xff);
	return buf;
}


