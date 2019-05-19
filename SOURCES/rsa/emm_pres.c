#include "_rsa.h"
#include "rsa.h"

char EMS_id[] = "EMMXXXX0";
#define EMS_id_SIZE	8		// size dows not include trailing '\0'

int     EMM_present(void)
{
	int i;
	unsigned long far *EMS_seg = MK_FP(0, INTR_EMM * 4);
	char far *device_name = MK_FP((*EMS_seg) >> 16, 0x0a);
	for (i=0; i < EMS_id_SIZE; i++) 	
		if (EMS_id[i] != device_name[i])
			return EMM_NOT_PRESENT;		
	return EMM_PRESENT;
}

