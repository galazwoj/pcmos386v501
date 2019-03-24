#include "_rsa.h"
#include "rsa.h"
                                  
#define GET_MAPPING	0x0 	// get mapping registers
#define SET_MAPPING	0x1	// set mapping registers          
#define GET_SET_MAPPING	0x2 	// get and set mapping registers at once
#define GET_ARRAY_SIZE	0x3 	// get size of page-mapping array

int     EMM_get_page_map(void *receive_buffer)            
{
	union REGS inregs, outregs;
	struct SREGS sregs;
	inregs.h.ah = EMM_GET_OR_SET_PAGE_MAP;
	inregs.h.al = GET_MAPPING;
	segread(&sregs);
	inregs.x.di = (unsigned)receive_buffer;
	int86x(INTR_EMM, &inregs, &outregs, &sregs);
	return (outregs.h.ah);
}

int     EMM_set_page_map(void *current_buffer)            
{
	union REGS inregs, outregs;
	struct SREGS sregs;
	inregs.h.ah = EMM_GET_OR_SET_PAGE_MAP;
	inregs.h.al = SET_MAPPING;
	segread(&sregs);
	inregs.x.si = (unsigned)current_buffer;
	int86x(INTR_EMM, &inregs, &outregs, &sregs);
	return (outregs.h.ah);
}

int     EMM_get_set_page_map(void *current_buffer, void *receive_buffer)  	
{
	union REGS inregs, outregs;
	struct SREGS sregs;
	inregs.h.ah = EMM_GET_OR_SET_PAGE_MAP;
	inregs.h.al = GET_SET_MAPPING;
	segread(&sregs);
	inregs.x.si = (unsigned)current_buffer;
	inregs.x.di = (unsigned)receive_buffer;
	int86x(INTR_EMM, &inregs, &outregs, &sregs);
	return (outregs.h.ah);
}

int     EMM_get_page_map_size(int *array_size)        	
{
	union REGS inregs, outregs;
	inregs.h.ah = EMM_GET_OR_SET_PAGE_MAP;
	inregs.h.al = GET_ARRAY_SIZE;
	int86(INTR_EMM, &inregs, &outregs);
	*array_size = outregs.h.al;
	return (outregs.h.ah);
}
