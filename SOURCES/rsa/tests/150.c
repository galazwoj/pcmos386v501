#include "rsa.h"

int main(void)
{
	int cursor_poss =  1 * 100 +  1;
	int dcursor_pos = 11 * 100 + 11;
	int cursor_posr =  5 * 100 + 40;
	char ch, exch;
	void *screenptr;
	screenptr = save_video_region(cursor_poss, dcursor_pos);
	if (!screenptr)
	{
		puts ("memory error");
		return 1;
	}
	wait_for_key(&ch, &exch);
	restore_video_region(cursor_posr, dcursor_pos, screenptr);
	return 0;
}
