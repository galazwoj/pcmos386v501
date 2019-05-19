#include "rsa.h"

int main(void)
{
	int drive = 0;
	int cylinder = 0;
	int head = 0;
	int sector = 1;
	int num_of_sectors = 1;
	char buffer[512];
	int result = bios_disk_read(drive, cylinder, head, sector, num_of_sectors, buffer);
	printf("bios disk read: %d, %s\n", result, int13h_status(result));
	if (result == 0) 
	{
		FILE * f;
		if (!(f = fopen("sector.bin", "wb")))		
		{
			puts("cannot save sector");
			return 1;		
		}
		fwrite(buffer, 1, 512, f);
		fclose(f);
	}
	return 0;
}
