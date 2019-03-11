#include "rsa.h"
#include "_rsa.h"

int     EMM_status(void)
{
	union REGS      inregs, outregs;
	inregs.h.ah = EMS_GET_MANAGER_STATUS;
	int86(INTR_EMS, &inregs, &outregs);
	return (outregs.h.ah);
}
