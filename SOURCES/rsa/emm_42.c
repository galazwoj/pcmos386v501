#include "rsa.h"
#include "_rsa.h"

int     EMM_get_page_count(int *total_pages, int *unallocated_pages)
{
	union REGS      inregs, outregs;
	inregs.h.ah = EMS_GET_NUMBER_OF_PAGES;
	int86(INTR_EMS, &inregs, &outregs);
	*total_pages = outregs.x.dx;
	*unallocated_pages = outregs.x.bx;
	return (outregs.h.ah);
}
