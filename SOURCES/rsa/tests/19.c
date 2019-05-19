#include "rsa.h"

int main(void)
{
	char *filename = "sample.txt";
	struct DATETIME dt;
	get_file_date(filename, &dt);
	printf("date %d/%d/%d time %d:%d:%d\n", dt.month, dt.day, dt.year, dt.hour, dt.minute, dt.second);
	dt.second = (dt.second > 30) ? 10 : 50;
	set_file_date(filename, &dt);
	get_file_date(filename, &dt);
	printf("date %d/%d/%d time %d:%d:%d\n", dt.month, dt.day, dt.year, dt.hour, dt.minute, dt.second);
	return 0;
}
