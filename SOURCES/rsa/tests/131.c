#include "rsa.h"

int main(void)
{
	int error = makepath("dir\\is\\here");
	if (error)
		printf("error is %d\n", error);
	return 0;
}
