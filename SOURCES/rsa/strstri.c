#include "rsa.h"
#include <string.h>
#include <stdlib.h>

#define NULL	(void *)0

char        *strstri(char *str1, char *str2)
{
	int k12;
	char *s1, *s12, *s2;
	int n1 = strlen(str1);
	int n2 = strlen(str2);
	if (n1 == 0 || n2 == 0)
		return NULL;

	s1 = malloc(n1+1);
	s2 = malloc(n2+1);		 
	strcpy(s1, str1);
	strcpy(s2, str2);	
	strupr(s1);
	strupr(s2);	

	if (! (s12 = strstr(s1, s2)))
	{
		free(s1);
		free(s2);
		return NULL;
	}

	k12 = s12 - s1;	
	s12 = str1 + k12;
	free(s1);
	free(s2);
	return s12;
}