#include <stdio.h>
#include <dos.h>

#define MK_FP( seg,ofs ) (void far * )(((unsigned long)((unsigned long)(seg) << 16)) + ((unsigned long)(ofs)))
#define MK_LA( seg,ofs )                              (((unsigned long)(seg) <<  4)  +  (unsigned long)(ofs))

#define INTR_DOS				0x21
#define	INTR_EMM				0x67
#define	INTR_EQUIPMENT				0x11
#define INTR_MOUSE				0x33
#define INTR_VIDEO				0x10

#define EMM_GET_MANAGER_STATUS			0x40
#define EMM_GET_PAGE_FRAME_SEGMENT		0x41
#define EMM_GET_NUMBER_OF_PAGES			0x42			
#define EMM_GET_HANDLE_AND_ALLOCATE_MEM         0x43
#define EMM_MAP_MEMORY                  	0x44
#define EMM_RELEASE_HANDLE_AND_MEMORY           0x45
#define EMM_GET_EMM_VERSION              	0x46
#define EMM_SAVE_MAPPING_CONTEXT                0x47
#define EMM_RESTORE_MAPPING_CONTEXT             0x48
#define EMM_GET_IO_PORT_ADDRESSES              	0x49
#define EMM_GET_TRANSLATION_ARRAY               0x4a
#define EMM_GET_NUMBER_OF_EMM_HANDLES           0x4b
#define EMM_GET_PAGES_OWNED_BY_HANDLE           0x4c
#define EMM_GET_PAGES_FOR_ALL_HANDLES           0x4d
#define EMM_GET_OR_SET_PAGE_MAP             	0x4e
#define EMM_GET_SET_PARTIAL_PAGE_MAP            0x4f
#define EMM_MAP_UNMAP_MLTPL_HANDLEPAGES     	0x50
#define EMM_REALLOCATE_PAGES                    0x51
#define EMM_GET_SET_HANDLE_ATTRIBUTES           0x52
#define EMM_GET_SET_HANDLE_NAME                 0x53
#define EMM_GET_HANDLE_DIRECTORY                0x54
#define EMM_ALTER_PAGE_MAP_AND_JUMP             0x55
#define EMM_ALTER_PAGE_MAP_AND_CALL             0x56
#define EMM_MOVE_EXCHANGE_MEMORY_REGION         0x57
#define EMM_GET_MAPPABLE_PHYS_ADDRARRAY 	0x58
#define EMM_GET_EXPANDED_MEM_HRDR_INFO       	0x59
#define EMM_ALLOCATE_STANDARD_RAW_PAGES        	0x5a
#define EMM_ALTERNATE_MAP_REGISTER_SET        	0x5b
#define EMM_PREPARE_EM_HRDW_WARM_BOOT 		0x5c
#define EMM_ENABLE_DISABLE_OS_FUNCTION          0x5d
          
#define VIDEO_MONO	0
#define VIDEO_COLOR	1

extern 	int 	ndays[12];	 
extern 	char 	*months[12];
extern 	FILE *fp_menu;
extern 	FILE *fp_help;
extern 	int	max_menus;
extern 	int	errmsg_counter;
extern 	char	current_time[14];
extern 	int	USR_flags;
extern 	int	_$help_count;
extern 	int	_$hp_list;
extern 	int	_$video_address;
extern 	int	_$fcolor;
extern 	int	_$bcolor;
extern 	int	_$hcolor;
extern 	int	_$tcolor;
extern 	int	_$hi_color;	
extern 	int	_$bar_color;
extern 	int	_$asa_color;	
extern 	int	_$menu_color;
extern 	int	_$ml_color;
extern 	char	_$CGA_mode;

extern 	unsigned int 	_$$cursor_sp;
extern	int	_$$cursor_stack[0x14];

void	_$read_video_region (int column1, int row1, int column2, int row2, void * buf, int video_mode);
void	_$write_video_region(int column1, int row1, int column2, int row2, void * buf, int video_mode);


#define	MAX_FILES	10
extern	int files_open;
extern	char * file_pointer_map[MAX_FILES];
extern	int file_record_size[MAX_FILES];
