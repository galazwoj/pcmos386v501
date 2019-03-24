#include "_rsa.h"
#include "rsa.h"

int     EMM_get_version(int *version)
{
	union REGS inregs, outregs;
	inregs.h.ah = EMM_GET_EMM_VERSION;
	int86(INTR_EMM, &inregs, &outregs);
	*version = outregs.h.al;
	return (outregs.h.ah);
}
