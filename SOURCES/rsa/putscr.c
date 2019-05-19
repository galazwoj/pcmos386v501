#include "_rsa.h"
#include "rsa.h"
#include <stdlib.h>

void putscr(char *screen_buf, int color)
{
	int *buf;		
	int i;                             	
#ifndef ORIGINAL_CODE
	if(!screen_buf)
		return;
#endif
	buf = malloc(80*25*2);		

#ifndef ORIGINAL_CODE
	if(!buf)
		return;
#endif

	for (i=0; i< 2000; i++)
		buf[i] = (color << 8) | (int)(*screen_buf++);

	_$write_video_region(1, 1, 80, 25, buf, _$CGA_mode & 0xff);
	free(buf);
}