#include "rsa.h"
#include "_rsa.h"

int	EMM_free_pages(int handle)
{
	union REGS      inregs, outregs;
	inregs.h.ah = EMS_RELEASE_HANDLE_AND_MEMORY;
	inregs.x.dx = handle;
	int86(INTR_EMS, &inregs, &outregs);
	return (outregs.h.ah);
}
