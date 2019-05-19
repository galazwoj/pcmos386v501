#include "_rsa.h"
#include "rsa.h"
#include <string.h>

int     USR_menu(int menu_id, int color)
{
	int r1, r2;		// 2,4
	int record_pos;		//  6
	int r3;			//  8	
	int i;                 	// 0a

	if(!fp_menu)
		return -2;
	USR_clear_message();
	current_time.year    = 0;
	current_time.month   = 0;
	current_time.day     = 0;
	current_time.hour    = 0;
	current_time.minute  = 0;
	current_time.second  = 0;
	current_time.msecond =99;
			
	for (i=0; i < max_menus; i++)
		if (menu_ids[i] == menu_id)
			break;
	if ( i>= max_menus)
		return -2;
	
	record_pos = i * 0x2d + 5;
	da_read(fp_menu, &field_ids[0]		,record_pos   );
	da_read(fp_menu, &field_position[0]	,record_pos+ 1);
	da_read(fp_menu, &field_type[0]		,record_pos+ 2);
	da_read(fp_menu, &field_length[0]       ,record_pos+ 3);
	da_read(fp_menu, &field_attrib[0]       ,record_pos+ 4);
	da_read(fp_menu, &field_ids[40]         ,record_pos+ 5);
	da_read(fp_menu, &field_position[40]    ,record_pos+ 6);
	da_read(fp_menu, &field_type[40]        ,record_pos+ 7);
	da_read(fp_menu, &field_length[40]      ,record_pos+ 8);
	da_read(fp_menu, &field_attrib[40]      ,record_pos+ 9); 
	da_read(fp_menu, &field_ids[80]         ,record_pos+10);
	da_read(fp_menu, &field_position[80]    ,record_pos+11);
	da_read(fp_menu, &field_type[80]        ,record_pos+12);
	da_read(fp_menu, &field_length[80]      ,record_pos+13);
	da_read(fp_menu, &field_attrib[80]      ,record_pos+14);
	da_read(fp_menu, &field_ids[120]       	,record_pos+15);
	da_read(fp_menu, &field_position[120]  	,record_pos+16);
	da_read(fp_menu, &field_type[120]      	,record_pos+17);
	da_read(fp_menu, &field_length[120]    	,record_pos+18);
	da_read(fp_menu, &field_attrib[120]   	,record_pos+19);      

	r1 = record_pos + 20;
	r2 = r1 + 24;
	for (r3=r1; r3 <=r2; r3++)  	
		da_read(fp_menu, &menu_text[(r3-r1)*0x50], r3);

	if (is_color_video() == VIDEO_MONO)
	{
		if (color != 0)
			color = convert_to_mono(color);
		for (i=0; i < MAX_FILES2; i++)
	         	field_attrib[i] = convert_to_mono(field_attrib[i]);
	}

	if (color != 0)
		_$menu_color = color;
	putscr(menu_text, _$menu_color);	
	update_time_and_date();
	put_cpos(0x0a14);
	return 1;
}
			