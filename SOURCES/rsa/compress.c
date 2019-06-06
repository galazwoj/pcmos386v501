#include "rsa.h"
#include <stdlib.h>
  
static 	unsigned char * append_character;                                                                           
static 	unsigned int  * code_value;
static	unsigned char * decode_stack;
static	unsigned int input_byte_count;                                                                           
static	unsigned int ib_index;                                                                                   
static	unsigned char * inbuff;                                                                                     
static	unsigned int ob_index;                                                                                   
static	unsigned char * outbuff;                                                                                    
static 	unsigned int * prefix_code;                                                                                

static  unsigned int    _$find_match(unsigned int aa, unsigned int bb);
static  unsigned char * _$decode_string(unsigned char *stack, unsigned int aa);
static  unsigned int    _$input_code (FILE *file);
static  void            _$output_code(FILE *file, unsigned int aa);

int  	compress_file(char *filename, char *out_filename, int show_msg)
{
	unsigned int percentage;	//  2
	unsigned int z;			//  4
	long fi_size;			//  8
	long fo_size;			//  c
	int pos;			// 0e
	char mark = '*';		// 10	
	int i;   			// 14
	int counter;			// 16
	FILE *fi;			//-18
	FILE *fo;			// 1c

 	if(!(code_value = malloc(0x468a)))  	// 0x2345 * sizeof(int)
		return 1;	
 	if(!(prefix_code = malloc(0x468a))) 	// 0x2345 * sizeof(int)
	{
		free(code_value);
		return 1;	
	}
	if(!(append_character = malloc(0x2345)))
	{
		free(code_value);
		free(prefix_code);
		return 1;	
	}
	if(!(inbuff = malloc(0x400)))    	
	{
		free(code_value);
		free(prefix_code);
		free(append_character);
		return 1;	
	}
	if(!(outbuff = malloc(0x400)))	
	{
		free(code_value);
		free(prefix_code);
		free(append_character);
		free(inbuff);	
		return 1;	
	}

  	if(!(fi = fopen(filename, "rb")))
	{
		free(code_value);
		free(prefix_code);
		free(append_character);
		free(inbuff);	
		free(outbuff);
		return 2;	
	}
  	if(!(fo = fopen(out_filename, "wb")))
	{
		fclose(fi);
		free(code_value);
		free(prefix_code);
		free(append_character);
		free(inbuff);	
		free(outbuff);
		return 3;	
	}

	counter = 0x100;

	for (i=9; i < 0x2345; i++)		
		code_value[i] = 0xffff;
		         
	if (show_msg)
	{	
		fprintf(stdout, "Compressing ... [ ]");
		pos = rdcpos() - 2;
		cursor_off();
	}

	z = getc(fi);
	i =0;
	ob_index = 0;

	while (!feof(fi) && ((input_byte_count = fread(inbuff, 1, 0x400, fi))> 0))
	{
		unsigned int y;      	//  a
		unsigned int zz;
		unsigned int xx;       	// 12
		for (ib_index = 0; ib_index < input_byte_count; ib_index++)
		{
			y = inbuff[ib_index] & 0xff;
			if((show_msg) && (++i % 0x3e8 == 0))
			{
			 	put_cpos(pos);
				fprintf(stdout, "%c", mark);
				mark = (mark == '*') ? (char)'+' : (char)'*';
			}
			xx = _$find_match(z, y);
			zz = code_value[xx];
			if ( zz == 0xffff)
			{
				if(counter <= 0x1ffe)
				{
					code_value[xx] = counter++; 
		                       	prefix_code[xx] = z;
					append_character[xx] = (unsigned char)y;
				}
				_$output_code(fo, z);
				z = y;
			}	
			else
			 	z = zz;
		}
	}							
      	_$output_code(fo, z);
	_$output_code(fo, 0x1fff);
	_$output_code(fo, 0);
	if(ob_index != 0)
		fwrite(outbuff, 1, ob_index, fo);	
	fclose(fi);
	fclose(fo);
	fi_size = get_file_size(filename);
	fo_size = get_file_size(out_filename);
	percentage = (unsigned)(((fi_size - fo_size) * 100) / fi_size);
	if (fo_size < fi_size)
	{
	 	if(show_msg)
		{
		 	put_cpos(pos);
			fprintf(stdout, "%2d%%]\n", percentage);
			cursor_on();
		}	
	}
	else
	{
	 	if(show_msg)
		{
		 	put_cpos(pos);
			fprintf(stdout, "** STORING **");
		}
		copy_file(filename, out_filename);
	 	if(show_msg)
		{
		 	put_cpos(pos);
			fprintf(stdout, "** STORED **]\n");
			cursor_on();
		}
	}

	free(code_value);			
	free(prefix_code);			
	free(append_character);			
	free(inbuff);			
	free(outbuff);			
	return (fo_size < fi_size) ? 0 : 0xffff;
}

unsigned int _$find_match(unsigned int aa, unsigned int bb)
{
  	int key = (bb << 5) ^ aa;			// 4
	int start = (key == 0) ? 1 : 0x2345 - key;    	// 2

  	while (1)
	{
		if ((code_value[key] == 0xffff) || ((prefix_code[key] == aa) && (append_character[key] == (unsigned char)bb)))
			return key;
		key -= start;
		if (key < 0) 
			key += 0x2345;
	}	
}

int 	expand_file(char *filename, char *new_filename, int show_msg)
{
	int counter;         		//  2
	unsigned int token;		//  4
	int pos;			//  6
	char mark = '*';		//  8
	unsigned char * ia;		//  a
	unsigned int prefix;		//  c
	unsigned int ie;		//  e	
	FILE *fi;			// 10
	unsigned int character;		// 12
	FILE *fo;			// 14

	if(!(decode_stack = malloc(0x0fa0)))
		return 1;
	if(!(prefix_code = malloc(0x468a)))
	{
	 	free(decode_stack);
		return 1;
	}
	if(!(append_character = malloc(0x2345)))
	{
		free(prefix_code);
	 	free(decode_stack);
		return 1;
	}
	if(!(inbuff = malloc(0x400)))
	{
		free(append_character);
		free(prefix_code);
	 	free(decode_stack);
		return 1;
	}
	if(!(outbuff = malloc(0x400)))
	{
		free(inbuff);
		free(append_character);
		free(prefix_code);
	 	free(decode_stack);
		return 1;
	}
	if(!(fi = fopen(filename, "rb")))
	{
		free(outbuff);
		free(inbuff);
		free(append_character);
		free(prefix_code);
	 	free(decode_stack);
		return 2;
	}
	if(!(fo = fopen(new_filename, "wb")))
	{
		fclose(fi);
		free(outbuff);
		free(inbuff);
		free(append_character);
		free(prefix_code);
	 	free(decode_stack);
		return 3;
	}

	ie = 0x100;
	counter = 0;
	ib_index = input_byte_count = 0x400;
	ob_index = 0;

	if(show_msg)
	{
		fprintf(stdout,	"Expanding ... [ ]");
		pos = rdcpos() -2;
		cursor_off();
	}
	prefix = character = _$input_code(fi);
	outbuff[ob_index++] = (unsigned char)prefix;

	while ((token = _$input_code(fi)) != 0x1fff)
	{
		if(show_msg && (++counter == 0x3e8))
		{
			counter = 0;			
			put_cpos(pos);
			fprintf(stdout, "%c", mark);
			mark = (mark == '*') ? (char)'+' : (char)'*';
		}
		if (token >= ie)
		{
		 	*decode_stack = (unsigned char)character;
                        ia = _$decode_string(decode_stack +1, prefix);
		} else
                        ia = _$decode_string(decode_stack, token);			
		character = *ia;			   		
		while (ia >= decode_stack)
		{
			outbuff[ob_index++] = *ia--;			
			if (ob_index == 0x400)
			{
				fwrite(outbuff, 1, 0x400, fo);
				ob_index = 0;
			}
		}
		if (ie <= 0x1ffe)
		{
			prefix_code[ie] = prefix;
			append_character[ie] = (unsigned char)character;
			ie++;
		}
		prefix = token;
	} 

	if(show_msg)
	{
		cursor_on();
		pos = pos / 100 * 100 + 1;	
		put_cpos(pos);
		ffill(stdout, 0x20, 0x40);
		fprintf(stdout, "\r");
	}
	if(ob_index != 0)
		fwrite(outbuff, 1, ob_index, fo);
	fclose(fi);
	fclose(fo);     
 	free(decode_stack);
	free(prefix_code);
	free(append_character);
	free(inbuff);
	free(outbuff);
	return 0;
}
  
unsigned char * _$decode_string(unsigned char *stack, unsigned int aa)
{
	int counter = 0;		// 2
	while (aa > 0xff)
	{               
		*stack ++ = append_character[aa];
		aa = prefix_code[aa];
		if (counter ++ < 0x0fa0)
			continue;
		printf("EXPAND: Fatal error during code expansion.");
		exit(1);
	}
	*stack = (unsigned char)aa;
	return stack;
} 
  
unsigned int _$input_code(FILE *file)
{
	static int l_89 = 0;
	static unsigned long l_90_91 = 0;
	unsigned long l2_90_91;
	unsigned int z;			// 2
	int  sh;

	while (l_89 <= 0x18)
	{
		if(ib_index == input_byte_count)
		{
			input_byte_count = fread(inbuff, 1, 0x400, file);
			ib_index =0;
		}
		sh = 0x18 - l_89;
		if (sh != 0)
			l_90_91 |= ((unsigned long)inbuff[ib_index++] << sh);
		else
			l_90_91 |= (unsigned long)inbuff[ib_index++];			
		l_89 += 8;		
	}

	l2_90_91 = l_90_91;	
	l2_90_91 >>= 0x13;
	l2_90_91 &= 0xffff;
	z = (unsigned int)l2_90_91;
	l_90_91 <<= 0xd;
	l_89 -= 0xd;
	return z;		
}

void _$output_code(FILE *file, unsigned int aa)
{
	static int l_92 = 0;
	static unsigned long l_93_94 = 0;
	int sh = 0x13 - l_92;

	if (sh != 0)
		l_93_94 |= ((unsigned long)aa << sh);
	else
		l_93_94 |= (unsigned long)aa;			
	l_92 += 0xd;			
	
	while (l_92 >= 8) 
	{
		outbuff[ob_index++] = (unsigned char)(l_93_94 >> 0x18);
		if (ob_index == 0x400)
		{
		 	ob_index = 0;
			fwrite(outbuff, 1, 0x400, file);			
		}
		l_93_94 <<= 8;
		l_92 -= 8;
	}
}
