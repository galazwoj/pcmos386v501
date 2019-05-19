#include "_rsa.h"
#include "rsa.h"

#ifdef ORIGINAL_CODE
void far *EMM_get_page_frame(void)
{
	union REGS      inregs, outregs;
	inregs.h.ah = EMS_GET_PAGE_FRAME_SEGMENT;
	int86(INTR_EMM, &inregs, &outregs);
	return MK_FP(outregs.x.bx, 0);
}
#else
int	EMM_get_page_frame(unsigned *frame_seg)
{
	union REGS inregs, outregs;
	inregs.h.ah = EMM_GET_PAGE_FRAME_SEGMENT;
	int86(INTR_EMM, &inregs, &outregs);
	*frame_seg = outregs.x.bx;
	return (outregs.h.ah);
}
#endif
