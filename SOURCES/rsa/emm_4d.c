#include "_rsa.h"
#include "rsa.h"

int     EMM_get_handle_map(int *num_of_active_emm_handles, void *buffer)
{
	union REGS inregs, outregs;
	struct SREGS sregs;
	inregs.h.ah = EMM_GET_PAGES_FOR_ALL_HANDLES;
	inregs.x.di = FP_OFF(buffer);	
#ifdef M_I86LM
	sregs.es = FP_SEG(buffer);	
#else
	segread(&sregs);
#endif
	int86x(INTR_EMM, &inregs, &outregs, &sregs);
	*num_of_active_emm_handles = outregs.x.bx;
	return (outregs.h.ah);
}
