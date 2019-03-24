#include "_rsa.h"
#include "rsa.h"

void far *normalize_address(unsigned seg, unsigned ofs)
{
	unsigned long physical_address = MK_LA(seg, ofs);			
	unsigned new_seg = (unsigned)(physical_address >> 4);
	unsigned new_ofs = (unsigned)(physical_address & 0xf);
	return MK_FP(new_seg, new_ofs);
}
