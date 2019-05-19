#include "rsa.h"
#include <ctype.h>

void  	input(char *character, char *ext_character)
{
	while (!inkey(character, ext_character))
		update_time_and_date();
	if (*character == 8)
	{
		putchar(*character);
		putchar(' ');      		
		putchar(*character);
		return;
	}
	if(isprint(*character))
		putchar(*character);
}
	
