#include "_rsa.h"
#include "rsa.h"

void far *EMM_get_page_frame(void)
{
	union REGS inregs, outregs;
	inregs.h.ah = EMM_GET_PAGE_FRAME_SEGMENT;
	int86(INTR_EMM, &inregs, &outregs);
	return MK_FP(outregs.x.bx, 0);
}
