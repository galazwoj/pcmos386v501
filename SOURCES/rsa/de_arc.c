#include "rsa.h"
#include <ctype.h>
#include <direct.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>

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

int de_archive_file(char *source_filename, char *out_name)
{
	int  update_date;		//   2
	char filename[14];		//  10
	char ext[6];			//  16
	int result2;			//  1a
	int compressed;			//  1c
	char tmp_name[0x42];		//  5e
	int attributes;			//  60;
	char new_filename[0x42];	//  a2
	struct DATETIME dt;		//  b0
	char fname[10];			//  ba	
	int bytes_read;			//  be
	char *c;			//  c0
	char *filebuf;			//  c2
	char drive[4];			//  c6
	FILE *fr;			//  c8
	int length;			//  ca
	FILE *fw;			//  cc
	char *tmp_env;			//  ce
	char dir[0x42];			// 110

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
	if (!(fr = fopen(source_filename, "rb")))
		return 2;
		
	if(!(filebuf = malloc(0x1000)))
	{
		fclose(fr);
		return 1;
	}

	compressed = getc(fr);
	c = filename;
	while ((*c++ = (char)getc(fr)) != '\0')
		;

	dt.year   = getw(fr);    
	dt.month  = getw(fr);   
	dt.day    = getw(fr);     
	dt.hour   = getw(fr);    
	dt.minute = getw(fr);  
	dt.second = getw(fr);  
	dt.msecond = 0;

	update_date = 1;
	if(!(length = strlen(out_name)))
		strcpy(new_filename, filename);
	else
	{												// 112
		if(out_name[length -1] == '\\')		
		{
		 	strcpy(new_filename, out_name);
		 	strcat(new_filename, filename);
		}	
		else
		{
		 	if(isalpha(out_name[0]) && out_name[1] == ':' && strlen(out_name) == 2)
			{
				strcpy(new_filename, out_name);
				strcat(new_filename, filename);
			}
			else										// 116
			{
			 	result2 = get_file_attributes(out_name, &attributes);
				if (!result2 && (attributes & _A_SUBDIR))
				{
					strcpy(new_filename, out_name);
					strcat(new_filename, "\\");
					strcat(new_filename, filename);
				}       	
				else
				{									// 117
					strcpy(new_filename, out_name);   					
					update_date = 0;
				}
			}
		}
	}
	if(compressed)											// 118
	{
		if (!(fw = fopen(tmp_name, "wb")))
		{
			fclose(fr);
			free(filebuf);
			return 3;
		}
		while (!feof(fr))
		{
			bytes_read = fread(filebuf, 1, 0x1000, fr);
			fwrite(filebuf, 1, bytes_read, fw);
		}
		fclose(fr);
		fclose(fw);
		if (!(result2 = expand_file(tmp_name ,new_filename, 1)))
		{
		 	remove(tmp_name);
			if(update_date)
				set_file_date(new_filename, &dt);
			free(filebuf);
			return 0;
		}
		free(filebuf);
		return result2;
	} 
	else
	{
		if (!(fw = fopen(new_filename, "wb")))
		{
			fclose(fr);
			free(filebuf);
			return 3;
		}
	
		while (!feof(fr))
		{
			bytes_read = fread(filebuf, 1, 0x1000, fr);
			fwrite(filebuf, 1, bytes_read, fw);
		}
		fclose(fr);
		fclose(fw);

		if(update_date)
			set_file_date(new_filename, &dt);
		free(filebuf);
		return 0;
	}
}
