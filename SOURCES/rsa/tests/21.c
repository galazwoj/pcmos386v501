#include "rsa.h"

int main(void)
{
	char ch, exch;
    	while(!inkey(&ch, &exch)) 
        	if(is_MOS())
            		MOS_wait(18);

	printf("%c %c\n", ch, exch);
	return 0;
}
