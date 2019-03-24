#include <stdio.h>

// EMM_present()
#define EMM_NOT_PRESENT	0
#define EMM_PRESENT	1

/*Values for EMS status function */
#define EMM_ERROR_00h   0x00     /* successful														*/
#define EMM_NO_ERROR	EMM_ERROR_00h
#define EMM_ERROR_80h   0x80     /* internal error                                                                                              		*/
#define EMM_ERROR_81h   0x81     /* hardware malfunction                                                                                                 */
#define EMM_ERROR_82h   0x82     /* busy -- retry later                                                                                                  */
#define EMM_ERROR_83h   0x83     /* invalid handle                                                                                                       */
#define EMM_ERROR_84h   0x84     /* undefined function requested by application                                                                          */
#define EMM_ERROR_85h   0x85     /* no more handles available                                                                                            */
#define EMM_ERROR_86h   0x86     /* error in save or restore of mapping context                                                                          */
#define EMM_ERROR_87h   0x87     /* insufficient memory pages in system                                                                                  */
#define EMM_ERROR_88h   0x88     /* insufficient memory pages available                                                                                  */
#define EMM_ERROR_89h   0x89     /* zero pages requested                                                                                                 */
#define EMM_ERROR_8Ah   0x8A     /* invalid logical page number encountered                                                                              */
#define EMM_ERROR_8Bh   0x8B     /* invalid physical page number encountered                                                                             */
#define EMM_ERROR_8Ch   0x8C     /* page-mapping hardware state save area is full                                                                        */
#define EMM_ERROR_8Dh   0x8D     /* save of mapping context failed                                                                                       */
#define EMM_ERROR_8Eh   0x8E     /* restore of mapping context failed                                                                                    */
#define EMM_ERROR_8Fh   0x8F     /* undefined subfunction                                                                                                */
#define EMM_ERROR_90h   0x90     /* undefined attribute type                                                                                             */
#define EMM_ERROR_91h   0x91     /* feature not supported                                                                                                */
#define EMM_ERROR_92h   0x92     /* successful, but a portion of the source region has been overwritten                                                  */
#define EMM_ERROR_93h   0x93     /* length of source or destination region exceeds length of region allocated to either source or destination handle     */
#define EMM_ERROR_94h   0x94     /* conventional and expanded memory regions overlap                                                                     */
#define EMM_ERROR_95h   0x95     /* offset within logical page exceeds size of logical page                                                              */
#define EMM_ERROR_96h   0x96     /* region length exceeds 1M                                                                                             */
#define EMM_ERROR_97h   0x97     /* source and destination EMS regions have same handle and overlap                                                      */
#define EMM_ERROR_98h   0x98     /* memory source or destination type undefined                                                                          */
#define EMM_ERROR_9Ah   0x9A     /* specified alternate map register or DMA register set not supported                                                   */
#define EMM_ERROR_9Bh   0x9B     /* all alternate map register or DMA register sets currently allocated                                                  */
#define EMM_ERROR_9Ch   0x9C     /* alternate map register or DMA register sets not supported                                                            */
#define EMM_ERROR_9Dh   0x9D     /* undefined or unallocated alternate map register or DMA register set                                                  */
#define EMM_ERROR_9Eh   0x9E     /* dedicated DMA channels not supported                                                                                 */
#define EMM_ERROR_9Fh   0x9F     /* specified dedicated DMA channel not supported                                                                        */
#define EMM_ERROR_A0h   0xA0     /* no such handle name                                                                                                  */
#define EMM_ERROR_A1h   0xA1     /* a handle found had no name, or duplicate handle name                                                                 */
#define EMM_ERROR_A2h   0xA2     /* attempted to wrap around 1M conventional address space                                                               */
#define EMM_ERROR_A3h   0xA3     /* source array corrupted                                                                                               */
#define EMM_ERROR_A4h   0xA4     /* operating system denied access                                                                                       */

int     EMM_status(void);
void far *EMM_get_page_frame(void);
int     EMM_get_page_count(int *total_pages, int *unallocated_pages);
int     EMM_allocate_pages(int num_logical_pages, int *handle);
int	EMM_map_page(int handle, int phys_page_number, int logical_page_number);
int	EMM_free_pages(int handle);
int     EMM_get_version(int *version);
int     EMM_save_page_map(int handle);
int     EMM_restore_page_map(int handle);
int     EMM_get_handle_count(int *num_of_emm_handles);
int     EMM_get_handle_pages(int handle, int *num_of_logical_pages);
int     EMM_get_handle_map(int *num_of_active_emm_handles, void *buffer);
int     EMM_get_page_map(void *receive_buffer);
int     EMM_set_page_map(void *current_buffer);
int     EMM_get_set_page_map(void *current_buffer, void *receive_buffer);
int     EMM_get_page_map_size(int *array_size);
int     EMM_present(void);
char	*EMM_error(int status);

// string

void   	center(char *buf, unsigned len);
int 	crc16(char *buf, int len);
void 	decrypt(char *buf, int key);
void 	encrypt(char *buf, int key);
int 	index(char character, char *buf);
void    squeeze(char *buf, int character);
void    squeezen(char *buf, int character, int count);
void 	strip_leading_blanks(char *buf);
void 	strip_trailing_blanks(char *buf);
char   *strstri(char *str1, char *str2);
void 	zap(void *buf, unsigned size, char character);

// display

// get_video_type()
#define VIDEO_TYPE_VGA  0
#define VIDEO_TYPE_EGA  1
#define VIDEO_TYPE_CGA  2
#define VIDEO_TYPE_HGC  3
#define VIDEO_TYPE_NONE 4

// is_color_video()
#define VIDEO_MONO	0
#define VIDEO_COLOR	1

// read_mouse()
#define MOUSE_PRESENT          	1
#define MOUSE_NOT_PRESENT	0   

// scr()
#define CLEARSCREEN	0
#define SET_CURSOR  	1
#define CLEARROW  	2
#define CLEARCOLUMN 	3
#define CHANGEATTRIBUTE	4

// scroll()
#define SCROLL_UP	0
#define SCROLL_DOWN	1

void 	change_video_attribute(void far *pixel, int attribute, int count);
int   	convert_to_mono(int attribute);
void	cursor_off(void);
void	cursor_on(void);
int     da_close(FILE *);
void  	display_copyright(char *str);
void 	dputchar(int character);
void 	dputs(char *s);
int 	get_video_type(void);
int	is_color_video(void);
void    put_cpos(int cursor_pos);
void 	putscr(void *screen_buf, int color);
int     rdcpos(void);
int	read_mouse(int action, int *button_status, int *rows, int *columns);
int     restore_video_region(int pos1, int pos2, void *buf);
void    *save_video_region(int pos1, int pos2);
void    scr(int action, int cursor_pos, int length, int color);
void    scroll(int cursor_pos1, int cursor_pos2, int num_of_lines, unsigned color, int direction);
void 	set_standard_colors(void);
void  	USR_disconnect(void);

// bios & dos

//get_CPU_type()
#define CPU_8086	0
#define CPU_80186       1
#define CPU_80286       2
#define CPU_80386       3
#define CPU_80486       4

//inkey()
#define INKEY_NO_KEY 0
#define INKEY_IS_KEY 1

struct DATETIME {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int msecond;
};

void far *absolute_to_segment(unsigned long address);
int	bios_disk_read(int drive, int cylinder, int head, int sector, int num_of_sectors, char *buffer);
int  	bios_disk_reset(int drive);
int 	bios_disk_status(void);  
int	bios_disk_write(int drive, int cylinder, int head, int sector, int num_of_sectors, char *buffer);
void  	delay(int time_ticks);
unsigned long diskfree(int drive);
int 	find_first_file(char *filespec, char *filename, unsigned *attribute);
int 	find_next_file(char *filename, unsigned *attribute);
int  	get_CPU_type(void); 	
void 	get_current_path(char *path);
int 	get_volume_label(int drive, char *label_name);
int 	inkey(char *character, char *ext_character);
int  	is_MOS(void);
int 	MOS_wait(int timer_ticks);
void far *normalize_address(unsigned seg, unsigned ofs);
void   	read_DTA(void *buf, int count);
void	read_PSP(void *psp_buffer);
unsigned long 	segment_to_absolute(unsigned long segment_address);
void  	setup_i24(void);
int 	set_volume_label(int drive, char *label_name);
void 	wait_for_key(char *character, char *ext_character);
void    write_DTA(void *buf, int count);

// file
int    	copy_file(char *source_file, char *dest_file);
int     count_matching_files(char *filespec);
int    	da_close(FILE *file);
FILE   *da_open(char *filename, char *mode, int record_size);
void    ffill(FILE *file, char character, unsigned count);
int 	get_file_attributes(char *filename, int *attributes);
int 	get_file_date(char *filename, struct DATETIME *datetime);
long    get_file_size(char *filename);
char   *get_line(char *buf, int len, FILE *file);
void    gtime(struct DATETIME *datetime);
int 	set_file_attributes(char *filename, int attributes);
int 	set_file_date(char *filename, struct DATETIME datetime);
