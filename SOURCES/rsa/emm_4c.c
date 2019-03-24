#include "_rsa.h"
#include "rsa.h"

int     EMM_get_handle_pages(int handle, int *num_of_logical_pages)
{
	union REGS inregs, outregs;
	inregs.h.ah = EMM_GET_PAGES_OWNED_BY_HANDLE;
	inregs.x.dx = handle;
	int86(INTR_EMM, &inregs, &outregs);
	*num_of_logical_pages = outregs.x.bx;
	return (outregs.h.ah);
}
