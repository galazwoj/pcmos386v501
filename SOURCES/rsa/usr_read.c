#include "_rsa.h"
#include "rsa.h"

int  	USR_read(int field_id, void *src_buf, int clear_row, int color)
{
	int ft;			// -2
	int action;		// -4;		
	int fl;			// -6
	int fp;                 // -8
	int my_color;		// -0a
	int rd;                 // -0c
	int i;                  // -0e
	char* msg_list[3];	// 16- 12
	int MOS_present;	// 1a	
	int fa;			// 1c

	MOS_present = (is_MOS == 0) ? 0 : 1; 
                        
	for (i=0; i < MAX_FILES2; i++)
	{
	 	if (field_id == - field_ids[i])
			return -5;
	 	if (field_id == field_ids[i])
		{
			fp = field_position[i];				
			ft = field_type[i];
			fl = field_length[i];
			fa = field_attrib[i];
			if (color == 0)
				color = field_attrib[i];
                                        
			if (!(USR_flags & 2))
			{
				my_color = color & 0x88;
				color = ((color & 0x70) !=0) ? (my_color | 0x70) : (my_color | 7);
				my_color = fa & 0x88;
				fa = ((fa & 0x70) !=0) ? (my_color | 0x70) : (my_color | 7);
			}
			break;
		}		
	}	    	
	if (i == MAX_FILES2)
		return -4;
                        
	switch (clear_row)
	{
		case -1: action = 4;	
			break;
		case  0: action = 1;	
			break;
		case  1: action = 2;	
			break;
		default: ;
	}

	while((rd = readed(action, fp, ft, fl, color, src_buf)) == -7)
	{
		msg_list[0] = "Bad data entered in field.";
		msg_list[1] = "Please re-enter it.";
		msg_list[2] = "";
	 	put_cpos(fp);
		USR_message(-1, msg_list, 3, 0, 3);
	}

	if (!(fa & 0x70))
	 	fa |= _$menu_color & 0x70;
	scr(4, fp, fl, fa);					
	return rd;
}
