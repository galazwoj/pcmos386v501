#include "_rsa.h"
#include "rsa.h"

void    gtime(struct DATETIME *datetime)
{
	union REGS      inregs, outregs;

	inregs.h.ah =0x2a;			
	int86(INTR_DOS, &inregs, &outregs);     // DOS 1+ - GET SYSTEM DATE
	datetime->year  = outregs.x.cx;
	datetime->month = outregs.h.dh;
	datetime->day   = outregs.h.dl;

	inregs.h.ah =0x2c;			
	int86(INTR_DOS, &inregs, &outregs);     // DOS 1+ - GET SYSTEM TIME
	datetime->hour    = outregs.h.ch;
	datetime->minute  = outregs.h.cl;
	datetime->second  = outregs.h.dh;
	datetime->msecond = outregs.h.dl;	
}