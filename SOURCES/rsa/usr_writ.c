#include "_rsa.h"
#include "rsa.h"
#include <stdlib.h>

int  	USR_write(int field_id, void *src_buf, int clear_row, int color)
{
	long * s1;		//  2
	int ft;			//  4
	int cursor_pos;     	//  6
	int fl;                 //  8
	int fp;			// 0a
	float *s2;             	// 0c
	int i;                  // 0e
				// 10
	int *s3;               	// 12

	s1 = (long *)src_buf;
	s2 = (float *)src_buf;
	s3 = (int *)src_buf;
	cursor_pos = rdcpos();
                        
	for (i=0; i < MAX_FILES2; i++)
	{
	 	if (field_id != abs(field_ids[i]))
			continue;
		fp = abs(field_position[i]);				
		ft = field_type[i];
		fl = field_length[i];
		if (color == 0)
			color = field_attrib[i];
		if (color == -1)
		{			
			switch (ft)
			{
				case I2_FIELD:	// L1
					if (*s3 <= 0)	
						color = 4;
					break;
				case IL_FIELD:	// L5
					if (*s1 <= 0)
						color = 4;
					break;
				case FLOAT_FIELD: // L6  
					if (*s2 <= (float)0)
						color = 4;
					break;
				default: // L13
					color = field_attrib[i];
			}
		}

                        
		if (is_color_video() == VIDEO_MONO)	
			color = convert_to_mono(color);
		if (!(color & 0x70))
			color |= (_$menu_color & 0x70);			
		put_field(clear_row, ft, fp, fl, color, src_buf);
		put_cpos(cursor_pos);
		return 1;
	}
	return 0x0fffc;
}
