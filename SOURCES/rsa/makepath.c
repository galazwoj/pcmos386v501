#include "rsa.h"
#include <direct.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static char fname[10];                	// 12
static char drive[4];                 	// 13
static char dir[0x42];                 	// 14
static char ext[5];			// 15

static int make_parent(char *name);

int makepath(char *path)
{
 	char buf[0x42];		// 42
	int len;		// 46
	strcpy(buf, path);
	len = strlen(buf);		
	if (buf[len-1] == '\\')  
		buf[len-1] = '\0';
	_splitpath(buf,drive, dir, fname, ext); 
	if(!strlen(fname))
		return 0;
	if (!mkdir(buf) || errno == EACCES)
		return 0;	
	if(make_parent(buf))
		return 1;
	mkdir(buf);
	return 0;
}

int make_parent(char *name)
{
	int len;
	char newpath[0x42];
	_splitpath(name, drive, dir, fname, ext); 
	if (!strcmp(dir, "\\"))
		return -1;
	sprintf(newpath, "%s%s", drive, dir);
	len = strlen(newpath);	
	if (newpath[len-1] == '\\')
		newpath[len-1] = '\0';		
	if (!mkdir(newpath))		
		return 0;
	if(make_parent(newpath))
		return 1;
	mkdir(newpath);		
	return 0;
}
