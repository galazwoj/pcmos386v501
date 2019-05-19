#include "_rsa.h"       	

void   	dump_buffer_to_screen(unsigned char *buf, int length)
{
	int  i;	
	int  k; 

	for (i=0; i < length; i+=0x10)
	{
	 	int x = (length -1 <= i + 0xf) ? length -1 : i + 0xf;
		for (k=i; k <= x; k++)
		{
			if(k == 0 || k == i)
				printf("%04X:  %02X ",	k, buf[k]); 		
			else
				printf("%02X ",buf[k]);				
		}
		if (length -1 == x)
			for (k=0; k < i-x + 0xf; k++)
			 	printf("   ");
		printf("---- ");
		for (k = i; k <= x; k++)
			printf("%c", (buf[k] < 0x20 || buf[k] > 0x7e) ? '.' : buf[k]);
		puts("  ");	
	}
	puts(" ");
}
