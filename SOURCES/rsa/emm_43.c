#include "rsa.h"
#include "_rsa.h"

int     EMM_allocate_pages(int num_logical_pages, int *handle)
{
	union REGS      inregs, outregs;
	
	inregs.h.ah = EMS_GET_HANDLE_AND_ALLOCATE_MEM;
	inregs.x.bx = num_logical_pages;
	int86(INTR_EMS, &inregs, &outregs);
	*handle = (outregs.h.ah == 0) ? outregs.x.dx : 0xffff;
	return (outregs.h.ah);
}
