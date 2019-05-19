#include "rsa.h"
#include <string.h>
#include <stdlib.h>
#include <dos.h>

static int in_progress;			// l$37
static char my_path[42];                // l$38
static int dir_level;                   // l$39
static char first_DTA[0x30];            // l$40		0x30 DTA size   !!!
static char filespec[0x41];             // l$41       	0x41 path size  !!!
static char **my_DTA = 0;               // l$31
static char **save_path = 0;            // l$32

int set_tree(char *path)
{
	char ext[6];			//  6
	int result;			//  8
	int  attributes;		// 0a
	char fname[14];			// 18
	int errors = 0;			// 1a
	char drive[4];			// 20
	char dir[66];			// 62
	int i;

	_splitpath(path,drive, dir, fname, ext); 
	strcpy(my_path, dir);
	strcat(my_path, fname);
	strcat(my_path, ext);
	if(strcmp(my_path, "\\"))
	{
		if((result = get_file_attributes(path, &attributes)))
			return 1;					
		if ((attributes & _A_SUBDIR) == 0)
			return 1;	                        
		strcpy(my_path, path);
	}
	else
		strcpy(my_path, drive);
	if (my_DTA)
	{
		dir_level = -1;
		in_progress = 1;
		return 0;
	}
	if (!(save_path = calloc(0x14, sizeof(int))))
		return 2;
	if (!(my_DTA = calloc(0x14, sizeof(int))))
	{
		free(save_path);
		return 2;
	}		
	for (i=0; i < 0x14; i++)
	{
		my_DTA[i] = 0;	
		save_path[i] = 0;
	}
	for(i = 0; i < 0x14; i++)
	{
		my_DTA[i] = malloc(0x30);
		save_path[i] = malloc(0x41);	
		if (!my_DTA[i] || !save_path[i])
		{
			errors = 1;
			break;	
		}
	}
	if (!errors)
	{
		dir_level = -1;
		in_progress = 1;
		return 0;
	}		
	for(i = 0; i < 0x14; i++)
	{
		if (my_DTA[i])
			free(my_DTA[i]);
		if (save_path[i])
			free(save_path[i]);
	}
	free(my_DTA);
	free(save_path);
	return 2;
} 

int walk_tree(char *path, int *attributes)
{
	char filename[14];			// 0e
	int attribute;				// 10
	int i;					// 12	

	if(!my_DTA)
		return 1+10;
	if(in_progress)
	{
		in_progress = 0;
		strcpy(filespec, my_path);
		strcat(filespec, "\\*.*");                                	
		if(!find_first_file(filespec, filename, &attribute))
			return 1+11;
		if (strcmp(filename, ".") == 0)                   		   
		 	find_next_file(filename, &attribute);
	}
	else
		write_DTA(first_DTA, 0x30);		

	while (1)
	{
		if (!find_next_file(filename, &attribute))
		{
			if(dir_level == -1)
			{
			 	for(i= 0; i< 0x14; i++)
				{
				 	free(my_DTA[i]);
				 	free(save_path[i]);
				}
			 	free(my_DTA);                            	
			 	free(save_path);
				my_DTA = save_path = 0;			
				return 1+12;
			}
			else
			{
				write_DTA(my_DTA[dir_level], 0x30);	
				strcpy(my_path, save_path[dir_level]);
				dir_level--;	
			}
		}
		else 
		{
		 	if ((attribute & _A_SUBDIR) == 0)
			{
				strcpy(path, my_path);
				strcat(path, "\\");                             
				strcat(path, filename);
				strupr(path);
				*attributes = attribute;
				read_DTA(first_DTA, 0x30);	
			}
			else 
			{
				dir_level++;
				strcpy(save_path[dir_level], my_path);
				read_DTA(my_DTA[dir_level], 0x30);
				strcat(my_path, "\\");                     	
				strcat(my_path, filename);
				strcpy(path, my_path);		
				*attributes = attribute;
				in_progress = 1;
			}
			return 0;
		}
	}			
}
