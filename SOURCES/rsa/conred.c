#include "rsa.h"
#include <ctype.h>

int     conred(char *buf, int length, int color, int show_char)
{
 	int numchars;					//  2
	int cursor_pos;					//  4
	char character;					//  8
	char ext_character;				// 0a
	int MOS_present;				// 0c

	MOS_present = (is_MOS() == 0) ? 0 : 1;	
	numchars = 0;
	buf[0] = '\0';	

	while(1)
	{
		while (!inkey(&character, &ext_character))
		{
			update_time_and_date();		
			if (MOS_present)	
				MOS_wait(1);
		}

		// special cases first
		if (character != 8)		
			USR_clear_message();
		if (character == 0xd || character == 3) 	// Enter || CtrlC				
			return character;
		if(character == 0x1b)                     	// ESC
		{
			buf[0] = '\0';	
			return character;
		}		
		if (character == 8 && numchars > 0)		 	// Backspace
		{
		 	dputchar(8);
			dputchar(' ');	
		 	dputchar(8);
			buf[numchars--] = '\0';
			continue;
		}

		//regular input
		if (isprint(character) && numchars < length)	
		{
			int ch;
			if (!numchars)	
			{
			 	cursor_pos = rdcpos();
				scr(2, cursor_pos, length, color);
			}	 
			ch = (show_char == 0) ? '#': character; 
			dputchar(ch);
			buf[numchars++] = character;	
			buf[numchars] = '\0';
			continue;
		} 

		if (character == 0 && numchars == 0)	              	// exended key
		{
		       	buf[0] = ext_character;
		  	return 0;
		}
	}			
}
			