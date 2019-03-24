#include "_rsa.h"
#include "rsa.h"

int     EMM_save_page_map(int handle)
{
	union REGS inregs, outregs;
	inregs.h.ah = EMM_SAVE_MAPPING_CONTEXT;
	inregs.x.dx = handle;
	int86(INTR_EMM, &inregs, &outregs);
	return (outregs.h.ah);
}
