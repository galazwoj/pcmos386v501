#include "rsa.h"
#include <stdlib.h>

#define MK_FP( seg,ofs ) (void far * )(((unsigned long)((unsigned long)(seg) << 16)) + ((unsigned long)(ofs)))

int main(void)
{
	char *charptr; 
	char *c;
	unsigned video_offset;
	unsigned video_seg = 0xB800;

	if (!(c = charptr = malloc(80*25)))
		return 1;

	for (video_offset=0; video_offset < 4000; video_offset+=2)
	{
		int far *v = MK_FP(video_seg, video_offset);
		*c++ = (char)(*v & 0xff);
	}

	putscr(charptr, _$asa_color);
	free(charptr);
	return 0;
}


