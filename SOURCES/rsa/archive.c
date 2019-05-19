#include "rsa.h"
#include <direct.h>
#include <stdlib.h>
#include <string.h>

//	archive structure
//	c is_compressed        
//	s fname.ext          
//	c 0                  
//	w year               
//	w month              
//	w day                
//	w hour               
//	w minute             
//	w second             
//	c data               

int archive_file(char *source_filename, char *out_name, int show_msg)
{
	char ext[6];			//   6
	int result;			//   a				
	int compressed;			//   c
	char tmp_name[0x42];		//  4e
	struct DATETIME dt;		//  9e
	char fname[10];			//  a8
	int bytes_read;			//  aa
//	int k;			//  ac
	char *filebuf;			//  ae
	char drive[4];			// 104
	FILE *fr;			// 106
	int length;			// 108
	FILE *fw;			// 10a
	char *tmp_env;			// 10c
	char dir[0x42];			// 14e

	if (!(tmp_env = getenv("TMP")))
	{
	 	strcpy(tmp_name, tmp_env);	
		length = strlen(tmp_name);
		if (tmp_name[length-1] != '\\')
			strcat(tmp_name, "\\'");						
	} else
		tmp_name[0]= '\0';				

	_splitpath(source_filename,drive, dir, fname, ext); 
	strcat(tmp_name, fname);
	strcat(tmp_name, ".TMP");
	if ((result = compress_file(source_filename, tmp_name, show_msg)) > 0)
		return result;
	compressed = (result == -1) ? 0 : 1;
	fr = fopen(tmp_name, "rb");
	if (!(fw = fopen(out_name, "wb")))
	{
		fclose(fr);
		return 3;
	}

	if(!(filebuf = malloc(0x1000)))
	{
		fclose(fr);
		fclose(fw);
		return 1;
	}
	
	if (show_msg)
		printf("Writing archive file...");
	putc(compressed, fw);
	fprintf(fw, "%s%s", fname, ext);
	putc(0, fw);
	get_file_date(source_filename, &dt);
	putw(dt.year, fw);    
	putw(dt.month, fw);   
	putw(dt.day, fw);     
	putw(dt.hour, fw);    
	putw(dt.minute, fw);  
	putw(dt.second, fw);  
	while (!feof(fr))
	{
	 	bytes_read = fread(filebuf, 1, 0x1000, fr);
	 	fwrite(filebuf, 1, bytes_read, fw);		
	}
	if(show_msg)
		printf("\n");
	fclose(fr);
	fclose(fw);
	remove(tmp_name);
	free(filebuf);
	return 0;
}
