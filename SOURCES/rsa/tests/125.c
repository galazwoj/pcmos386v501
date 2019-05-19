#include "rsa.h"

int main(void)
{
	char ch = 1; 
	char exch = 2;
	input(&ch, &exch);
	printf("'%c', %d, %d\n", ch, ch, exch);
	return 0;
}
