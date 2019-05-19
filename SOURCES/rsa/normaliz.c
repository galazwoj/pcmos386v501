#include "_rsa.h"
#include "rsa.h"

void far *normalize_address(unsigned seg, unsigned ofs)
{
	unsigned long address = MK_LA(seg, ofs);			
	unsigned new_seg = (unsigned)((address & 0xf0000UL) >> 4);
	unsigned new_ofs = (unsigned)(address & 0xffff);
	return MK_FP(new_seg, new_ofs);
}
