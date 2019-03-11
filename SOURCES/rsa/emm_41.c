#include "rsa.h"
#include "_rsa.h"

void far *EMM_get_page_frame(void)
{
	union REGS      inregs, outregs;
	inregs.h.ah = EMS_GET_PAGE_FRAME_SEGMENT;
	int86(INTR_EMS, &inregs, &outregs);
	return MK_FP(outregs.x.bx, 0);
}
