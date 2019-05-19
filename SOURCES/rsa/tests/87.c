#include "rsa.h"

int main(void)
{
	struct DATETIME dt;
	gtime(&dt);
	printf("date %d/%d/%d time %2d:%2d:%2d.%2d\n", dt.month, dt.day, dt.year, dt.hour, dt.minute, dt.second, dt.msecond);
	delay(18*2);	// 36 seconds
	gtime(&dt);
	printf("date %d/%d/%d time %2d:%2d:%2d.%2d\n", dt.month, dt.day, dt.year, dt.hour, dt.minute, dt.second, dt.msecond);
	return 0;
}
