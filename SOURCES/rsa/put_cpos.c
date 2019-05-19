#include "_rsa.h"
#include "rsa.h"

void    put_cpos(int cursor_pos)
{
	int row    = cursor_pos / 100;				
	union REGS inregs, outregs;
	int column = cursor_pos % 100;               	
	inregs.h.dh = (char)row - 1;
	inregs.h.dl = (char)column - 1;
	inregs.h.ah = 2;
	inregs.h.bh = 0;
	int86(INTR_VIDEO, &inregs, &outregs);	// VIDEO - SET CURSOR POSITION
}
