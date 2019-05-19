#include "_rsa.h"
#include "rsa.h"

int main(void)
{
	int i;

	for (i=0; i < 12; i++)
		printf("%d ",ndays[i]);
	puts("");
	for (i=0; i < 12; i++)
        	printf("%s ", months[i]);
	puts("");	
	printf("%d\n", max_menus);
	printf("%d\n", errmsg_counter);
	printf ("%d %d %d %d %d %d %d\n", current_time.year, current_time.month, 
			current_time.day, current_time.hour, current_time.minute, current_time.second, current_time.msecond);
	printf("%d\n", 	USR_flags);
	printf("%d\n", _$help_count);
	printf("%d\n", _$video_address);
	printf("%d\n", _$fcolor);
	printf("%d\n", _$bcolor);
	printf("%d\n", _$hcolor);
	printf("%d\n", _$tcolor);
	printf("%d\n", _$hi_color);	
	printf("%d\n", _$bar_color);
	printf("%d\n", _$asa_color);	
	printf("%d\n", _$menu_color);
	printf("%d\n", _$ml_color);
	printf("%d\n", _$CGA_mode);
}
