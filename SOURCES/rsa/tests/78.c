#include "rsa.h"

int main(void)
{
	char ch, exch;
	wait_for_key(&ch, &exch);
	cursor_off();
	wait_for_key(&ch, &exch);
	cursor_on();
	wait_for_key(&ch, &exch);
	return 0;
}
