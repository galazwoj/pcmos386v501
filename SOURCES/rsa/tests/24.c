#include "rsa.h"
#include <string.h>

int main(void)
{
	int drive =3;
	char label_name[15];
	int error;
	memset(label_name, 0, 15);
	strcpy(label_name, "mylabel");
	if((error=set_volume_label(drive, label_name)))
	{
		printf("error %d setting volume label", error);	
		return 1;
	}
	else                                                                           
		puts("volume label set");	

	memset(label_name, 0, 15);
	if((error = get_volume_label(drive, label_name)))
		printf("error %d retrieving volume label", error);	
	else
		printf("drive %c, volumne label '%s'\n", drive +'A'- 1, (strlen(label_name) > 0) ? label_name : "no label");
	return 0;
}
