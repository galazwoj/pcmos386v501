#include "rsa.h"
#include <string.h>

char buf[10] = {'?','1','2','3','4','5','6','7','8','9'};

int main(void)
{
	FILE *file;

	if (!(file = da_open("da_test.bin", "w+b", 10)))
	{
		puts("da_copen wrong");
		return 1;
	}
	
	buf[0] = 'a';
	if(!da_write(file, buf, 0))
	{
		puts("da_write 0, wrong");
		if(!da_close(file))
			puts("da_close, wrong");
		return 1;
	}	

	buf[0] = 'b';
	if(!da_write(file, buf, 1))
	{
		puts("da_write 1, wrong");
		if(!da_close(file))
			puts("da_close, wrong");
		return 1;
	}	

      	buf[0] = 'c';
	if(!da_write(file, buf, 2))
	{
		puts("da_write 2, wrong");
		if(!da_close(file))
			puts("da_close, wrong");
		return 1;
	}	
	
	memset(buf, 0, 10);
	if(!da_read(file, buf, 1))
		puts("da_read, wrong");
	else
	{
		puts("da_read, ok");		
		printf("%c%c%c%c%c%c%c%c%c%c\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], buf[8], buf[9]);
	}
	if(!da_close(file))
	{
		puts("da_close, wrong");
		return 1;
	}
	return 0;
}
