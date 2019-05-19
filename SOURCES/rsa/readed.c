#include "_rsa.h"
#include "rsa.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int     readed(int action, int position , int field_type, int length, int color, char *src_buf)
{
	long  l_value;					//  4
	char  buf2[10];					//  0e
	float *s5; 					//  10 
	char  buf3[10];					//  1a
	unsigned *s2;   				//  1c
	char  buf4[10];					//  26           
	char  buf[82];					//  78
	unsigned long *s4;  		   	 	//  7a
//	int  con_result;				//  84    
	struct DATETIME dt;				//  88    
	int *s1;       					//  8a    
	int  con_result;				//  8c
	char *buf_work;					//  8e
	int  time24h;					//  90
	int  i;						//  92
	long *s3;       				//  94
	char character;					//  96
	int  leap_year;					//  98
	char ext_character;   				//  9a
	int  count;					//  9c
	unsigned long ul_value;				//  a0	
	int  buf_len;					//  a2
	int  MOS_present;				//  a4

	s1 = (int *)src_buf;       		   
	s2 = (unsigned *)src_buf;   		
	s3 = (long *)src_buf;       		
	s4 = (unsigned long *)src_buf;     	
	s5 = (float *)src_buf; 		
             
	MOS_present = (is_MOS() == 0) ? 0 : 1; 

	if (position < 0)
	{
	 	position = abs(position);
		scr(action, position, length, color);

		while(1)
		{
			while(!inkey(&character, &ext_character))
			{
			 	update_time_and_date();
				if (MOS_present)
					MOS_wait(1);
			}
			USR_clear_message();
			if (character == 0x1b)
				return 0x1b;
			if (character == 0x0d)
				return -8;
			if (character == 0)
			{
				src_buf[0] = ext_character;
				return 0;
			}
		}
	}

	if (position == 0)
		position = rdcpos();
	scr(action, position, length, color);

	while (1)
	{
		if (field_type == HASH_FIELD)
			con_result = conred(buf, length, color, 0);
		else
			con_result = conred(buf, length, color, 1);

		if (con_result == 3)
			continue;

		if (field_type == HASH_FIELD)
			field_type = CH_FIELD;			

		if (field_type != CH_FIELD)
		{
			strupr(buf);
			squeeze(buf, ' ');
		}
		if (!con_result)
		{
			src_buf[0] = buf[0];
			return con_result;	
		}
		if (con_result == 0xd)
		{
			if(!strlen(buf))
  				return -8;
		}
		if (con_result == 0x1b)		
			return con_result;	

		switch (field_type)
		{
 	 		case   	I2_FIELD:
			case   	IL_FIELD:
                        	buf_len = strlen(buf);
				if (*buf == '-' || *buf == '+' || (isdigit(*buf)))
				{
				 	for (i = 1; i < buf_len; i++)
						if (!isdigit(buf[i]))
							return BAD_DATA;
					sscanf(buf, "%ld", &l_value);
					if (field_type == I2_FIELD)
					{
						if (l_value > SHRT_MAX || l_value < SHRT_MIN)
							return BAD_DATA;
						*s1 = (int)l_value;	
						put_field(0, field_type, position, length, color, &l_value);
					}
					if (field_type == IL_FIELD)
					{
						*s3 = l_value;
						put_field(0, field_type, position, length, color, &l_value);
					}
					break;
				}
				else
					return BAD_DATA;
			case   	FLOAT_FIELD:
                              	buf_len = strlen(buf);
				if (*buf == '-' || *buf == '+' || *buf == '.' || (isdigit(*buf)))
				{
					count = 0;
					if (*buf == '.')
						count ++;
					for (i=1; i < buf_len; i++)
					{
						if (buf[i] == '.')					 		
							count ++;
						else	
							if (!isdigit(buf[i]))
								return BAD_DATA;
					}
					if (count > 1)
						return BAD_DATA;				
					sscanf(buf, "%f", s5);	
					put_field(0, field_type, position, length, color, s5);
					break;
				}
				else
					return BAD_DATA;
 			case	TIME_FIELD:
				time24h = 0;
				buf_work = strstr(buf, "AM");
				if (buf_work)
					*buf_work = '\0';
				buf_work = strstr(buf, "PM");
					if(buf_work) 
				{
					*buf_work = '\0';
					time24h = 1;
				}
				buf_len = strlen(buf);
				count = 0;

				for (i=0; i < buf_len; i++)
				{
					if (buf[i] == ':')
						count++;
					else
					   	if(!isdigit(buf[i]))
							return BAD_DATA;
				}			

 	 	 	 	if (count == 0|| count > 2)	
					return BAD_DATA;

				buf_work = buf;
				count = index(':', buf); 
				strncpy(buf2, buf_work, count);
        			buf2[count] = '\0';
				buf_work += count +1;	
				count = index(':', buf_work);
				if (count == -1)
				{
					strcpy(buf3, buf_work);
					strcpy(buf4, "0");
				}
				else
				{
					strncpy(buf3, buf_work, count);
					buf3[count] = '\0';
					buf_work += count +1;	
					strcpy(buf4, buf_work);
				}
						
				sscanf(buf2,"%d", &dt.hour);
				sscanf(buf3,"%d", &dt.minute);
				sscanf(buf4,"%d", &dt.second);
				dt.msecond = 0;
				if (dt.hour > 12)
					return BAD_DATA;
				if (dt.minute > 60)
					return BAD_DATA;
				if (dt.second > 60)
					return BAD_DATA;
				if (time24h) 
				{	
					if(dt.hour < 12)
						dt.hour +=12;
				}
				else	
				{
					if (dt.hour == 12)
						dt.hour = 0;
				}
				put_field(0, field_type, position, length, color, &dt);
				memcpy(src_buf+6, &dt.hour, 4 * sizeof(int));
				break;
  		 	case   	NUMERIC_DATE_FIELD:
				gtime(&dt);
			    	dt.year %= 100;
				buf_work = buf;
				for (i=0; i < 3; i++)
				{
					if (i == 0)
						dt. month = atoi(buf_work);
					if (i == 1)
	 					dt. day = atoi(buf_work);	
					if (i == 2)
	 					dt. year = atoi(buf_work);
                        
					buf_work = strchr(buf_work, '/');
					if (buf_work == NULL || *++buf_work == '\0')
						break;
				}	
				if (dt.month < 1 || dt.month > 12)	
					return BAD_DATA;		
				count = dt.month -1;
				if (dt.day <1 || ndays[count] < dt.day)
				{
					if ((leap_year = dt.year % 4) != 0)
						return BAD_DATA;
					if (dt.day !=29)
						return BAD_DATA;
					if (count != 1)
						return BAD_DATA;
				}
				memcpy(src_buf, &dt, 6);				 	
				put_field(0, field_type, position, length, color, &dt);
				break;
   	    	    	case   	STRING_DATE_FIELD:
				count = 0;
				buf_len = strlen(buf);
				for (i = 0; i < buf_len; i++)
					if (buf[i] == '-')
						count ++;
				if (count != 2)				
					return BAD_DATA;

				buf_work = buf;
				count = index('-', buf);				
				strncpy(buf2, buf_work, count);
				buf2[count] = '\0';
				buf_work += count +1;
				count = index('-', buf_work);				
				strncpy(buf3, buf_work, count);
				buf3[count] = '\0';
				strupr(buf3);
				buf_work += count + 1;
				strcpy(buf4, buf_work);
				dt.month = 0;				
				for (i=0; i< 12; i++)
					if (strcmpi(buf3, months[i]) == 0)
					{
						dt.month = i+1;
						break;
					}								

				sscanf(buf2, "%d", &dt.day);	
				sscanf(buf4, "%d", &dt.year);

				if (dt.year < 0 || dt.year > 99)	
					return BAD_DATA;
				if(dt.month <1 || dt.month > 12)
					return BAD_DATA;			
				leap_year = dt.year % 4;
				count = dt.month;

				if (leap_year !=0 || dt.month != 2)
				{
				  	if(dt.day < 1 || dt.day > ndays[count-1]) 
						return BAD_DATA;
				}
				else
					if (dt.day < 1 || dt.day > 29)	
						return BAD_DATA;
				memcpy(src_buf, &dt, 6);				 	
				put_field(0, field_type, position, length, color, &dt);
				break;
                      	case   	HX_FIELD:
                        case   	HL_FIELD:
				buf_len = strlen(buf);
				if (field_type == HX_FIELD && buf_len > 4)
					return BAD_DATA;
				for (i=0; i < length; i++)
				 	if(isalpha(buf[i]) && islower(buf[i]))
						buf[i] -= ' ';	
				for (i=0; i < buf_len; i++)
				 	if (!isxdigit(buf[i]))
						return BAD_DATA;
				if(length >4)
					sscanf(buf, "%lx", &l_value);
 	 	 		else
					sscanf(buf, "%x", &l_value);
				if (field_type == HX_FIELD)
					*s1 = (int)l_value;
				if (field_type == HL_FIELD)
					*s3 = l_value;
				put_field(0, field_type, position, length, color, &l_value);					
				break;
			case 	U2_FIELD:
			case 	UL_FIELD:
				buf_len = strlen(buf);
				for (i=1; i < buf_len; i++)
					if(!isdigit(buf[i]))
						return BAD_DATA;	
				sscanf(buf, "%lu", &ul_value);				
				if (field_type == U2_FIELD)
				{
					if (ul_value > UINT_MAX)
						return BAD_DATA;
					*s2 = (unsigned int)ul_value;	
				}
				if (field_type == UL_FIELD)
					*s4 = ul_value;
				put_field(0, field_type, position, length, color, &ul_value);
				break;
 	 	 	case   	CH_FIELD:		// fall thru
                        case   	HASH_FIELD:             // fall thru
	                default:
				strcpy(src_buf, buf);
		}
		return 0xd;
       	}
}
