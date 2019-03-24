#include "_rsa.h"
#include "rsa.h"

void  	USR_disconnect(void)
{
	da_close(fp_menu);
	da_close(fp_help);
}
