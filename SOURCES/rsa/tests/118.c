#include "rsa.h"
#include <string.h>
#include <dos.h>

int main(void)
{
	int drive =3;
	char label_name[15];
	int error;
	memset(label_name, 0, 15);
	if((error = get_volume_label(drive, label_name)))
	{
		printf("error %d getting volume label or the disc has no label", error);	
		return 1;
	}
	else
	{
		printf("drive %c, volumne label '%s'\n", drive +'A'- 1, (strlen(label_name) > 0) ? label_name : "no label");
		return 0;	
	}
}
