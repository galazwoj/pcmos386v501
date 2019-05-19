#include "_rsa.h"
#include "rsa.h"

int	EMM_free_pages(int handle)
{
	union REGS inregs, outregs;
	inregs.h.ah = EMM_RELEASE_HANDLE_AND_MEMORY;
	inregs.x.dx = handle;
	int86(INTR_EMM, &inregs, &outregs);
	return (outregs.h.ah);
}
