#include "rsa.h"

int main(void)
{
	int cursor_pos1 = 10 * 100 + 20;
	int cursor_pos2 = 20 * 100 + 30;
	int cursor_pos3 =  5 * 100 + 40;
	int cursor_pos4 = 15 * 100 + 50;
	char ch, exch;
	wait_for_key(&ch, &exch);
	scroll(cursor_pos1, cursor_pos2, 10, _$hcolor, SCROLL_UP);
	wait_for_key(&ch, &exch);
	scroll(cursor_pos3, cursor_pos4, 10, _$asa_color, SCROLL_DOWN);
	return 0;
}
