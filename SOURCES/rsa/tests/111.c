#include "rsa.h"

char *cpu_name[] = {"8086", "80186" , "80286" , "80386" , "80486"};

int main(void)
{
	int n;
	printf("%s\n", ((n = get_CPU_type()) <= 4) ? cpu_name[n] : "unknown");
	return 0;
}
