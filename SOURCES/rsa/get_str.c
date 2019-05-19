#include "rsa.h"
#include <ctype.h>

int     get_string(char *buf, int num_chars, int show_char)
{
	int chars_read = 0;		//  2
	char character;             	//  6
	char ext_character;		//  8	
	int MOS_present;		// 0a

	MOS_present = (is_MOS()) ? 1: 0;
	buf[0] = '\0';

	while(1)
	{
		if(inkey(&character, &ext_character))
		{
		 	if (character == 0xd)			// Enter
				return 0xd;
		 	if (character == 3)             	// Ctrl-C
				return 3;
		 	if (character == 0x1b)     		// Esc
			{
				buf[0] = '\0';
				return 0x1b;
			}
		 	if (character == 8 && chars_read > 0)	// Backspace
			{
				dputchar(8);	
				dputchar(' ');			
				dputchar(8);	
				buf[chars_read--] = '\0';	
				continue;
			}
		 	if (!isprint(character) || chars_read >= num_chars)
			{
				if (character == 0 && chars_read == 0)	
				{
					buf[0] = ext_character;		
					return 0;
				}
			} else
			{
			 	if (show_char == 0)	
			 	     	dputchar('#');
				else
					dputchar(character);
				buf[chars_read++] = character;
				buf[chars_read] = '\0';
			}
		} else
			if(MOS_present)
				MOS_wait(1);
	}	
}
