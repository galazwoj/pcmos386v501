#include "rsa.h"

int main(void)
{
	char ch, exch;
	scr(CLEARSCREEN, 0, 0, _$hcolor);
	wait_for_key(&ch, &exch);
	scr(SET_CURSOR, 20 * 100 + 20, 0, 0);
	wait_for_key(&ch, &exch);
	scr(CLEARROW, 20 * 100 + 20, 10, _$asa_color);
	wait_for_key(&ch, &exch);
	scr(CLEARCOLUMN, 10 * 100 + 10, 10, _$bar_color);
	wait_for_key(&ch, &exch);
	scr(CHANGEATTRIBUTE, 18 * 100 + 20, 10, _$bar_color);
	wait_for_key(&ch, &exch);
	return 0;
}

