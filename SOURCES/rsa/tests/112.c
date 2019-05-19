#include "rsa.h"

int main(void)
{
	char path[80];
	get_current_path(path);
	printf("current path is: %s\n", path);
	return 0;
}
