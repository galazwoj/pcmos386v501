#include "rsa.h"
#include "_rsa.h"

int	EMM_map_page(int handle, int phys_page_number, int logical_page_number)
{
	union REGS      inregs, outregs;
	inregs.h.ah = EMS_MAP_MEMORY;
	inregs.h.al = phys_page_number;
	inregs.x.bx = logical_page_number;
	inregs.x.dx = handle;
	int86(INTR_EMS, &inregs, &outregs);
	return (outregs.h.ah);
}
