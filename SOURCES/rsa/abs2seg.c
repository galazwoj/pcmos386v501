#include "_rsa.h"
#include "rsa.h"

void far *absolute_to_segment(unsigned long address)
{
	unsigned seg = (unsigned)((address & 0xf0000UL) >> 4);
	unsigned ofs = (unsigned)(address & 0xffff);
	return MK_FP(seg, ofs);
}
