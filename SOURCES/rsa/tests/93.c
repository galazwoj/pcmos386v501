#include "rsa.h"

int main(void)
{
	char ch, exch;
     	draw_box(525, 3, 640, _$bcolor, _$fcolor);
	wait_for_key(&ch, &exch);
	draw_box(318, 1, 1944, _$bcolor, _$fcolor);
	wait_for_key(&ch, &exch);
     	draw_box(1025, 2, 432, _$bcolor, _$fcolor);
	wait_for_key(&ch, &exch);
     	draw_box(825, 3, 1440, _$bcolor, _$fcolor);
	return 0;
}
