#include "rsa.h"

void    convert_tabs(char *str1, char *str2, int len, int tabsize)
{
	int ts;			
	int i =0;		
	int nts = tabsize;	
	int j = 0;		

#ifndef	ORIGINAL_CODE
	if (!str1 || !str2 || !len || tabsize < 1)
		return;
#endif

	while (i < len && str1[i] != '\0')
	{
		if (str1[i] == 9)
		{
		 	ts = nts - j;
			while (ts -- > 0)
			 	str2[j++] = ' ';
			nts += tabsize;			
		} else
		{	
			str2[j++] = str1[i];
			if (j == nts)
				nts += tabsize;	
		}
		i++;
	}
	str2[j] = '\0';
}
