#include "rsa.h"
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include "ctype.h"
#include <direct.h>

static char name[14];			// l$15	
static char filespec[65];             	// l$16

static void remove_directory(char *path);

#ifdef ORIGINAL_CODE
// This is the original code and it doesn't work
int killpath(char *path)
{
	char *file_buf;			//  2
	char * DTA_buf;			//  4
	char full_name[0x44];		// 46
	int attribute;			// 4a
	int length;			// 4c

	if(isalpha(path[0]) && path[1] == ':' && path[2] == '\0')
		return 1;
	if(!(DTA_buf = malloc(0x30)))
		return 2;
	if(!(file_buf = malloc(0x41)))
	{
		free(DTA_buf);
		return 2;
	}
	read_DTA(DTA_buf, 0x30);
	strcpy(file_buf, path);
	length = strlen(file_buf);
	if(file_buf[length-1] != '\\')
		strcat(file_buf, "\\");
	strcpy(filespec, file_buf);
	strcat(filespec, "*.*");
	if (!find_first_file(filespec, name, &attribute))
	{
		remove_directory(path);	 	
		write_DTA(DTA_buf, 0x30);
		free(DTA_buf);
		free(file_buf);
		return 0;
	}
	if(strcmp(name, ".") == 0)
	{
		find_next_file(name, &attribute);
		if (!find_next_file(name, &attribute))
		{
			remove_directory(path);	 	
			write_DTA(DTA_buf, 0x30);
			free(DTA_buf);
			free(file_buf);
			return 0;
		}			
	}
	while (1)
	{
	 	strcpy(full_name, file_buf);
		strcat(full_name, name);
		if ((attribute & _A_SUBDIR) != 0)
		{
			int result;               	// 48
			if ((result = killpath(full_name)) !=0)
			{
				write_DTA(DTA_buf, 0x30);
				free(DTA_buf);
				free(file_buf);
				return result;
			}
		}
		else 
		{
			if ((attribute & _A_VOLID) !=0)
		 		remove(full_name);
		}
		if (!find_next_file(name, &attribute))
		{
			remove_directory(path);	 	
			write_DTA(DTA_buf, 0x30);
			free(DTA_buf);
			free(file_buf);
			return 0;
		}			
	}
}
#else
int killpath(char *path)
{
	char *file_buf;			//  2
	char * DTA_buf;			//  4
	char full_name[0x44];		// 46
	int attribute;			// 4a
	int length;			// 4c
	int result;

	if(isalpha(path[0]) && path[1] == ':' && path[2] == '\0')
		return 1;
	if(!(DTA_buf = malloc(0x30)))
		return 2;
	if(!(file_buf = malloc(0x41)))
	{
		free(DTA_buf);
		return 2;
	}
	read_DTA(DTA_buf, 0x30);
	strcpy(file_buf, path);
	length = strlen(file_buf);
	if(file_buf[length-1] != '\\')
		strcat(file_buf, "\\");
	strcpy(filespec, file_buf);
	strcat(filespec, "*.*");
	result = find_first_file(filespec, name, &attribute);
	while (result)
	{
		if(strcmp(name, ".") != 0 && strcmp(name, "..") != 0)  
		{
		 	strcpy(full_name, file_buf);
			strcat(full_name, name);
			if ((attribute & _A_SUBDIR) != 0)
			{
				int result;               	// 48
				if ((result = killpath(full_name)) !=0)
				{
					write_DTA(DTA_buf, 0x30);
					free(DTA_buf);
					free(file_buf);
					return result;
				}
			}
			else 
				if ((attribute & _A_VOLID) == 0)
			 		remove(full_name);
		}
		result = find_next_file(name, &attribute);
	}
	remove_directory(path);	 	
	write_DTA(DTA_buf, 0x30);
	free(DTA_buf);
	free(file_buf);
	return 0;
}
#endif

static void remove_directory(char *path)
{
	char newpath[0x42];		// 42
	int length;			// 44
	strcpy(newpath, path);	
	length = strlen(newpath);
	if(newpath[length-1] == '\\')
		newpath[length-1] = '\0';
	rmdir(newpath);
}
