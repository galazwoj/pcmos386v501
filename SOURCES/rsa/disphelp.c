#include "_rsa.h"
#include "rsa.h"
#include <stdlib.h>
#include <string.h>

int   	display_help(char *help, int pos)
{
	int imax2;			// 2
	char * msg_list[10];		// 20 - 1a
	int cursor_pos2;		// 22
	int cursor_pos;			// 24
	unsigned hash_help;             // 26
	int *video_buf;			// 28
	int imin2;                      // 2a
	int cursor_pos3;		// 2c
	int length;			// 2e
	int size_help;			// 30
	int i;				// 32
	int pos2;			// 34
	int imin;                      	// 36
	char buf[0x80];			// b6
	char chr;                 	// b8
	char exchr;			// ba
	int cursor_pos4;		// bc 
	int imax;			// be
	int MOS_present;		// c0
	int cursor_pos1;		// c2

	if (!fp_help)
	{
		msg_list[0] = "     No HELP file attached.";
		msg_list[1] = " ";
		msg_list[2] = ">> Press ANY key to continue <<";
		msg_list[3] = "";
		USR_message(0, msg_list, 1, 0, -2);
		return -9;
	}
	zap(buf, 0x80, 0);
	MOS_present = (is_MOS()) ? 1: 0;		
	hash_help = hash(help);

	for(i = 0; i< _$help_count; i++)
	 	if (_$hp_list[i].a0 == hash_help)
			break;

	if (i == _$help_count)
	{
		msg_list[0] = ">> HELP message NOT found <<";			
#ifndef ORIGINAL_SOURCE
		sprintf(buf, "Help topic '%s'", help);
#else
		sprintf(buf, "TAG = $$%s", help);
#endif
		msg_list[1] = buf;		
		msg_list[2] = "";
		USR_message(0xca, msg_list, 2, 0, 5);
		return -9;	
	}
              
	imin2 = _$hp_list[i].a1;
	size_help = _$hp_list[i].a2;
	imax2 = imin2 + size_help -1;
	imin = imin2;
	imax = imin2 + pos -1;		
	if (imax > imax2)
	{
	 	imax = imax2;
		pos = imax -imin + 1;
	}
	pos2 = pos + 2;
	if (strlen(" HELP ") > strlen(" ESC=EXIT "))
	 	length = strlen(" HELP ");
	else
		length = strlen(" ESC=EXIT ");	
	
	for (i = imin2; i <= imax2; i++)
	{
		da_read(fp_help, buf, i);
		if (strlen(buf)	>= length)
		 	length = strlen(buf);
	}	
	length +=4;
	cursor_pos2 = pos2 * 100 + length;
	cursor_pos1 = (0x19 - pos2)/2 * 100 + (0x50 - length)/2;
	cursor_pos4 = cursor_pos1 + 0x66 ;
	cursor_pos3 = cursor_pos1 + pos2 * 100 - 0xc6;
	cursor_off();
	video_buf = save_video_region(cursor_pos1, cursor_pos2 + 0x66); 		
	draw_box(cursor_pos1, 4, cursor_pos2, _$bcolor, _$fcolor);	
	cursor_pos = (length - strlen(" HELP ")) / 2 + cursor_pos1;
	scr(2, cursor_pos, strlen(" HELP "), _$hcolor);		
	dputs(" HELP ");
	cursor_pos = (length - strlen(" ESC=EXIT ") )/2 + pos2 * 100 + cursor_pos1 -100;
	scr(2, cursor_pos, strlen(" ESC=EXIT "), _$tcolor);	
	dputs(" ESC=EXIT ");
	cursor_pos = cursor_pos4;
	for (i=imin; i <= imax; i++)
	{
		da_read(fp_help, buf, i);
		put_cpos(cursor_pos);	
		dputs(buf);	
		cursor_pos += 100;
	}	
	while(1)
/*17*/	{
		cursor_pos = cursor_pos1 + length +0x63;
		if (imin <= imin2)
			scr(4, cursor_pos, 1, _$bcolor);	
		else
			scr(4, cursor_pos, 1, _$asa_color);	
		dputchar(0x18);
		cursor_pos = pos2 * 100 + cursor_pos1 + length -0xc9;	
		if (imax >= imax2)
			scr(4, cursor_pos, 1, _$bcolor);	
		else
			scr(4, cursor_pos, 1, _$asa_color);	
		dputchar(0x19);

		while (!inkey(&chr, &exchr))
		{
			update_time_and_date();
			if (MOS_present)
				MOS_wait(1);	
		}
		if (chr == 0x1b)
		{
			restore_video_region(cursor_pos1, cursor_pos2 + 0x66, video_buf);
			cursor_on();
			return 0;
		}
/*25*/		if (chr != 0)
			continue;
/*26*/			
		switch(exchr)
		{		
			case 0x50:
				if(imax != imax2)
				{
					scroll(cursor_pos1+0x66, cursor_pos2-0xcc, 1, _$fcolor, 0);
					imin++;
					imax++;
					da_read(fp_help, buf, imax);
					put_cpos(cursor_pos3);
					dputs(buf);
				}
				break;
/*28*/			case 0x48: 
				if(imin != imin2)
				{
					scroll(cursor_pos1+0x66, cursor_pos2-0xcc, 1, _$fcolor, 1);
					imin--;
					imax--;
					da_read(fp_help, buf, imin);
					put_cpos(cursor_pos4);	
					dputs(buf);
				}
				break;	
/*31*/			case 0x51: 
				if(imax != imax2)
				{
					imax +=pos;	
					if (imax > imax2)
						imax = imax2;						
					scroll(cursor_pos1+0x66, cursor_pos2-0xcc, 0, _$fcolor, 0);
					imin = imax - pos + 1;
					cursor_pos = cursor_pos4;
					for (i = imin; i <= imax; i++)
					{
						da_read(fp_help, buf, i);
						put_cpos(cursor_pos);
						dputs(buf);
						cursor_pos += 100;
					}
				}
				break;
/*38*/ 			case 0x49: 
				if(imin != imin2)
				{
					if (imin - imin2 >= pos) 
						imin -= pos;
					else
						imin = imin2;
					imax = imin + pos -1;							
					scroll(cursor_pos1+0x66, cursor_pos2-0xcc, 0, _$fcolor, 0);					
					cursor_pos = cursor_pos4;
					for(i = imin; i <= imax; i++)	
					{
						da_read(fp_help, buf, i);
						put_cpos(cursor_pos);
						dputs(buf);
						cursor_pos += 100;
					}										
				}
				break;
/*46*/ 			case 0x47: 
				if(imin != imin2)
				{
					imin = imin2;
					imax = imin2 + pos -1;
					scroll(cursor_pos1+0x66, cursor_pos2-0xcc, 0, _$fcolor, 0);					
					cursor_pos = cursor_pos4;
					for(i = imin; i <= imax; i++)	
					{
						da_read(fp_help, buf, i);
						put_cpos(cursor_pos);
						dputs(buf);
						cursor_pos += 100;
					}
				}       
				break;          	
/*52*/ 			case 0x4f: 
				if(imax != imax2)
				{
					imax = imax2;
					imin = imax - pos + 1;				
					scroll(cursor_pos1+0x66, cursor_pos2-0xcc, 0, _$fcolor, 0);					
					cursor_pos = cursor_pos4;
					for(i = imin; i <= imax; i++)	
					{
						da_read(fp_help, buf, i);
						put_cpos(cursor_pos);
						dputs(buf);
						cursor_pos += 100;
					}
				}
				break;
			default:
				;
	        }
	}
}
