#include "_rsa.h"
#include "rsa.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static 	void _$Fill_option_box(int cursor_pos1, int cursor_pos2, char **opt_list, int index, int clear);
static	void _$Place_color_bar(int cursor_pos, int cursor_pos2, int length);
static	void _$Remove_color_bar(int cursor_pos, int cursor_pos2, int length);
//                       4        6         8                a        c             e             10
int  	select_option(int pos, int height, char **opt_list, int opt, char *header, char *trailer, unsigned char mask)
{
	int cursor_pos4;			//  2	
	char *msg1_list[3];			// 8 -4
	int cursor_pos5;			// 0a
	int index;				// 0c
	int dpos2;				// 0e;
	int cursor_pos;				// 10
	char buf[0x52];				// 62
	int max_option;				// 64
	int row;				// 66
	int i68;				// 68
	int length_opt;				// 6a
	int *save_video_buf;			// 6c
	char **option;				// 6e
	int i;					// 70
	int length_h;				// 72
	int row2;				// 74
	int i76;				// 76
	int i78;				// 78
	int height1;				// 7a
	int i7c;				// 7c
	int cursor_pos3;			// 7e
	char *msg_list[16];			// 90-80
	char chr;				// 92	
	int column;				// 94
	int length_t;				// 96
	char exchr;				// 98
	int buf_length;				// 9a
	int i9c;				// 9c
	int pos2;				// 9e	
	int cursor_pos2;			// a0
	int column2;				// a2

	i = 0;
	buf[0] = 0;
	
	msg_list[0] = "Select the desired  option by moving";
	msg_list[1] = "the  cursor among  the choices with ";
	msg_list[2] = "the  UP., DN.,  PGUP, PGDN,  HOME or";	
	msg_list[3] = "END  key. Press  ENTER(...) to  make";
	msg_list[4] = "the choice  or press the  ESC key to";	
	msg_list[5] = "exit.";
	msg_list[6] = " ";
	msg_list[7] = "   >> Press ANY key to continue <<";	
	msg_list[8] = "";	
	if (!strlen(trailer))
		trailer = "F1=HELP ";

	cursor_pos = rdcpos();
	row = cursor_pos / 100;
	column = cursor_pos % 100;	
	cursor_off();
	length_t = strlen(trailer) + 4;
	length_h = strlen(header) + 4;			
	if (length_h < length_t)	
		length_h = length_t;
	height1 = height + 2;
						 
	while (length_opt = strlen(opt_list[i]))
	{
		if (length_h < length_opt + 4)
			length_h = length_opt + 4;
		i++;
	}

	length_opt = i+1;
	i--;
	if (mask & HELP_DEFINED)
	{
		option = opt_list+length_opt;
		max_option = 0;
		while (strlen(option[max_option++]))
			;
	}
	if (opt > i)
		opt = i;
					
	dpos2 = height1 * 100 + length_h;
	cursor_pos2 = dpos2 -0xcc;
	index = opt / height * height; 	
	i68 = i - index;
	if (i68 >= height)
		i68 = height -1;
	cursor_pos4 = opt - index;
	if (pos == -1)
		pos2 = (row <= 0xc) ? (column <= 0x28) ? cursor_pos + 0x66		: cursor_pos - length_h + 0x62
				   : (column <= 0x28) ? cursor_pos - height1 * 100 + 2 	: cursor_pos - height1 * 100 - length_h - 2;
	if (pos == 0)
		pos2 = (0x50 - length_h)/2 + (0x19 - height1) /2 * 100;
	if (pos != 0 && pos != -1)
	{
		row2 = pos / 100; 
		column2 = pos % 100; 
		if (!row2)
			row2 = (0x19 - height1)/2;
		if (!column2)
			column2 = (0x50 - length_h)/2;
		pos2 = row2 * 100 + column2;
	}
	if (mask & RESTORE_VIDEO)
		save_video_buf = save_video_region(pos2, dpos2 + 0x66);
	if (!(mask & NO_BORDER))
	{
		draw_box(pos2, 4, dpos2, _$bcolor, _$fcolor); 
		if((length_opt = strlen(header)))
		{
		 	scr(2, pos2 + (length_h - length_opt)/2, length_opt, _$hcolor);
			dputs(header);
		}
		length_opt = strlen(trailer);
		cursor_pos3 = height1 * 100 + (length_h - length_opt)/2 + pos2 - 100; 
		scr(2, cursor_pos3, length_opt, _$tcolor);
		dputs(trailer);
	}
    	_$Fill_option_box(pos2+0x66, cursor_pos2, opt_list, index, 0);				// 24
    	_$Place_color_bar(pos2, cursor_pos4, length_h - 4);                                     // 25
	while (1)
	{ 											
xxx:		cursor_pos3 = pos2 + length_h + 0x63;                                          	// 27
		if (index <= 0)
			scr(2, cursor_pos3, 1, _$bcolor);
		else
			scr(2, cursor_pos3, 1, _$asa_color);
		dputchar(0x18);
		cursor_pos3 = length_h + pos2 + height1 * 100 - 0xc9;
		if(index + i68 >= i)
			scr(2, cursor_pos3, 1, _$bcolor);
		else
			scr(2, cursor_pos3, 1, _$asa_color);
		dputchar(0x19);
		wait_for_key(&chr, &exchr);
		USR_clear_message();
		if (chr == KEY_ESC)
		{
			_$Remove_color_bar(pos2, cursor_pos4, length_h -4);
			cursor_pos5 = -1;
			if (mask & RESTORE_VIDEO)
				restore_video_region(pos2, dpos2+0x66, save_video_buf);
			put_cpos(cursor_pos);
			cursor_on();
			return cursor_pos5;
		}
	/*34*/	if (chr == KEY_ENTER)
		{
			_$Remove_color_bar(pos2, cursor_pos4, length_h -4);
			cursor_pos5 = cursor_pos4 +index;
			if (mask & RESTORE_VIDEO)
				restore_video_region(pos2, dpos2+0x66, save_video_buf);
			put_cpos(cursor_pos);
			cursor_on();
			return cursor_pos5;
		}
	/*35*/	if (isprint(chr))
		{
			buf_length = strlen(buf);
			buf[buf_length] = chr;
			buf[buf_length+1] = 0;
			buf_length++;
			i9c = 0;
			i7c = index + cursor_pos4;
			i78 = 0;
			while (1)
			{
	/*45 42*/		if (i78 > i) 
				{ 
					if (i9c == 0)				
					{
						buf[0] = 0;
						msg1_list[0] = "     Option not found";
						msg1_list[1] = ">> Press key to continue <<";
						msg1_list[2] = "";
						USR_message(-1, msg1_list, 3, 0, -2);
					}	
					goto xxx;
				}
	/*45*/			if(strnicmp(buf, opt_list[i78], buf_length))
					i78 ++;
				else
					break;
			}                        
			if (height -1 < i)
	/*37*/		{
				i76 = i78 - index;
				if (i76 >= 0 && i76 <= i68)
				{
				 	_$Remove_color_bar(pos2, cursor_pos4, length_h -4);
					cursor_pos4 = i76;      
				}
	/*39*/			else
				{
					index = i78;	
					cursor_pos4 = 0;
					if (i68 > i- index)
						i68 = i- index;												
					_$Fill_option_box(pos2 + 0x66, cursor_pos2, opt_list, index, 1);		
				}
			}
	/*46*/		else
			{
				_$Remove_color_bar(pos2, cursor_pos4, length_h -4);
				cursor_pos4 = i78; 			
			}
	/*41*/		_$Place_color_bar(pos2, cursor_pos4, length_h -4);					
			i9c = 1;
			continue;
		}
		
	/*47*/	buf[0] = 0;

		if (chr)
			continue;

		switch(exchr)
		{
	/*48*/		case	KEY_F1:
			 	if (mask & HELP_DEFINED)
				{
				 	i7c = index + cursor_pos4;
				 	if (i7c <= max_option)	
					 	display_help(option[i7c], 0xa);
					else
						display_help("NO-HELP", 0xa);				         	
				}
				else
					USR_message(-1, msg_list, 5, 0 ,-2);
				break;	
	/*52*/		case	KEY_DOWN:
				if (cursor_pos4 < i68)
				{
					_$Remove_color_bar(pos2, cursor_pos4++, length_h - 4);
					_$Place_color_bar(pos2, cursor_pos4, length_h - 4); 
					break;
				}
				if (index + i68 < i)			
				{
				 	_$Remove_color_bar(pos2, cursor_pos4, length_h - 4);
					scroll(pos2 + 0x66, cursor_pos2, 1, _$bar_color, 0);
					put_cpos(height * 100 + pos2 + 2);
					index++;
					dputs(opt_list[index + height -1]);
				}
				break;
	/*57*/		case	KEY_UP:
				if (cursor_pos4 >0)
				{
					_$Remove_color_bar(pos2, cursor_pos4--, length_h - 4);
					_$Place_color_bar(pos2, cursor_pos4, length_h - 4); 
					break;
				}
				if (index > 0)
				{
				 	_$Remove_color_bar(pos2, cursor_pos4, length_h - 4);
					scroll(pos2 + 0x66, cursor_pos2, 1, _$bar_color, 1);
					index --;
					put_cpos(pos2 + 0x66);
					dputs(opt_list[index]);
					if (height -1 > i68)
						i68++;
				}
				break;	
	/*62*/		case	KEY_HOME:
				if(cursor_pos4 != 0 || index != 0)
				{
					if (index == 0)
					{
					 	_$Remove_color_bar(pos2, cursor_pos4, length_h - 4);
						cursor_pos4 = 0;
						_$Place_color_bar(pos2, cursor_pos4, length_h - 4); 
					}
				        else
					{
						cursor_pos4 = 0;
						index = 0;	
						_$Fill_option_box(pos2 + 0x66, cursor_pos2, opt_list, index, 1);		
						_$Place_color_bar(pos2, cursor_pos4, length_h - 4); 
					}
					i68 = i - index ;
					if (i68 >= height)
						i68 = height -1;
				}
				break;	                                               
	/*68*/		case	KEY_END:
				if(cursor_pos4 != i68 || i68 + index != i)
				{
					if(i68 + index == i && cursor_pos4 < i68)
					{
					 	_$Remove_color_bar(pos2, cursor_pos4, length_h - 4);				 	
						cursor_pos4 = i68;
						_$Place_color_bar(pos2, cursor_pos4, length_h - 4);
					}
					else 
					{
						i68 = height -1;
						if (i68 > i)
							i68 = i;
						cursor_pos4 = i68;
						index = i - i68;
					    	_$Fill_option_box(pos2+0x66, cursor_pos2, opt_list, index, 1);		
					    	_$Place_color_bar(pos2, cursor_pos4, length_h - 4);                     
					}
				}
				break;
	/*73*/		case	KEY_PGUP:
				if(cursor_pos4 != 0 || i68 + index != 0)
				{
					if (index == 0)
					{
					 	_$Remove_color_bar(pos2, cursor_pos4, length_h - 4);				 		
						cursor_pos4 = 0;	
					    	_$Place_color_bar(pos2, cursor_pos4, length_h - 4);                                  				
					}
					else
					{
						index -= height;
						if (index < 0)
						      index = 0;
						i68 = height -1;
						if (i68 >i)
							i68 = i;
					    	_$Fill_option_box(pos2+0x66, cursor_pos2, opt_list, index, 1);		
					    	_$Place_color_bar(pos2, cursor_pos4, length_h - 4);                     
					}
				}
				break;
	/*77*/		case	KEY_PGDOWN:
				if (cursor_pos4 != i68 || i68 + index != i)				
				{
					if (index + i68 == i)
					{
					 	_$Remove_color_bar(pos2, cursor_pos4, length_h - 4);
						cursor_pos4 = i68;
					    	_$Place_color_bar(pos2, cursor_pos4, length_h - 4); 
					}					
					else
					{
						index += height;
						if (index > i)
							index -= height;
						i68 = i - index;
						if (i68 > height - 1)
							i68 = height - 1;
						if (cursor_pos4 > i68)
							cursor_pos4 = i68;
						_$Fill_option_box(pos2+0x66, cursor_pos2, opt_list, index, 1);
						_$Place_color_bar(pos2, cursor_pos4, length_h - 4); 
					}				
				}
				break;
			default:				
				;
		}	
	}       
}	       
    	
void 	_$Fill_option_box(int cursor_pos1, int cursor_pos2, char **opt_list, int index, int clear)
{
	int cursor_pos;
	int pos2;		
	cursor_pos = rdcpos();
	pos2 = cursor_pos2 / 100;
	if (clear)	
	 	scroll(cursor_pos1, cursor_pos2, 0, _$fcolor, 0);
	while (strlen(opt_list[index]) && pos2-- > 0)
	{
	 	put_cpos(cursor_pos1);
		dputs(opt_list[index++]);
		cursor_pos1 += 100;
	}
	put_cpos(cursor_pos);	
}

void	_$Place_color_bar(int cursor_pos, int cursor_pos2, int length)
{
	cursor_pos += cursor_pos2 * 100 + 0x66;
	scr(4, cursor_pos, length, _$bar_color);
}

void	_$Remove_color_bar(int cursor_pos, int cursor_pos2, int length)
{
	cursor_pos += cursor_pos2 * 100 + 0x66;
	scr(4, cursor_pos, length, _$fcolor);
}
