#include "_rsa.h"
#include "rsa.h"

void    scr(int action, int cursor_pos, int length, int color)
{
	int video_seg;
	union REGS inregs, outregs;
	int video_offset;

	if (is_color_video() == VIDEO_MONO)
	{
		video_seg = 0xB000;
		color = convert_to_mono(color);
	}
	else
		video_seg = 0xB800;

#ifndef	ORIGINAL_CODE
	_$video_address = video_seg;
#endif
		
	switch (action)
	{
		case CLEARSCREEN:  	// scroll up entire window
			inregs.x.ax = 0x600;
			inregs.h.bh = (char)color;
			inregs.x.cx = 0;
			inregs.h.dh = 0x18;
			inregs.h.dl = 0x4f;
			int86(INTR_VIDEO, &inregs, &outregs);	// VIDEO - SCROLL UP WINDOW
			put_cpos(0x65);	
			break;			
                case SET_CURSOR:	// set cursor
			put_cpos(cursor_pos);
			break;
		case CLEARROW:	// clear multiple columns / one row
			inregs.x.ax = 0x600;
			inregs.h.bh = (char)color;
			inregs.h.ch = (char)(cursor_pos / 100 -1);
			inregs.h.cl = (char)(cursor_pos % 100 -1);
			inregs.x.dx = inregs.x.cx;
			inregs.h.dl += (char)(length -1);
			int86(INTR_VIDEO, &inregs, &outregs);	// VIDEO - SCROLL UP WINDOW
			put_cpos(cursor_pos);
			break;
		case CLEARCOLUMN:	// clear multiple rows / one column
			inregs.x.ax = 0x600;
			inregs.h.bh = (char)color;
			inregs.h.ch = (char)(cursor_pos / 100 -1);
			inregs.h.cl = (char)(cursor_pos % 100 -1);
			inregs.x.dx = inregs.x.cx;
			inregs.h.dh += (char)(length -1);
			int86(INTR_VIDEO, &inregs, &outregs);	// VIDEO - SCROLL UP WINDOW
			put_cpos(cursor_pos);
			break;
		case CHANGEATTRIBUTE:	// direct row attribute change
			put_cpos(cursor_pos);
			video_offset  = ((int)(cursor_pos / 100)) * 0xa0 - 0xa0;			
			video_offset += ((int)(cursor_pos % 100)) *  2 -  2; 
			change_video_attribute(video_seg, video_offset, color, length);
			break;
		default:
			;
	}	
}
