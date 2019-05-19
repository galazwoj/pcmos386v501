#include "_rsa.h"
#include "rsa.h"

void  update_time_and_date(void)
{
	int cursor_pos;		// -2
	struct DATETIME dt;	// -10h
	
	cursor_pos = rdcpos();
	gtime(&dt);
                        
	if(dt.year != current_time.year || dt.month != current_time.month || dt.day != current_time.day)
	{
		if (current_time.year == 0)   
			USR_write(0x3e6, &dt, 1, 0);
		else
			USR_write(0x3e6, &dt, 0, 0);			
	}
                        
	if(current_time.second != dt.second) 
	{
		if (current_time.year  == 0)   
			USR_write(0x3e7, &dt, 1, 0);
		else
			USR_write(0x3e7, &dt, 0, 0);			
				
		if ((USR_flags & 1))
		{
			if (errmsg_counter == 0)
				USR_clear_message();	
			else 
				errmsg_counter--;
		}
	}
				
        current_time.year     =  dt.year;   
	current_time.month    =  dt.month;  
	current_time.day      =  dt.day;    
	current_time.hour     =  dt.hour;   		
	current_time.minute   =  dt.minute; 
	current_time.second   =  dt.second; 	
	current_time.msecond  =  dt.msecond;	
                        
	put_cpos(cursor_pos);
}
