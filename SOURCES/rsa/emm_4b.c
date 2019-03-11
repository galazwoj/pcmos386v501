#include "rsa.h"
#include "_rsa.h"

int     EMM_get_handle_count(int *num_of_emm_handles)
{
	union REGS      inregs, outregs;
	inregs.h.ah = EMS_GET_NUMBER_OF_EMM_HANDLES;
	int86(INTR_EMS, &inregs, &outregs);
	*num_of_emm_handles = outregs.x.bx;
	return (outregs.h.ah);
}
