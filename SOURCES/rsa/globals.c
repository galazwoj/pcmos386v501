#include "_rsa.h"
#include "rsa.h"

int 	ndays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};	 
char 	*months[12] = {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};
FILE *	fp_menu = NULL;
FILE *	fp_help = NULL;
int	max_menus = 0;
int	errmsg_counter = 0;
char	current_time[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int	USR_flags = 0;
int	_$help_count = 0;
int	_$hp_list = 0;
int	_$video_address = 0;
int	_$fcolor = 0x70;
int	_$bcolor = 0x71;
int	_$hcolor = 0x7c;
int	_$tcolor = 0x71;
int	_$hi_color = 0x7e;	
int	_$bar_color = 0x30;
int	_$asa_color = 0x17;	
int	_$menu_color = 0x1f;
int	_$ml_color = 0x1e;
char	_$CGA_mode = 0;

int	_$$cursor_stack[0x14];
