#include "rsa.h"
#include <stdio.h>

static char str1[] = "(C) Copyright 1990,1991 - The Software Link, Inc.";
static char str2[] = "All Rights Reserved.\n";

void  display_copyright(char *str)
{
	puts(str);
	puts(str1);
	puts(str2);
}
