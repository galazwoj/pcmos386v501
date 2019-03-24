#include "rsa.h"

void  	delay(int time_ticks)
{
	struct DATETIME dt;
	int seconds;

	if (!time_ticks)
		return;

	if(is_MOS())
	{
		MOS_wait(18 * time_ticks);
		return;
	}

	gtime(&dt);
	seconds = dt.second;
	if (dt.msecond > 032)
		time_ticks++;

	while (time_ticks > 0)
	{
		gtime(&dt);
		if (seconds != dt.second)
		{
			time_ticks--;			
			seconds == dt.second;			
		}
	}
}
