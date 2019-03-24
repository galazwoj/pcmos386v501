#include "rsa.h"
#include <string.h>

int get_volume_label(int drive, char *label_name)
{
	char filename[14];							
	char path[66];                                                  
	int  attribute;								

	int result;

	if(!drive)							
	{                                                               
		get_current_path(path);				        
		strcpy(path+2,"\\*.*");                                 
	} else                                                          
		sprintf(path, "%c:\\*.*", drive + 'A' - 1);             
		                                                       	
	result = find_first_file(path, filename, &attribute);           
	                                                                		
	while (result)                                              	
	{                                                               
		if (attribute == 8)     			// if attribute == volume label
		{                                                      	
			squeeze(filename, '.');                         
			strcpy(label_name, filename);                        
			return 0;                                       
		}                                                       
               	result = find_next_file(filename, &attribute);         	
	}		                                               	
	return 1;                                        		
}
                                          
