#include "rsa.h"
#include <string.h>

int USR_attach(void);
void messages(void);

main(void)
{
    	puts("PC-MOS System Configuration Utility (V1.2)");
    	puts("(C) Copyright 1990-1992, The Software Link, Inc.");
    	puts("All Rights Reserved Worldwide.");

    	if(USR_attach())      /* Connect to User Interface, display screen */
		return 1;

  	messages();
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

void messages(void)
{
	char key1, key2;
    	char *msg_list[20];

        msg_list[0] = "Cannot install a CACHE.";
        msg_list[1] = "No Extended Memory free.";
        msg_list[2] = " ";
        msg_list[3] = ">> Press ANY key to continue <<";
        msg_list[4] = "";
        USR_message(-1, msg_list, NONE		, 0, PAUSE_FOR_KEY);
	inkey(&key1, &key2);
        USR_message(-1, msg_list, NOTE		, 0, PAUSE_FOR_KEY);
	inkey(&key1, &key2);
        USR_message(-1, msg_list, WARNING     	, 0, PAUSE_FOR_KEY);
	inkey(&key1, &key2);
        USR_message(-1, msg_list, ERROR		, 0, PAUSE_FOR_KEY);
	inkey(&key1, &key2);
        USR_message(-1, msg_list, FATAL		, 0, PAUSE_FOR_KEY);
	inkey(&key1, &key2);
        USR_message(-1, msg_list, HELP		, 0, PAUSE_FOR_KEY);
	inkey(&key1, &key2);
        USR_message(-1, msg_list, INSTRUCTIONS	, 0, PAUSE_FOR_KEY);
	inkey(&key1, &key2);
}

