#include <graph.h>

/* soun, nosound, delay routines based on Borland C */

/*--------------------------------------------------------------------------*

Name            timer_init - initialize multiplier for delay function

Usage           void timer_init (void);

Description     Determine the multiplier required to convert milliseconds
                to an equivalent interval timer value.  Interval timer 0
                is normally programmed in mode 3 (square wave), where
                the timer is decremented by two every 840 nanoseconds;
                in this case the multiplier is 2386.  However, some
                programs and device drivers reprogram the timer in mode 2,
                where the timer is decremented by one every 840 ns; in this
                case the multiplier is halved, i.e. 1193.

                When the timer is in mode 3, it will never have an odd value.
                In mode 2, the timer can have both odd and even values.
                Therefore, if we read the timer 100 times and never
                see an odd value, it's a pretty safe assumption that
                it's in mode 3.  This is the method used in timer_init.

Return value    None

*---------------------------------------------------------------------------*/

static int timer_run = 0;
static unsigned long multiplier = 1193*2L;
extern unsigned near readtimer (void);

static void timer_init(void)
{
    	int i;
	
	timer_run = 1;
    	for (i = 0; i < 100; i++)
        	if ((readtimer() & 1) == 0)     /* readtimer() returns complement */
            	{
            		multiplier = 1193L;
            		return;
            	}
}

/*--------------------------------------------------------------------------*

Name            delay - wait for specified period.

Usage           void delay(unsigned milliseconds);

Description     Execution is suspended for the specified number of milliseconds.

Return value    None
*---------------------------------------------------------------------------*/

static void delay( unsigned milliseconds)
{
    	volatile unsigned long stop;
    	volatile unsigned long cur, prev;
	
	if (!timer_run)
		timer_init();

    	stop = (prev = readtimer()) + (milliseconds * multiplier);
    	while ((cur = readtimer()) < stop)
        {
        	if (cur < prev && (stop >= 0x10000L))     /* Check for timer wraparound */
            		stop -= 0x10000L;
        	prev = cur;
        }
}

extern void near sound(unsigned frequency);
extern void near nosound(void);

void beep(void) 
{
	sound(99);
	delay(100);
	nosound();
}

#define SCROLL_UP  	6
#define SCROLL_DOWN     7

extern void near scroll(int direction, int x1, int y1, int x3, int y2, int numlines, int attribute);

void insline(int x1, int y1, int x2, int y2, int numlines)
/* Inserts a line at the current line */
{
	int attribute = _gettextcolor();
	unsigned long bgr = _getbkcolor();
	attribute = ((unsigned char)(bgr << 4)) | ((unsigned char)(attribute & 0xf));
        scroll(SCROLL_DOWN, x1-1, y1-1, x2-1, y2-1, numlines, attribute);
} 

void delline(int x1, int y1, int x2, int y2, int numlines)
/* Deletes the current line on the screen */
{
	int attribute = _gettextcolor();
	unsigned long bgr = _getbkcolor();
	attribute = ((unsigned char)(bgr << 4)) | ((unsigned char)(attribute & 0xf));
        scroll(SCROLL_UP,   x1-1, y1-1, x2-1, y2-1, numlines, attribute);
}
