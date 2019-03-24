#include "_rsa.h"
#include "rsa.h"

int     EMM_status(void)
{
	union REGS inregs, outregs;
	inregs.h.ah = EMM_GET_MANAGER_STATUS;
	int86(INTR_EMM, &inregs, &outregs);
	return (outregs.h.ah);
}
