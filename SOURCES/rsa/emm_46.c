#include "rsa.h"
#include "_rsa.h"


int     EMM_get_version(int *version)
{
	union REGS      inregs, outregs;
	inregs.h.ah = EMS_GET_EMM_VERSION;
	int86(INTR_EMS, &inregs, &outregs);
	*version = outregs.h.al;
	return (outregs.h.ah);
}
