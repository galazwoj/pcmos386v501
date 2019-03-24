#include "_rsa.h"
#include "rsa.h"

unsigned int 	_$$cursor_sp = 0xffff;

void	cursor_off(void)
{
	union REGS regs;
	if (_$$cursor_sp  == 0x13)
		return;
	regs.h.ah = 3;
	regs.h.bh = 0;
	int86(INTR_VIDEO, &regs, &regs);		// VIDEO - GET CURSOR POSITION AND SIZE
	_$$cursor_stack[++_$$cursor_sp] = regs.x.cx;
	regs.h.ah = 1;
	regs.x.cx = 0x2000;
	int86(INTR_VIDEO, &regs, &regs);		// VIDEO - SET TEXT-MODE CURSOR SHAPE	
}

void    cursor_on(void)
{
	union REGS regs;
	if (_$$cursor_sp == 0xffff)
		return;
	regs.h.ah = 1;
	regs.x.cx = _$$cursor_stack[_$$cursor_sp--];
	int86(INTR_VIDEO, &regs, &regs);		// VIDEO - SET TEXT-MODE CURSOR SHAPE
}



