#include "rsa.h"
#include "_rsa.h"
#include <stdlib.h>

void putscr(void *screen_buf, int color)
{
	char *buf = malloc(0x0fa0);
	char *c = screen_buf;
	int i = 0;
	do {
		*(buf + i) = *c++;
		*(buf + i+1) = (char) color;
		i +=2;
	} while (i < 0x0fa0);

	_$write_video_region(1, 1, 80, 25, buf, _$CGA_mode);
	free(buf);
}