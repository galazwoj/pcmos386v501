#include "_rsa.h"
#include "rsa.h"

static int mouse_present = 0;
static int screen_x = 1;
static int screen_y = 1;

int	read_mouse(int action, int *button_status, int *rows, int *columns)
{
	int cursor_pos;
	union REGS inregs, outregs;

	if (action == 0)
	{
		int row, column;
		inregs.x.ax = 0x21;
		int86(INTR_MOUSE, &inregs, &outregs);    	// MS MOUSE v6.0+ - SOFTWARE RESET
		if (inregs.x.ax == outregs.x.ax) 		
		{
			inregs.x.ax = 0;
			int86(INTR_MOUSE, &inregs, &outregs); 	// MS MOUSE - RESET DRIVER AND READ STATUS
			if (inregs.x.ax == outregs.x.ax)
			{ 		
				mouse_present = 0;
				return MOUSE_NOT_PRESENT;
			}
		}		
		inregs.x.ax = 3;
		int86(INTR_MOUSE, &inregs, &outregs);   	// MS MOUSE v1.0+ - RETURN POSITION AND BUTTON STATUS
		column = outregs.x.cx * 2;
		row = outregs.x.dx * 2;

		screen_x = column / 0x50;
		screen_y = row / 0x18;
		*button_status = outregs.x.bx;
#ifndef ORIGINAL_CODE
		if (column == 0 || row == 0)
			mouse_present = 0;
		else
#endif		
		mouse_present = 1;
	}
	if (mouse_present == 0)
	{
		*button_status = 0;
#ifndef ORIGINAL_CODE
		*rows = 0;
		*columns = 0;
#endif		
		return MOUSE_NOT_PRESENT;
	}
	if (action == 0 || action == 2)
	{
		inregs.h.ah = 3;
		inregs.h.bh = 0;
		int86(INTR_VIDEO, &inregs, &outregs);		// VIDEO - GET CURSOR POSITION AND SIZE
		cursor_pos = outregs.x.dx;
		inregs.x.cx = (cursor_pos & 0xff) * screen_x;
		inregs.x.dx = (cursor_pos >> 8  ) * screen_y;
		inregs.x.ax = 4;
		int86(INTR_MOUSE, &inregs, &outregs);       	// MS MOUSE v1.0+ - POSITION MOUSE CURSOR
	}
	inregs.x.ax = 3;
	int86(INTR_MOUSE, &inregs, &outregs);           	// MS MOUSE v1.0+ - RETURN POSITION AND BUTTON STATUS
	*button_status = outregs.x.bx;
	*rows = outregs.x.dx / screen_y + 1;
	*columns = outregs.x.cx / screen_x +1;

	return MOUSE_PRESENT;
}
