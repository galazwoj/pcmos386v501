#include "rsa.h"

int main(void)
{
	printf("%s, %d\n", "0"   , htoi("0"));
	printf("%s, %d\n", "01"  , htoi("01"));
	printf("%s, %d\n", "a"   , htoi("a"));
	printf("%s, %d\n", "  "  , htoi("  "));
	printf("%s, %d\n", "t"   , htoi("t"));
	printf("%s, %d\n", "0a"  , htoi("0a"));
	printf("%s, %d\n", "123" , htoi("123"));
	printf("%s, %d\n", "12z" , htoi("12z"));
	printf("%s, %d\n", "12 " , htoi("12 "));
	printf("%s, %d\n", " 12" , htoi(" 12"));
	return 0;
}
