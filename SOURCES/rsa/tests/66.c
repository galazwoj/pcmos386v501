#include "rsa.h"

int main(void)
{
	int drive = 0;
	int cylinder = 0;
	int head = 0;
	int sector = 1;
	int num_of_sectors = 1;
	char buffer[512];
	int result;
	FILE * f;
	
	if (!(f = fopen("sector.bin", "rb")))		
	{
		puts("cannot read sector");
		return 1;		
	}
	fread(buffer, 1, 512, f);
	fclose(f);

	result = bios_disk_write(drive, cylinder, head, sector, num_of_sectors, buffer);
	printf("bios disk write: %d, %s\n", result, int13h_status(result));
}
