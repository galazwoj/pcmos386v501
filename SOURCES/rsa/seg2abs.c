#include "_rsa.h"
#include "rsa.h"

unsigned long 	segment_to_absolute(unsigned long segment_address)
{
	unsigned seg = FP_SEG(segment_address);
	unsigned ofs = FP_OFF(segment_address);
	return MK_LA(seg, ofs);
}
