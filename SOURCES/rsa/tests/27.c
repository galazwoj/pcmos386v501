#include "rsa.h"
#include <string.h>

int USR_attach(void);
void Welcome(void);

main(void)
{
    	puts("PC-MOS System Configuration Utility (V1.2)");
    	puts("(C) Copyright 1990-1992, The Software Link, Inc.");
    	puts("All Rights Reserved Worldwide.");

    	if(USR_attach())      /* Connect to User Interface, display screen */
		return 1;

    	Welcome();
    	USR_disconnect();
    	scr(0,0,0,7);
}
/* ======================================================================= */
USR_attach(void)
{
    	char    *menu_header;
    	int     cpos,
            	status;
/*
    Connect to USR and display the main screen.
*/
    	status = USR_connect("ACU.MNU", "ACU-HELP.HLP");
    	if(!status) 
        	puts("ACU:  Could not find menu file \"ACU.MNU\".");
/*
    Paint the menu background on the screen.
*/
    	menu_header = " PC-MOS Configuration ";
    	cpos = 101 + (80 - strlen(menu_header))/2;

      	USR_menu(1, _$menu_color);
    	scr(2, cpos, strlen(menu_header), _$ml_color);
    	dputs(menu_header);
	return 0;
}
/*
    Display a welcome message for the user.
*/
void Welcome(void)
{
    char    key1,
            key2,
            *header,
            *trailer,
            *msg_list[20];

    int     i,
            cpos,
            *video;

    	header = " WELCOME ";
    	trailer = " Press ANY key to continue .. ";

    	msg_list[0]  = "  This  Auto-Configuration  Utility will";
    	msg_list[1]  = "build  a CONFIG.SYS  file (or  modify an";
    	msg_list[2]  = "existing CONFIG.SYS file) to set up your";
    	msg_list[3]  = "system configuration under PC-MOS.";
    	msg_list[4]  = " ";
    	msg_list[5]  = "  You  will be  able to  set up  various";
   	msg_list[6]  = "parameters, such  as: memory management,";
    	msg_list[7]  = "video configuration, and disk caching.";
    	msg_list[8]  = " ";
    	msg_list[9]  = "  You  will  also  be  able  to  install";
    	msg_list[10] = "various device drivers,  such as: serial";
    	msg_list[11] = "port, mouse, EMS, and RAM Disk drivers -";
    	msg_list[12] = "as well  as special drivers  for VNA and";
    	msg_list[13] = "IONA hardware.";
    	msg_list[14] = " ";
    	msg_list[15] = "  Use the following  menus to select and";
    	msg_list[16] = "set up the system options that you need.";
    	msg_list[17] = "";

    	video = save_video_region(101, 2580);
    	draw_box(318, 1, 1944, _$bcolor, _$fcolor);

    	cpos = 318 + (44 - strlen(header)) / 2;
    	put_field(1, CH_FIELD, cpos, strlen(header), _$hcolor, header);
    	cpos = 2118 + (44 - strlen(trailer)) / 2;
    	put_field(1, CH_FIELD, cpos, strlen(trailer), _$tcolor, trailer);

    	cpos = 420;
    	for(i=0; i<17; ++i) {
        	put_field(1, CH_FIELD, cpos, strlen(msg_list[i]), _$fcolor, msg_list[i]);
        	cpos += 100;
    	}

    	cursor_off();
    	while(!inkey(&key1, &key2)) 
	{
   	     	update_time_and_date();
       	 	if(is_MOS())
       	     		MOS_wait(18);
    	}
    	cursor_on();
    	restore_video_region(101, 2580, video);
}
