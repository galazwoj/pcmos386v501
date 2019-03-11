#include "rsa.h"
#include "_rsa.h"

int     EMM_get_handle_map(int *num_of_active_emm_handles, void *buffer)
{
	union REGS      inregs, outregs;
	struct SREGS	sregs;
	inregs.h.ah = EMS_GET_PAGES_FOR_ALL_HANDLES;
	inregs.x.di = (unsigned)buffer;	
	segread(&sregs);
	int86x(INTR_EMS, &inregs, &outregs, &sregs);
	*num_of_active_emm_handles = outregs.x.bx;
	return (outregs.h.ah);
}
