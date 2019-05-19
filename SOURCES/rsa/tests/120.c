#include "rsa.h"

int main(void)
{
	printf("%s, %u\n", "0"   , hash("0"));
	printf("%s, %u\n", "01"  , hash("01"));
	printf("%s, %u\n", "a"   , hash("a"));
	printf("%s, %u\n", ""    , hash(""));
	printf("%s, %u\n", " "   , hash(" "));
	printf("%s, %u\n", "  "  , hash("  "));
	printf("%s, %u\n", "t"   , hash("t"));
	printf("%s, %u\n", "0a"  , hash("0a"));
	printf("%s, %u\n", "123" , hash("123"));
	printf("%s, %u\n", "12z" , hash("12z"));
	printf("%s, %u\n", "12 " , hash("12 "));
	printf("%s, %u\n", " 12" , hash(" 12"));
	printf("%s, %u\n", "Welcome home" , hash("Welcome home"));
	printf("%s, %u\n", "Copyrigth Alphasoft Corporation Unlimited" , hash("Copyrigth Alphasoft Corporation Unlimited"));
	printf("%s, %u\n", "All I want is here" , hash("All I want is here"));
	return 0;
}
