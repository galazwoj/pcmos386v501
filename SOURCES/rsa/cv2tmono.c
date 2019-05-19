#include "rsa.h"

int   	convert_to_mono(int attribute)
{
	if (((char)attribute & 7))
	{
		attribute &= 0x88; 	
		attribute |= 0x07; 	
	} else {
		attribute &= 0x88; 	
		attribute |= 0x70; 	
	}
	return attribute;
}
