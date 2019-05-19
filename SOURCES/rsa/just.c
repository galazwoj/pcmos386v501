#include "rsa.h"
#include <string.h>

void just(char *buf,int length,int mode)
{
  	int k;
  	int i;
  	int j;

#ifndef	ORIGINAL_CODE
	if (!buf || !length || strlen(buf) < length)
		return;
#endif
  
  	k = length -1;
	if (k == 0)
		return;
	if (mode != JUST_LEFT && mode != JUST_RIGHT)
		return;

	if (mode == JUST_LEFT) 
	{
		for (j=0; j < length; j++) 
		{
			char c = buf[j];
			if (c > ' ' && (c <= 0x7e))                                    
			{                                                                
  				if (j == 0)                                              
    					return;
  				i = j;
  				for(j=0; j < length; j++) 
				{
   	   	  			buf[j] = buf[i];
			    		buf[j + 1] = 0;
			    		i++ ;
			    		if (i > k)                   
						return;              
			  	}
				return;			
			}			

		}
	}	
			
	if (mode == JUST_RIGHT) 
	{
		for (j=0; j < length; j++) 
		{
			char c = buf[j];
			if (c < ' ' || c > 0x7e) 
				buf[j] = ' ';
		}
		for (j = k; j>= 0; j--)  
		{
			char c = buf[j];
			if (c > ' ' && c <= 0x7e) 
			{
				if (j == k) 
					return;
				i = j;
				buf[length] = 0;
				for(j=k; j >= 0; j--) 
				{
					buf[j] = buf[i];
					buf[i] = ' ';
					i --;
					if (i < 0) 
						return;
				}
				return;
			}			
		}
	}
}
