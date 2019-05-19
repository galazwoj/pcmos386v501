#include "_rsa.h"
#include "rsa.h"
#include <stdlib.h>

void    USR_clear(int field)
{
	int cursor_pos = rdcpos();		// 2
	int i;				// 8
	if (field == -1)
	{
		USR_clear_message();
		for (i = 0; i < MAX_FILES2; i++)
		{
			int f = field_ids[i];
			if (f == 0x3e6 || f == 0x3e7)
				continue;
			if (f != 0)
			 	_$Clear_the_field(i);
		}	
	} else
	{
		for (i = 0; i < MAX_FILES2; i++)
		{
			if (field == abs(field_ids[i]))
			{
				_$Clear_the_field(i);
				break;	
			}	
		}
	}
	put_cpos(cursor_pos);
}

void	_$Clear_the_field(int field)
{
	int fl;         // 2
	int fp;		// 4
	int fa;		// 6

 	fp = abs(field_position[field]);
	fl = field_length[field];
	fa = field_attrib[field];
#ifndef	ORIGINAL_CODE
	if (is_color_video() == VIDEO_MONO)	
#else
	if (is_color_video() != VIDEO_MONO)	
#endif
	 	fa = convert_to_mono(fa);
	if ((fa & 0x70) == 0)
		fa = _$menu_color & 0x70;		
	scr(2, fp, fl, fa); 
}
