#include "rsa.h"

void set_standard_colors(void)
{
	if (is_color_video() == VIDEO_MONO)
	{
		_$fcolor	= 7;
		_$bcolor	= 7;
		_$hcolor	= 0x0f;
		_$tcolor	= 0x0f;
		_$hi_color	= 0x0f;
		_$bar_color	= 0x70;
		_$asa_color	= 0x70;
		_$menu_color	= 7;
		_$ml_color	= 7;
	} else {
		_$fcolor	= 0x70;
		_$bcolor	= 0x71;
 		_$hcolor	= 0x7c;
 		_$tcolor	= 0x71;
		_$hi_color	= 0x0e;
		_$bar_color	= 0x30;
		_$asa_color	= 0x17;
		_$menu_color	= 0x1f;
		_$ml_color	= 0x1e;
	}
}
