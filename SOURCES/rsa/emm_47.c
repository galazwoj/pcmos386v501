#include "rsa.h"
#include "_rsa.h"

int     EMM_save_page_map(int handle)
{
	union REGS      inregs, outregs;
	inregs.h.ah = EMS_SAVE_MAPPING_CONTEXT;
	inregs.x.dx = handle;
	int86(INTR_EMS, &inregs, &outregs);
	return (outregs.h.ah);
}
