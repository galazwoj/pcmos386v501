#include "rsa.h"

//
// 	NOTICE
//
// 	When regular key is pressed (i.e. not extended) then exch should be 0.
//	Unfortunamtely exch is not set to 0 by the original rsa lib in that case.
//	so results fro the org and the new libraries differ because of this. 
//	This is not a bug but a desired feature.
//

int main(void)
{
	char ch = 1; 
	char exch = 2;
	wait_for_key(&ch, &exch);
	printf("'%c', %d, %d\n", ch, ch, exch);
	return 0;
}
