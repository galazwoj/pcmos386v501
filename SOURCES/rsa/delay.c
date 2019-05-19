#include "rsa.h"

// time tick is in seconds

void  	delay(int time_ticks)	
{
	int second;
	struct DATETIME dt;

	if (!time_ticks)
		return;

	if(is_MOS())
	{
		MOS_wait(18 * time_ticks);
		return;
	}

	gtime(&dt);
	second = dt.second;
	if (dt.msecond > 50)
		time_ticks++;

	while (time_ticks > 0)
	{
		gtime(&dt);
		if (second != dt.second)
		{
			time_ticks--;			
			second = dt.second;			
		}
	}
}
