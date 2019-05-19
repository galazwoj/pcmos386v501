#include "rsa.h"
#include <string.h>
#include <dos.h>

int get_volume_label(int drive, char *label_name)
{
	char filename[14];							
	char path[66];                                                  
	int  attribute;								

	int result;

	if(!drive)							
	{                                                               
		get_current_path(path);				        
		puts(path);
		strcpy(path+2,"\\*.*");                                 

	} else                                                          
		sprintf(path, "%c:\\*.*", drive + 'A' - 1);             
#ifdef DEBUG
	puts(path);		                                                       	
#endif
	result = find_first_file(path, filename, &attribute);           
#ifdef DEBUG
#define	isa(attr, ATTR, label)	(((attr) & (ATTR)) == (ATTR)) ? (label) : ' '
	printf("(%d) '%s' %d [%c%c%c%c%c%c]\n", result, filename, attribute,	                                                                		
		isa(attribute, _A_ARCH  , 'A'), isa(attribute, _A_SUBDIR, 'D'),	isa(attribute, _A_VOLID , 'V'), 
		isa(attribute, _A_SYSTEM, 'S'),	isa(attribute, _A_HIDDEN, 'H'), isa(attribute, _A_RDONLY, 'R'));
#endif
	while (result)                                              	
	{                                                               
		if ((attribute & _A_VOLID) == _A_VOLID)     			// if attribute == volume label
		{                                                      	
			squeeze(filename, '.');                         
			puts(label_name);
			strcpy(label_name, filename);                        
			return 0;                                       
		}                                                       
               	result = find_next_file(filename, &attribute);         	
#ifdef DEBUG
		printf("(%d) '%s' %d [%c%c%c%c%c%c]\n", result, filename, attribute,	                                                                		
			isa(attribute, _A_ARCH  , 'A'), isa(attribute, _A_SUBDIR, 'D'),	isa(attribute, _A_VOLID , 'V'), 
			isa(attribute, _A_SYSTEM, 'S'),	isa(attribute, _A_HIDDEN, 'H'), isa(attribute, _A_RDONLY, 'R'));
#endif
	}		                                               	
	return 1;                                        		
}
