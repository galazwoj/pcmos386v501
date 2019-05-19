#include "rsa.h"

#define MAKELONG( seg,ofs )  (unsigned long)(((unsigned long)(seg) << 16) + (unsigned long)(ofs))

int main(void)
{
	unsigned long addr1 = MAKELONG(0x6EF5L, 0x1234L); 
 	unsigned long absaddr = segment_to_absolute(addr1);
	void far * addr2;
	printf(" %x:%x %lx \n", (unsigned)(addr1 >> 16),(unsigned)(addr1), absaddr);	
 	addr2 = absolute_to_segment(absaddr);
	printf(" %p %lx \n", addr2, absaddr);	
	return 0;
}
