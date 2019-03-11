#include "rsa.h"
#include "_rsa.h"

static char EMS_id[] = " EMMXXXX0";
#define EMS_id_SIZE	8

int     EMM_present(void)
{
	int i = 0;
	void far *vect_ptr = MK_FP(0, INTR_EMS * 4);
	char far *device_name = (char far*)vect_ptr + 0x0a;
	while (i < EMS_id_SIZE) 
		if (EMS_id[i++] != *device_name++)
			return 0;		
	return 1;
}
