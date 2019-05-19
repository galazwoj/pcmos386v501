#include "rsa.h"
#include <dos.h>
#define MK_FP( seg,ofs ) (void far * )(((unsigned long)((unsigned long)(seg) << 16)) + ((unsigned long)(ofs)))

int main(void)
{
	void far * addr1 = MK_FP(0x6EF5, 0x1234); 
 	unsigned seg = FP_SEG(addr1);
	unsigned ofs = FP_OFF(addr1);
 	void far * addr2 = normalize_address(seg, ofs);
	printf(" %p %p \n", addr1, addr2);	
	return 0;
}
