#include "rsa.h"

void wait_for_key(char *character, char *ext_character)
{
	if(is_MOS())
	{
		if(!inkey(character, ext_character))
			MOS_wait(1);
	} else 
		while (!inkey(character, ext_character))
			;
}
