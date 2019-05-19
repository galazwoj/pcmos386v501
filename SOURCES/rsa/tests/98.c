#include "rsa.h"

int main(void)
{
	FILE *f = fopen("newfile.txt", "w");
	if (!f)
		puts("cannot write");
	else
	{
		ffill(f, 'x', 30);
		fclose(f);
	}
	return 0;
}


