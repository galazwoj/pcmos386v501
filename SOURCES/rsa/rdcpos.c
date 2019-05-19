#include "_rsa.h"
#include "rsa.h"

int     rdcpos(void)
{
	int cursor_pos;
	union REGS inregs, outregs;	
	inregs.h.ah = 3;
	inregs.h.bh = 0;
	int86(INTR_VIDEO, &inregs, &outregs);		// VIDEO - GET CURSOR POSITION AND SIZE
	outregs.x.dx += 0x101;
	cursor_pos = outregs.h.dh * 100 + outregs.h.dl;
	return cursor_pos;
}
