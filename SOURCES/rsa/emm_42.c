#include "_rsa.h"
#include "rsa.h"

int     EMM_get_page_count(int *total_pages, int *unallocated_pages)
{
	union REGS inregs, outregs;
	inregs.h.ah = EMM_GET_NUMBER_OF_PAGES;
	int86(INTR_EMM, &inregs, &outregs);
	*total_pages = outregs.x.dx;
	*unallocated_pages = outregs.x.bx;
	return (outregs.h.ah);
}
