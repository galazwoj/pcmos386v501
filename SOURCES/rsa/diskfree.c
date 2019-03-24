#include "_rsa.h"
#include "rsa.h"

unsigned long diskfree(int drive)
{
	unsigned long space;
	union REGS inregs, outregs;
	inregs.h.ah = 0x36;
	inregs.h.dl = (char)drive;
	int86(INTR_DOS, &inregs, &outregs);
	space = (outregs.x.ax * outregs.x.bx * outregs.x.cx) / 1024;
	return space;
}
