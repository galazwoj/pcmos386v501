#include "rsa.h"
#include <dos.h>

int main(void)
{
	char path[80];
	int attributes =  _A_RDONLY;
	int error = set_tree("my\\dir");
	printf("%d\n", error);

	if(!error)
		error = walk_tree(path, &attributes);
	printf("%d\n", error);
	if(!error)
		puts(path);

	return 0;
}

