#include "_rsa.h"
#include "rsa.h"
#include "stdlib.h"

void draw_box(int pos,int box_start,int box_length,int bgr_color,int fgr_color)          
{                                                                                                  
  	char *buf;                                                                                       
  	int row;                                                                                         
  	int point_offset;                                                                                
  	int column;                                                                                     
  	char char_lr;                                                                            
  	char char_vr;                                                                            
  	int i,j;                                                                                   
  	char char_hr;                                                                            
  	char char_ll;                                                                            
  	char char_ur;                                                                            
  	int row_end;                                                                                   
  	char char_ul;                                                                              
  	int column_end;                                                                                    
	int busy;
	int color_present;
	int pos2;
                                                                                                   
	busy = 1;
  	if (!(buf = malloc(4000)))                                                                              
  	{
	    	scr(0,0,0,7);                                                                                  
	    	puts("<FATAL> - DRAW_BOX.C - Unable to allocate workspace.");                                                                                
	    	exit(1);                                                                                       
  	}                                                                                                
  	row = pos / 100;                                                                          
  	column = pos % 100;                                                                      
	row_end = box_length / 100;
	column_end = box_length % 100;  
	color_present = (is_color_video() == VIDEO_MONO) ? 0 : 1;
				                                                                         
  	if ((box_start & 0x80U) != 0) 
	{                                                                  
    		busy = 0;                                                                            
    		box_start &= 0x7f;                                                            
  	}                                                                                                
  	_$read_video_region(1, 1, 80, 25, (int *)buf, _$CGA_mode & 0xff);                                                     

	switch (box_start)                                                                            
	{
		default:                        // fall thru
		case 0:   	       	
		    	char_ul = 0xda;     	//  6   	upper left  slim
		    	char_ur = 0xbf;    	// 0e           upper right slim
		    	char_ll = 0xc0;    	// 12           lower left  slim
		    	char_lr = 0xd9;    	// 22           lower right slim
		    	char_hr = 0xc4;    	// 16           horizontal  slim
    			char_vr = 0xb3; 	// 20           vertical    slim
  			break;                  
		case 1:				// fall thru
		case 4:	
    			char_ul = 0xc9;       	//		upper left   bold double horizontal  
    			char_ur = 0xbb;        	//              upper right  bold double horizontal
    			char_ll = 0xc8;        	//              lower left   bold double horizontal
    			char_lr = 0xbc;        	//              lower right  bold double horizontal
    			char_hr = 0xcd;        	//              horizontal   bold double horizontal
			char_vr = 0xba;        	//              vertical     bold double horizontal
			break;
		case 2:
   			char_ul = 0xd6;       	//  		upper left   bold
    			char_ur = 0xb7;        	//              upper right  bold
    			char_ll = 0xd3;        	//              lower left   bold
   			char_lr = 0xbd;        	//              lower right  bold
    			char_hr = 0xc4;        	//              horizontal   bold
			char_vr = 0xba;        	//              vertical     bold
			break;
		case 3:
        		char_ul = 0xd5;       	//           	upper left   slim double horizontal
        		char_ur = 0xb8;        	//              upper right  slim double horizontal
        		char_ll = 0xd4;        	//              lower left   slim double horizontal
        		char_lr = 0xbe;        	//              lower right  slim double horizontal
        		char_hr = 0xcd;        	//              horizontal   slim double horizontal
    			char_vr = 0xb3; 	//              vertical     slim double horizontal
			break;
	}		
  	point_offset = row * 0xa0 + column * 2 - 0xa2;                                                         
  	buf[point_offset++] = char_ul;                                           
  	buf[point_offset++] = (char)bgr_color;                             

  	for (i=0; i < column_end - 2; i++) 
	{                                                      
		buf[point_offset++] = char_hr;
		buf[point_offset++] = (char)bgr_color;
	}

 	buf[point_offset++] = char_ur;    
 	buf[point_offset  ] = (char)bgr_color;   

  	for (i = row+1; i < row + row_end - 1; i++) 
	{                         
    		point_offset = i * 0xa0 + column * 2 - 0xa2;              
    		buf[point_offset    ] = char_vr;                           
    		buf[point_offset + 1] = (char)bgr_color;                        
    		point_offset += column_end * 2 - 2;  
                         
		buf[point_offset] = (box_start == 4) 	? (row + 1 == i) ? (char)0x18                               
				   		 	: (row + row_end - 2 == i) ? (char)0x19 : (char)0xb1                            
      							: char_vr;                            
    		buf[point_offset + 1] = (char)bgr_color;                             
  	}                                                                        

	row += row_end -1;
  	point_offset = row * 0xa0 + column * 2 - 0xa2;                  
	buf[point_offset++] = char_ll;
  	buf[point_offset++] = (char)bgr_color;                              

  	for (i = 0; i <  column_end - 2; i++) 
	{               
		buf[point_offset++] = char_hr;
		buf[point_offset++] = (char)bgr_color;
	}

	buf[point_offset++] = char_lr;
	buf[point_offset  ] = (char)bgr_color;

  	if (fgr_color != 0) 
	{
    		pos2 = pos + 0x65;                          
    		for (i=0; i < row_end - 2; i++) 
		{                                  
		      	row    = pos2 / 100; 
	      		column = pos2 % 100;
			point_offset = row * 0xa0  + column * 2 - 0xa2;
	
			for (j =0; j < column_end - 2; j++) 
			{
	       			buf[point_offset  ] = ' ';  
				buf[point_offset+1] = (char)fgr_color;  
			        point_offset += 2; 
			 }
			pos2 += 0x64;                       
	      	}	                                             
	}	
             
  	if(color_present && busy)
	{
  		row = pos / 100 + 1;
              	column = pos % 100 + column_end;      
     		point_offset = row * 0xa0 + column * 2 - 0xa2;          

    		for (i=1; i< row_end; i++) 
    		{
			if (!color_present)
			{
			 	buf[point_offset + 1] = 0x70;
				buf[point_offset + 3] = 0x70;
			}
			else 
			{
			 	buf[point_offset + 1] = 7;
				buf[point_offset + 3] = 7;
			}
                        point_offset += 0xa0;                          
		}
		
		row = pos / 100 + row_end;
		column = pos % 100 + 2;
	    	point_offset = row * 0xa0 + column * 2 - 0xa2;         

	    	for (i=0; i < column_end; i++) 
	    	{
	      		buf[point_offset + 1] = 7;                      
	      		point_offset += 2;                              
	    	}                                                       
  	}                                                               
            
  	_$write_video_region(1, 1, 80, 25, (int *)buf, _$CGA_mode & 0xff);                
  	free(buf);                                                                                      
  	return;                                                                                          
}                                                                                                  
                                                                                                   