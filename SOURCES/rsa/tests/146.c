#include "rsa.h"

int main(void)
{
	char PSP[0x100];
	FILE *f;
	read_PSP(PSP);
	dump_buffer_to_screen(PSP, 0x100);
	if((f = fopen("psp.txt","wb")))
	{	
		fwrite(PSP, 1, 0x100, f);
		fclose(f);
	}
	return 0;
}

