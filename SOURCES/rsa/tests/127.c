#include "rsa.h"

int main(void)
{
	printf("Is PC-MOS running? %s\n", (is_MOS() == 0)? "NO" : "YES");
	return 0;
}
