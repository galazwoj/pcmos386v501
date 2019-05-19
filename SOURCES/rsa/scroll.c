#include "_rsa.h"
#include "rsa.h"

void    scroll(int cursor_pos1, int cursor_pos2, int num_of_lines, unsigned color, int direction)
{
	union REGS regs;
	 
	if(direction == SCROLL_UP) 
		regs.h.ah = 6;
	else
		regs.h.ah = 7;	
	if (is_color_video() == VIDEO_MONO)
		color = convert_to_mono(color & 0xff);	
	regs.h.al = (char)num_of_lines;
	regs.h.bh = (char)color;
	regs.h.ch = (char)(cursor_pos1 / 100 -1);
	regs.h.cl = (char)(cursor_pos1 % 100 -1);
	regs.h.dh = (char)(cursor_pos2 / 100 + regs.h.ch -1);
	regs.h.dl = (char)(cursor_pos2 % 100 + regs.h.cl -1);
	int86(INTR_VIDEO, &regs, &regs);
}
