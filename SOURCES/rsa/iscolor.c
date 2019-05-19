#include "_rsa.h"
#include "rsa.h"

static char video_mode = 0;

int	is_color_video(void)
{
	if (video_mode == 0)
	{
		union REGS inregs, outregs;
		int86(INTR_EQUIPMENT, &inregs, &outregs);
		video_mode = outregs.h.al & 0x30;
	}
	return ((video_mode & 0x30) == 0x30) ? VIDEO_MONO : VIDEO_COLOR;
}
   