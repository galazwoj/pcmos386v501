#include "rsa.h"
#include <stdlib.h>
#include <string.h>

void   	center(char *buf, unsigned len)       
{
	char *str;                       
	int k;
#ifndef ORIGINAL_CODE
	if (len <= strlen(buf) + 2)           
		return;                       
#endif  
	str = malloc(len + 1);                
#ifndef ORIGINAL_CODE
	if (!str)
		return;
#endif
	strcpy(str, buf);
	k = (len - strlen(str))/2 - 1;     
	zap(buf, len, ' ');                
	strcpy(buf + k, str);              
	free(str);                            
}                                             

#ifndef ORIGINAL_CODE
void   	center_r(char *buf, unsigned len)       
{
	char *str;                       
	int k, n;

	if (len <= strlen(buf) + 2)           
		return;                       
	if (!(str = malloc(len + 1)))
		return;
	strcpy(str, buf);
	n = strlen(str);
	k = (len - n)/2;     
	zap(buf, len, ' ');                
	strncpy(&buf[k], str, n);              
	buf[len] = '\0';
	free(str);                            
}                                             
#endif
	