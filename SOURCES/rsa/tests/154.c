#include "rsa.h"
#include <string.h>

int USR_attach(void);
void Welcome(void);

main(void)
{
    	char    *header ;
 	char    *trailer;
        char    *opt_list[10];
    	int    	opt;

    	if(USR_attach())      /* Connect to User Interface, display screen */
		return 1;
/*
    Provide the user with options.
*/
    	opt = 0;
//	wait_for_key(&ch, &exch);

    	while(1) {
        	header = " Main Menu ";
        	trailer = " F1=HELP  ESC=EXIT ";
        	opt_list[0] = "System Generation (Build CONFIG.SYS)";
        	opt_list[1] = "Exit to PC-MOS";
        	opt_list[2] = "Info";
        	opt_list[3] = "PC-MOS-SYSGEN";
        	opt_list[4] = "";
        	opt = select_option(0, 2, opt_list, opt, header, trailer, RESTORE_VIDEO);

        	if(opt == -1 || opt == 1)
           		break;

        	if(++opt > 1)
        	    	opt = 0;
    	};

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

//    	USR_menu(1, _$menu_color);
    	scr(2, cpos, strlen(menu_header), _$ml_color);
   	dputs(menu_header);
	return 0;
}
