#include "_rsa.h"
#include "rsa.h"
#include <stdlib.h>
#include <string.h>

static char * format_str[] = {          
	 "%2d:%02d:%02d PM"		// time		     	                             0	`
	,""                             // character           	#define CH_FIELD	     1
	,"%%%dd"	            	// iint                 #define I2_FIELD             2	
	,"%%%dld"                     	// long   	        #define IL_FIELD             3	
	,"%%%d.2f"	              	// float                #define FLOAT_FIELD          4	
	,"%2d:%02d:%02d AM"            	// time                 #define TIME_FIELD           5	
	,"%2d/%02d/%02d"		// numeric date	        #define NUMERIC_DATE_FIELD   6	
	,"%2d-%s-%02d"                	// string date          #define STRING_DATE_FIELD    7	
	,"%%%dX"	              	// hex int              #define HX_FIELD             8	
	,"%%%dlX"              		// hex long             #define HL_FIELD             9	
	,""	                    	// hash                 #define HASH_FIELD          10                   	
	,"%%%du"			// unsigned int         #define U2_FIELD            11
	,"%%%dlu"	              	// unsigned long        #define UL_FIELD            12	
	};

// original source placed big tables on stack which results in stack overflow
static 	char original_buf[82];                           
static	char result_buf[82];                             
static	char format_buf[82];                             

void   	put_field(int clear_row, int field_type, int field_pos, int field_length, int color, void *src_buf)
{
	int cursor_pos;				    
	int *s1;                                    
	unsigned int *s2;                           
	long *s3;                                   
	unsigned long *s4;                          
	float *s5;                                 
	struct DATETIME *s6;	

#ifndef ORIGINAL_CODE
	if(!src_buf)
		return;
	if (field_length < 4)
		field_length = 4;
	if (field_length > 81)
		field_length = 81;
	memset(original_buf, 0, 82);
	memset(result_buf, 0, 82);
	memset(format_buf, 0, 82);
	memcpy(original_buf, src_buf, field_length);
#else
	memcpy(original_buf, src_buf, 81);
#endif
	s1 = (int *)original_buf;
	s2 = (unsigned int *)original_buf;
	s3 = (long *)original_buf;
	s4 = (unsigned long *)original_buf;
	s5 = (float *)original_buf;
	s6 = (struct DATETIME *)original_buf;

	cursor_pos = rdcpos();
	if (clear_row)
		scr(2, field_pos, field_length, color);
 	switch (field_type)
	{
		case CH_FIELD:   
			strncpy(result_buf, src_buf, field_length);
			result_buf[field_length] = '\0';                                             
			break;                                         
		case I2_FIELD:                                               
			sprintf(format_buf, format_str[field_type], field_length);
			sprintf(result_buf, format_buf, *s1); 
			break;                                        
		case IL_FIELD: 
			sprintf(format_buf, format_str[field_type], field_length);                       
			sprintf(result_buf, format_buf, *s3);                       
			break;                                        
		case FLOAT_FIELD:                                               
			sprintf(format_buf, format_str[field_type], field_length);
			sprintf(result_buf, format_buf, *s5);
			break;   
		case TIME_FIELD:                                               
			if(s6->hour < 12)
			{
				if(s6->hour == 0)
					s6->hour = 12;				
				sprintf(result_buf, format_str[field_type], s6->hour, s6->minute, s6->second);
			} else 
			{	
				s6->hour -= 12;
				if(s6->hour == 0)
					s6->hour = 12;
				sprintf(result_buf, format_str[0], s6->hour, s6->minute, s6->second);
			}			
			break; 
		case NUMERIC_DATE_FIELD:
			sprintf(result_buf, format_str[field_type], s6->month, s6->day, s6->year%100);
			break; 
		case STRING_DATE_FIELD:                                               
			sprintf(result_buf, format_str[field_type], s6->day, months[s6->month-1], s6->year%100);
			break;
		case HX_FIELD:
			sprintf(format_buf,format_str[field_type], field_length);
			sprintf(result_buf, format_buf, *s1);
			break;
		case HL_FIELD:
			sprintf(format_buf, format_str[field_type], field_length);
			sprintf(result_buf, format_buf, *s3);
			break;
		case HASH_FIELD:
			zap(result_buf, field_length, '#');			
			result_buf[field_length] = '\0';
			break;
		case U2_FIELD:
			sprintf(format_buf, format_str[field_type], field_length);
			sprintf(result_buf, format_buf, *s2);
			break;
		case UL_FIELD:
			sprintf(format_buf, format_str[field_type], field_length);
			sprintf(result_buf, format_buf, *s4);
			break;
		default:
			zap(result_buf, field_length, '?');
			result_buf[field_length] = '\0';
	}
	if (field_length < strlen(result_buf))
	{
		zap(result_buf,81,'*');
		result_buf[field_length] = '\0';            
	} 
	put_cpos(field_pos);
	dputs(result_buf);
	put_cpos(cursor_pos);
}
