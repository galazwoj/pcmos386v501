#include "_rsa.h"
#include "rsa.h"
#include <string.h>

static int * save_video_buf = 0;	// L_54
static int pos_diff;			// L_55
static int pos;				// L_56

static char *message_title[] = {
	""
	," NOTE "
	," WARNING "
	," ERROR "
	," FATAL "
	," HELP "
	," INSTRUCTIONS "
	, "XXXX "
	,""};

int   	USR_message(int position, char **msg_buf, int msg_type, int unused, int parameter)
{
	char *str;		// -2
	int box_size;		// -4
	int cursor_pos;		// -6
	int result;		// -8
	int row;		// -0ah
	int color;		// -0ch
	int fgr_color;		// -0eh
	int x;			// -10h
	int row2;		// -12h
	int i;			// -14h
	char character;		// -16h
	int y;			// -18h
	int cursor_pos2;	// -1ah	
	char ext_character;	//  1ch
	int center1;		// -1eh
	int column;		// -20h
 	int MOS_present;	// -22h
	int bgr_color;		// -24h
	int len;		// -26h
	int column2;		// -28h
	int center2;		// -2ah

	(void)unused;
#ifndef ORIGINAL_CODE
	result = 0;
#endif
	x = 0;
	y = 2;
	MOS_present = (is_MOS() == 0) ? 0 : 1;
	cursor_pos = rdcpos();
	row    = cursor_pos / 100;
	column = cursor_pos % 100;
	USR_clear_message();
	cursor_off();
	
	i=0;
	while(len = strlen(msg_buf[i]))
	{
		y++;
		if(x < len)
			x = len;
		i++;				 			
	} 
				
	if (is_color_video() == VIDEO_MONO)
		fgr_color = bgr_color = 7;
	else
	{
		fgr_color = 0x70;
		bgr_color = 0x71;
	}
 	 	 	
	switch (msg_type)
	{			
//L$8 
       		case NONE:	str = message_title[msg_type];
			break;
//L$9 
		case NOTE:	str = message_title[msg_type];
			color = 0x71;
			break;
//L$11
		case WARNING:	str = message_title[msg_type];
			color = 0x74;
			break;
//L$12
		case ERROR:	str = message_title[msg_type];
			color = 0x7c;
			break;
//L$14
		case FATAL: 	str = message_title[msg_type];
			color = 0xfc;
			break;
//L$15
		case HELP: 	str = message_title[msg_type];
			color = 0x7c;
			break;
//L$16
		case INSTRUCTIONS: str = message_title[msg_type];
			color = 0x71;
			break;
//Lx17		
      		default: str = message_title[7];
			color = 0x70;
	}
			
        if (is_color_video() == VIDEO_MONO)	
	{
		if (color & 0x80)
			color = 0x87;
		else
			color = 7;
	}
			
	len = strlen(str);
	if (len <= x)
	{
		center2 = (x - len)/2 +2;	
		center1 = 2;	
	}
	else
	{
		center1 = (len - x)/2 +2;
		x = len;
		center2 = 2;
	}
			
	x +=4;
	box_size = x + y * 100;	
	pos_diff = box_size + 0x66;
	if(position == -1)
#if 1
                pos = (row <= 0xc) ? (column <= 0x28) ? cursor_pos + 0x65       : cursor_pos -x + 0x63
		                           : (column <= 0x28) ? cursor_pos - y * 100 +1 : cursor_pos - y * 100 -x -1;
#else
	{
		if (row <= 0xc)
      		{
			if (column <= 0x28)	
			 	pos = cursor_pos + 0x65;
			else
			 	pos = cursor_pos -x + 0x63;
		}
                if (row > 0xc) 
		{
			if (column <= 0x28)	
		        	pos = cursor_pos - y * 100 +1;
			else	
				pos = cursor_pos - y * 100 -x -1;
		}
	}
#endif
	else
	{
	 	if (position == 0)
			pos = (0x19 - y)/2 * 100 + (50-x)/2; 
		else
		{
			row2 = position / 100;
			column2 = position % 100;		 	
			if (row2 == 0)
				row2 = (0x19 - y)/2;
			if (column2 == 0)
 				column2 = (0x50 -x) /2; 
			pos = row2 * 100 + column2;
		}
	}
	save_video_buf = save_video_region(pos, pos_diff);
       	draw_box(pos, 1, box_size, bgr_color, fgr_color);	
	if ((len = strlen(str))!=0)
	{
		cursor_pos2 = center2 + pos;
		scr(2, cursor_pos2, len, color);
		dputs(str);
	}
	cursor_pos2 = 100 + center1 + pos;
	i = 0;
	while (strlen(msg_buf[i]))
	{
		put_cpos(cursor_pos2);
		dputs(msg_buf[i]);
		cursor_pos2 += 100;
		i++;
	}
	if (parameter == PAUSE_FOR_KEY)
	{
		put_cpos(0x0a14);
		if (MOS_present)
		{
			while (!inkey(&character, &ext_character))
			{
			 	update_time_and_date();
				MOS_wait(1);
			}
		} else
			while (!inkey(&character, &ext_character))
				update_time_and_date();				
			
       		USR_clear_message();
		if (!character)
			result = ext_character << 8;
		else
			result = character;	            	
	} 
	else 
	{			
	   	if (parameter != ERRMSG_KEEP )
		{
			USR_flags |=1;
			errmsg_counter = parameter;
		}
	}
	put_cpos(cursor_pos);
	cursor_on();
	return result;
}

void  	USR_clear_message( void)
{
	USR_flags |= 0xfe;                       
	errmsg_counter = 0;                      
	if (save_video_buf)                           
	{
		restore_video_region(pos, pos_diff, save_video_buf);  
		save_video_buf= 0;                                		
	}
}
                                        