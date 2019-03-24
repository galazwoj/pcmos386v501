#include "_rsa.h"
#include "rsa.h"

int	EMM_map_page(int handle, int phys_page_number, int logical_page_number)
{
	union REGS inregs, outregs;
	inregs.h.ah = EMM_MAP_MEMORY;
	inregs.h.al = (char)phys_page_number;
	inregs.x.bx = logical_page_number;
	inregs.x.dx = handle;
	int86(INTR_EMM, &inregs, &outregs);
	return (outregs.h.ah);
}
