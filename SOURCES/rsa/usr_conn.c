#include "_rsa.h"
#include "rsa.h"
#include <stdlib.h>
#include <string.h>

int    	USR_connect(char *menu_filename, char *hlp_filename)
{
	int record_num;                        	// 2           	//	
	char bufhlp[0x48];			// 4a
//	long count;                       	//4a-48
	int record_pos;                       	// 4c        	//
	int i;					// 4e
	char bufmenu[0x50];			// 9e		//
#define count bufhlp[0]		
	USR_disconnect();
	if(!strlen(menu_filename))
		return 0;

	if(!(fp_menu = da_open(menu_filename, "rb", 0x50)))
		return 0;

	da_read(fp_menu, bufmenu, 0);
	max_menus = (int)bufmenu[0];
	da_read(fp_menu, &menu_ids[0],   1);
       	da_read(fp_menu, &menu_ids[40],  2);
	da_read(fp_menu, &menu_ids[80],  3);
	da_read(fp_menu, &menu_ids[120], 4);

	if ((strlen(hlp_filename)) && (fp_help = da_open(hlp_filename, "rb", 0x48)))
	{		
		// reads number of records
       		da_read(fp_help, &count, 0);
		_$hp_list = (struct HP_LIST *)calloc((int)count*12, sizeof(struct HP_LIST));
		record_num = 0;
		record_pos = 1;
		for (i=0; i < (int)count; i++)
		{
			// reads 12 records at once 
		 	da_read(fp_help, &_$hp_list[record_num] ,record_pos);
			record_pos ++;
			record_num += 12;
       		}
		_$help_count = (int)count;
	}
	else
	 	fp_help = 0;
			
	USR_flags = 0;
	if (is_color_video() != VIDEO_MONO)
		USR_flags |= 2;
       	set_standard_colors();
	return 1;
}
										