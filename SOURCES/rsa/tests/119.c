#include "rsa.h"

int main(void)
{
	struct DATETIME dt;
	gtime(&dt);
	printf("date %d/%d/%d time %d:%d:%d.%d\n", dt.month, dt.day, dt.year, dt.hour, dt.minute, dt.second, dt.msecond);
	return 0;
}
