#include "rsa.h"

int main(void)
{
	char ch, exch;
	int cursor_pos = rdcpos();
	wait_for_key(&ch, &exch);
	cursor_pos += 20;
	put_cpos(cursor_pos);
	wait_for_key(&ch, &exch);
	return 0;
}
