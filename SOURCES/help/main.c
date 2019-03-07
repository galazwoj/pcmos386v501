/*
 * Pascal  version
 * mjs 11/07/88	Corrected spelling of facility.
 * pw  09/22/89    	Add code to clear bottom lines (#24 & #25) of screen properly
 * bwr 01/12/90	Minor fix to avoid screen clutter in foreign versions
 *				of messages.
 * bwr 3/29/90 	Bottom-of-screen messages centered.
 *
 * C version
 *  galazwoj 3/05/19 	Code ported to Microsoft C 5.1 Much of Turbo Pascal logic retained.
 *		 	Only some really awkward constructs changed to C equivalent.
*/

#include <graph.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include <fcntl.h>

#define _XY(x,y)		(y), (x)
#define _W(x1,y1,x2,y2)		(y1), (x1), (y2), (x2)	 

#ifndef  SEEK_SET 
#define  SEEK_SET 0
#endif

#define FILE_SIZE 80

#define TRUE	1
#define FALSE 	0

#define ERR_SIZE	40
#define BUFF_SIZE     4096
#define TABLE_RECS      90
#define STRP_SIZE	15
#define STRC_SIZE	(STRP_SIZE + 1)
#define DISP_LINES	18
#define XLATE_RECS 	19

#define TOP	1
#define BOT	2
                   
#define KEY_ENTER	13 
#define KEY_ESC		27 
#define KEY_EXTENDED	0  
#define KEY_HOME	71 
#define KEY_END		79 
#define KEY_UP		72 
#define KEY_DOWN	80 
#define KEY_RIGHT	77 
#define KEY_LEFT	75 
#define KEY_PGUP	73 
#define KEY_PGDOWN	81 

typedef char StrP_type [STRP_SIZE];
typedef char StrC_type [STRC_SIZE];

typedef struct Table_Type_ {
	StrP_type key;
        unsigned long offset;
        int size;
} Table_type;

char *Xlate_table[ ] = {
		".LABEL",
		".SHIFT",
		".TREE",
		".VER",
		".ATTRIB",
		".BREAK",
		".SYS",
		".FIND",
		".REN",
		".SUBST",
		".ASSIGN",
		".BACKUP",
		".CHDIR",
		".RMDIR",
		".MKDIR",
		".CHKDSK",
		".COMP",
		".RESTORE",
		".SORT"
		};

char Fname[FILE_SIZE];
char filename[FILE_SIZE];

char Error_Msg[ERR_SIZE];
char Disp_Buff[BUFF_SIZE];

Table_type Index_Table[TABLE_RECS];

extern void beep(void);
extern void insline(int x1, int y1, int x2, int y2, int numlines);
extern void delline(int x1, int y1, int x2, int y2, int numlines);

void get_filename(const char *s)
{	
	int i = strlen(s);
	char *s1 = strrchr(s, '.');
	filename[0] = '\0';
	if (i<3) 
		return;
	if (!s1)
		return;
	strncpy(filename, s, s1-(char *)s);		
	filename[s1-(char *)s] = '\0';
}

int Total_Recs;
int NdxHandle, TxtHandle;
int choice;
int L,Lc;
int LinesPerCol;
int outkey;
char BarLine [81];
int Ytop;
int Xstrt,Ystrt;
int Xofs;
int MaxCol;
int Xcoord,Ycoord;
int Row,Col;
int topmore, botmore;

int Total_lines;
int topline;
int scrollok;
StrC_type parameter;

int fix_crlf = FALSE;

static void writemore(void)
{
    	int  oldfgd = _gettextcolor();
    	long oldbgd = _getbkcolor();
	_settextcolor(15);
	_outtext(" Continued . . .");
	_settextcolor(oldfgd);
	_setbkcolor(oldbgd);
}

static void putmore(int location)
{
	if ((location == TOP) && !topmore) 
	{
		_settextwindow(_W(1,1,80,25));
  		_settextposition(_XY(2,2));
  		writemore();
  		topmore = TRUE;
	}
	if ((location == BOT) && !botmore) 
	{
    		_settextwindow(_W(1,1,80,25));
		_settextposition(_XY(2,23));
		writemore();
		botmore = TRUE;
	}
	_settextwindow(_W(1,Ytop + 1,80,22));
}

static void putbar(int location)
{
	if ((location == TOP) && topmore) 
	{  	
		_settextwindow(_W(1,1,80,25));      
  		_settextposition(_XY(2,2));
  		_outtext("様様様様様様様様");
  		topmore = FALSE;
  	}
  	if ((location == BOT) && botmore) 
	{
    		_settextwindow(_W(1,1,80,25));
    		_settextposition(_XY(2,23));
    		_outtext("様様様様様様様様");
    		botmore = FALSE;
	}
	_settextwindow(_W(1,Ytop + 1,80,22));
}

static void Choice2RC(void)
{
	Col = ((choice - 1) / LinesPerCol) + 1;
	Row = choice - ((Col - 1) * LinesPerCol);
}

static void RC2Choice(void)
{
	choice = ((Col - 1) * LinesPerCol) + Row;
}

static void RC2XY(void)
{
	Xcoord = ((Col - 1) * Xofs) + Xstrt;
	Ycoord = Row - 1 + Ystrt;
}

static void dispkey(int choice, char attr)
{
	StrC_type buf;
	char bgrcolor  = attr >> 4;
	char forecolor = attr & 0xf;
	_setbkcolor((long)bgrcolor); 
	_settextcolor(forecolor);
	strncpy(buf, Index_Table[choice-1].key, STRP_SIZE);
	buf[STRP_SIZE] = '\0';
	_outtext(buf);
	_settextposition(_XY(Xcoord + STRP_SIZE, Ycoord + Ytop - 3)); 
}

static void LoChoice(void)
{
	_settextposition(_XY(Xcoord,Ycoord));
	dispkey(choice,7);
}

static void HiChoice(void)
{
	_settextposition(_XY(Xcoord,Ycoord));
	dispkey(choice,0x70);
}

static void moveleft(void)
{
	LoChoice();
	if (Col == 1)
		Col = MaxCol;
	else 
		Col --;
	RC2Choice();
	if (choice > Total_Recs)
	{
  		choice = Total_Recs;
  		Choice2RC();
	} 
	RC2XY();
	HiChoice();
}

static void moveright(void)
{
	LoChoice();
	if (Col == MaxCol)
		Col = 1;
	else 
		Col ++;
	RC2Choice();
	if (choice > Total_Recs)
	{
  		choice = Total_Recs;
  		Choice2RC();
	}
	RC2XY();
	HiChoice();
}

static void moveup(void)
{
	LoChoice();
	if (Row == 1) 
	{
  		Row = LinesPerCol;
  		if (Col > 1) 
			Col --;
	  	else 
			Col = MaxCol;
	}
	else 
		Row --;
	RC2Choice();
	if (choice > Total_Recs) 
	{
  		choice = Total_Recs;
  		Choice2RC();
	}
	RC2XY();
	HiChoice();
}

static void movedown(void)
{
	LoChoice();
	if (Col == MaxCol) 
	{        
  		if (choice == Total_Recs) 
		{
   		 	Row = 1;
    			Col = 1;
		}
  		else
	    		Row ++;
	} else {
  		if (Row == LinesPerCol) 
		{
    			Row = 1;
    			Col ++;
		}
  		else 
			Row ++;
	}
	RC2Choice();
	RC2XY();
	HiChoice();
}

static int menugetkeys(void)
{
	while(TRUE)
	{
  		int ch = getch();
  		if (ch == KEY_EXTENDED) 				// extended key pressed	
		{
    			if (kbhit())                                                            	
			{
		  		ch = getch();                                                          	
      				switch (ch)                                                           	
				{                                                                       
					case KEY_HOME :	//            	{ home }                     	
						break; 
      					case KEY_UP:  	//         	{ up arrow }           		
						moveup();
						break;
      					case KEY_PGUP : //     		{ pg up }                	
					        break;
					case KEY_RIGHT :  //      	{ right arrow }    		
						moveright();
						break;
					case KEY_PGDOWN : //            { pg dn }                    	
					      	break;
					case KEY_DOWN :	//        	{ down arrow }             	
						movedown();
						break;
					case KEY_END : 	//            	{ end }              		
					       	break;
					case KEY_LEFT : //        	{ left arrow }             	
						moveleft();
						break;
					default:     	//             	{ undefined extended key }
					        beep();            
			        }
			}
		}

		if (ch == KEY_ESC)  	// { simple escape key }
		{
			_settextwindow(_W(1,1,80,25));
			_clearscreen(_GWINDOW);
			return 0; 	// exit program
		}

    		if (ch == KEY_ENTER)
			return 1;
		else
			beep();
	}
}

static void clreol(void)
{
	char buf[80];

	struct rccoord rc;
 	rc = _gettextposition();
	memset(buf, ' ', 80 - rc.col);	 
	buf[80 - rc.col] = '\0';           	
	_outtext(buf);
}

static void Menu_Status(void)
{
	_settextwindow(_W(1,1,80,25));
	_settextposition(_XY(1,1)); 
	_outtext("                       ");  	// {BWR: Added a space }
	_settextposition(_XY(1,24)); 
	clreol();                     		// { Added to clear bottom text - PW }
	_settextposition(_XY(1,25)); 
	clreol();                     		// { Added to clear bottom text - PW }
	_settextposition(_XY(15,24)); 
	_outtext("Use arrow-keys to select choice, then press <ENTER>");
	_settextposition(_XY(15,25)); 
	_outtext("            Press <ESC> to return to MOS           ");
	_settextwindow(_W(1,Ytop,80,22));
}

typedef struct Bindextype_ {
	char 	*offset;
        int 	size;
} Bindextype;

Bindextype Buff_Index[201];  		// { max of 200 lines }

#define TAB 9

char * expand_tab(char *s)
{
static	char buf [81];
	int col = 0;
	char *c = buf;
	int size = 80;
	memset(buf, ' ', 80);
	buf[80] = '\0';

	while ((*s != '\0') && (col < size))  {
		if ((*s) != TAB)
		{
			*c++ = *s++;
			col ++;
		}
		else	
		{
			s++;
			*c++ = ' ';
			do {
				*c ++ = ' ';			
				col ++;
			} while ( col % 8 != 0);
			*c ++ = ' ';
			col ++;
		}
	}
	*c = '\0';
	return (char *)buf;
}

static void displine(int lnum)
{
	char buf[81];
	char *offset = Buff_Index[lnum].offset;
	int size = Buff_Index[lnum].size;
	if (size > 80)
		size = 80;
	strncpy(buf, offset, size);					
	buf[size] ='\0';
	if (fix_crlf && (buf[size-2] == 13) && (buf[size-1] == 10))
	{
		buf[size-2] = ' ';
		buf[size-1] = '\0';		
	}
	_outtext(expand_tab(buf));
}

static void scrollup(void)
{
	if ((topline > 1) && scrollok)
	{
  		topline --;
  		_settextwindow(_W(1,Ytop + 1,80,21));
	  	_settextposition(_XY(1,1));
	  	insline(1, Ytop, 80,21,1);		 
	  	displine(topline);
	  	_settextwindow(_W(1,Ytop+1,80,22));
	}
}

static void scrolldown(void)				
{
	if ((topline + DISP_LINES - 1 != Total_lines) && scrollok) 
	{
	  	topline ++;
	  	_settextwindow(_W(1,Ytop + 1,80,21));           
		_settextposition(_XY(1,1));
	  	delline(1, 4, 80,21,1);					
	  	_settextposition(_XY(1,DISP_LINES));   
		fix_crlf = TRUE;
	  	displine(topline + DISP_LINES - 1);             
		fix_crlf = FALSE;
	  	_settextwindow(_W(1,Ytop +1,80,22));    
	}
}

void init_text(void)
{
	int y, numlines;
	_clearscreen(_GWINDOW);
	if (scrollok)
	{
  		numlines = DISP_LINES;
  		putmore(BOT);
	}
	else 
		numlines = Total_lines;
	_settextposition(_XY(1,1));                        
	for (y = 1; y <= numlines; y++) 
		displine(y);
	topline = 1;
}

void PgDn(void)
{
	int y;
	if (scrollok && (topline + DISP_LINES - 1 != Total_lines)) 
	{
		_clearscreen(_GWINDOW);
  		_settextposition(_XY(1,1));
  		if ((topline + DISP_LINES - 1) > (Total_lines - DISP_LINES)) 
    			topline = Total_lines - DISP_LINES + 1;
  		else 
    			topline += DISP_LINES;
  		for (y = topline; y <= (topline + DISP_LINES - 1); y++)
			displine(y);
 	}
}

static void disptext(void)
{
	StrC_type buf;
	char *Curofs;
	int Curbyte;
	int MaxBytes;
	int loop1, loop2;

	_settextwindow(_W(1,Ytop,80,22));
	_setbkcolor((long)0);
	_settextcolor(7);
	_clearscreen(_GWINDOW);
	_settextwindow(_W(1,1,80,25));
	_settextposition(_XY(1,24)); 
	clreol();                  		// { Added to clear bottom text - PW }
	_settextposition(_XY(1,25)); 
	clreol();                     		// { Added to clear bottom text - PW }
	_settextposition(_XY(21,24)); 
	_outtext("Press \"+\" or \"-\" to select next screen.");
	_settextposition(_XY(21,25)); 
	_outtext("  Press <ESC> to return to the menu.   ");
	_settextposition(_XY(1,1)); 
	_outtext("Command: ");
	strncpy(buf, Index_Table[choice-1].key, STRP_SIZE);
	buf[STRP_SIZE] ='\0';
	_outtext(buf);

	_settextwindow(_W(1,Ytop + 1,80,22));
	if (lseek(TxtHandle, Index_Table[choice-1].offset, SEEK_SET) == -1)
	{
  		strcpy(Error_Msg, "Lseek in HELP.TXT");
  		return;
	}

	if (read(TxtHandle, Disp_Buff, Index_Table[choice-1].size) < 0)
	{
  		strcpy(Error_Msg, "Reading from HELP.TXT");
		return;
	}

	Total_lines = 1;
	Curofs = Disp_Buff;
	Curbyte = 0;
	MaxBytes = Index_Table[choice-1].size;

	loop1 = TRUE;                    	// { build an index to each line in the block }
	while(loop1) 
	{
  		Buff_Index[Total_lines].offset = Curofs;
  		Buff_Index[Total_lines].size = Curbyte;
  		loop2 = TRUE;
	  	while(loop1 && loop2) 
		{
#define CR	13
	    		if (Disp_Buff[Curbyte] == CR) 
			{	
	      			Curbyte += 2;
	      			Buff_Index[Total_lines].size = Curbyte - Buff_Index[Total_lines].size;
			      	Curofs += Buff_Index[Total_lines].size;
      				Total_lines ++;
	      			loop2 = FALSE;
	      		}
	    		else 
			{
	      			Curbyte ++;
	      			if (Curbyte > MaxBytes) 
					loop1 = FALSE;
			}
		}
	}

	Total_lines --;
	putbar(TOP);
	putbar(BOT);

	scrollok = FALSE;
	if (Total_lines > DISP_LINES)
	{
  		scrollok = TRUE;
  		_settextwindow(_W(1,1,80,25));
  		_settextposition(_XY(1,24)); 
		clreol();              			//{ Added to clear bottom text - PW }
  		_settextposition(_XY(1,25)); 
		clreol(); 		             	//{ Added to clear bottom text - PW }
  		_settextposition(_XY(5,24)); 
		_outtext("Use cursor keys to scroll text. Use \"+\" and \"-\" to select next screen.");
  		_settextposition(_XY(5,25)); 
		_outtext("                  Press <ESC> to return to the menu.                  ");
  		_settextwindow(_W(1,Ytop + 1,80,22));
  	}

	init_text();

	while(TRUE) 
	{
  		int ch = getch();
  		if (ch == KEY_EXTENDED) 
		{
    			if (kbhit()) 
			{
				int y;
				ch = getch();
      				switch (ch)
				{
      					case KEY_HOME : 	//	{ home }
						if (topline > 1) 
							init_text();
						break;
      					case KEY_UP   : 	//     	{ up arrow }
						scrollup();
						break;
     					case KEY_PGUP :  	//   	{ pg up }
              					if ((Total_lines > DISP_LINES) && (topline != 1)) {
                					if (topline > DISP_LINES)
							{
                  						topline -= DISP_LINES;
                  						_clearscreen(_GWINDOW);
                  						_settextposition(_XY(1,1));
                  						for (y = topline; y <= (topline + DISP_LINES - 1); y++) 
                    							displine(y);
                  					}
                  					else 
								init_text();
						}
						break;
      					case KEY_PGDOWN : 	//     	{ pg dn }
						PgDn();
						break;
      					case KEY_DOWN :  	//     { down arrow }
						scrolldown();
						break;
      					case KEY_END :  	//  	{ end key }
            					if (scrollok) 
						{
							_clearscreen(_GWINDOW);
             						_settextposition(_XY(1,1));
              						topline = Total_lines - DISP_LINES + 1;
              						for (y = topline; y <= (topline + DISP_LINES - 1); y++)
								displine(y);
						}
						break;            					
        				default: 	//       { undefined extended key }
						beep();
    				}
			}
		}

    		if (ch == KEY_ESC)	
			return;  //	{ simple escape key }

		if (ch == KEY_ENTER)
 			PgDn();
    		else
      			if (ch  == '+' || ch == '-') 
			{
        			outkey = ch;
        			return;
			}
      		else 
			beep();

  		if (scrollok)
		{
	    		if (topline > 1) 
				putmore(TOP);
	    		else 
				putbar(TOP);
	    		if ((topline + DISP_LINES - 1) != Total_lines) 
				putmore(BOT);
	    		else 
				putbar(BOT);
		}

	}
}

void message1(char *msg)
{
	_outtext("Unrecognized parameter: ");
	_outtext(msg);
	_outtext("\n");
	exit(1);
}

char *rtrim(char *s)
{
	char *p = s;
	int i = strlen(s) -1;
	while (s[i] == ' ')
		i--;
	s[i+1] = '\0';
	return p;
}
	
static void checktable1(char *parm, int start)
{
	int i;
	StrC_type buf;	
	if (strlen(parm) > (STRP_SIZE - start)) 
	  	message1(parm);
	strcpy(parameter+start, parm);
	rtrim(parameter);
	strupr(parameter);
	for (i=0; i < Total_Recs; i++) {
		strncpy(buf, Index_Table[i].key, STRP_SIZE);
		buf[STRP_SIZE] = '\0';
		if (strcmpi(rtrim(buf), parameter) == 0) {
			choice = ++i;
			break;
		}
	}
}	

char * msg_table[ ] = {
	"DISKID",    //  0
	"NEXT"	,    //  1  
	"DIRMAP",    //  2
	"REL"	,    //  3   
	"FILEMODE",  //  4
	"KILL"	,    //  5
	"MSYS"	,    //  6 
	"SEARCH",    //  7
	"RENAME",    //  8
	"ALIAS"	,    //  9
	"ALIAS"	,    // 10
	"EXPORT",    // 11
	"CD"	,    // 12   
	"RD"	,    // 13   
	"MD"	,    // 14   
	"VERIFY",    // 15
	"COMPFILE",  // 16
	"IMPORT",    // 17
	"MSORT"      // 18
	};    

void checkparm(int argc, char *parm)
{
	if (argc > 1)
	{
		strupr(parm);
  		checktable1(parm, 0); 			//      { see if can match as is }
  		if ((choice == 0) && (parm[0] != '.')) 
		{
    			parameter[0] = '.';  	//     { if match by adding a dot, scold them }
    			checktable1(parm,1);
    			if (choice > 0)
			{		
	      			_outtext("Use:    HELP .");
				_outtext(parm);
				_outtext("\n");	
				exit(1);
			}
		}
  		if (choice == 0) 		//   { didn't match first table, check 2nd }
		{
    			int i;
     			for (i = 0; i < XLATE_RECS; i++)  {
      				if (strcmpi(Xlate_table[i],parameter) == 0) {
					choice = ++i;
					break;
				}
			}
    			if (choice == 0)  
				message1(parm);	// { failed both searches }

			_outtext("Use:    HELP .");
			_outtext(msg_table[choice-1]);
			_outtext("\n");
			exit(1);
		}
	}
}

void Do_Process(int argc, char **argv)
{
	int i;
	int readbytes;
    	int  oldfgd;
    	long oldbgd;

	Xstrt = 4;
	Ystrt = 2;
	Xofs = 15;
	MaxCol = 5;
	Row = 1;
	Col = 1;
	Xcoord = Xstrt;
	Ycoord = Ystrt;
	topmore = FALSE;
	botmore = FALSE;

	memset(Error_Msg, 0, ERR_SIZE);
	// { OPEN THE INDEX FILE AND READ INTO ARRAY }

	get_filename(argv[0]);
	strcpy(Fname, filename);
	strcat(Fname, ".NDX");
	if ((NdxHandle = open(Fname, O_RDONLY| O_BINARY, 0)) == -1)
	{
	  	strcpy(Error_Msg, "Opening the HELP.NDX file    ");
		return;
	}

	if ((readbytes = read(NdxHandle, (char *)Index_Table, sizeof(Table_type) * TABLE_RECS)) < 0)	
	{
  		strcpy(Error_Msg, "Reading the HELP.NDX file    ");
		return;
	}	

	if (close(NdxHandle) == -1)
	{
  		strcpy(Error_Msg, "Closing the HELP.NDX file    ");
		return;            
	}

	Total_Recs = readbytes / sizeof(Table_type);
	LinesPerCol = Total_Recs / MaxCol;
	if (MaxCol * LinesPerCol < Total_Recs) 
		LinesPerCol ++;

	for (i=0; i<Total_Recs; i++)	
		Index_Table[i].offset = (Index_Table[i].offset >> 16)|(Index_Table[i].offset << 16);

	// { OPEN THE TEXT FILE }
	strcpy(Fname, filename);
	strcat(Fname, ".TXT");

	if ((TxtHandle = open(Fname, O_RDONLY|O_BINARY, 0)) == -1)
	{
	  	strcpy(Error_Msg, "Opening the HELP.TXT file    ");
		return;
	}

    	oldfgd = _gettextcolor();
    	oldbgd = _getbkcolor();

	_settextcolor(7);
	checkparm(argc, argv[1]);
	memset(BarLine, 205, 80);
	BarLine[80] = '\0';
	_clearscreen(_GCLEARSCREEN);

	_settextposition(_XY(29,1)); 
	_outtext("PC-MOS HELP UTILITY");
	_settextposition(_XY(1,2)); 
	_outtext(BarLine);
	_settextposition(_XY(1,23)); 
	_outtext(BarLine);
	Ytop = 3;

	if (choice > 0)
	{
	  	disptext();
	  	if (*Error_Msg) 
			goto close_TxtHandle;
	  	Choice2RC();
	  	RC2XY();
	}
	else
		choice = 1;

	while(TRUE) 
	{
  		Menu_Status();
		_clearscreen(_GWINDOW); 
  		L = 1;
  		Lc = 1;
  		Xcoord = Xstrt;
  		Ycoord = Ystrt;
		do
		{
    			_settextposition(_XY(Xcoord,Ycoord));
    			dispkey(L,7);
    			Ycoord ++;
    			L ++;
    			Lc ++;
    			if (Lc > LinesPerCol)
			{
			      Lc = 1;
			      Ycoord = Ystrt;
			      Xcoord += Xofs;
			}
		} while (L <= Total_Recs);

  		RC2XY();
  		_settextposition(_XY(Xcoord,Ycoord));
  		HiChoice();

  		if (!menugetkeys())
			goto close_TxtHandle;			

  		do
		{
	    		outkey = 'x';
	    		disptext();

		    	if (*Error_Msg) 
				goto close_TxtHandle;
    			putbar(TOP);
    			putbar(BOT);
    			if (outkey == '+') 
      				if (choice < Total_Recs) 
					choice ++;
	      			else choice = 1;
			if (outkey == '-') 
      				if (choice > 1) 
					choice --;
        			else 
					choice = Total_Recs;
		} while (outkey != 'x');
  		Choice2RC();
  		RC2XY();
	}	
close_TxtHandle:
	close(TxtHandle);

	_settextcolor(oldfgd);
	_setbkcolor(oldbgd);
	_clearscreen(_GCLEARSCREEN);
}

int main(int argc, char *argv[])
{
	if (sizeof Index_Table[0] != 21) {
		_outtext("Internal error, compile program with byte boundary packing option (/Zp) ");
		return 1;
	}
	Do_Process(argc, argv);
	if (*Error_Msg) 
	{
		_outtext("\nError:  ");
		_outtext(Error_Msg);
		_outtext("\n\n");
	  	return 1;
	} else
		return 0;
}
