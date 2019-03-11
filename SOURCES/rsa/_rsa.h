#include <dos.h>

#define MK_FP( seg,ofs ) (void far * )(( seg  << 16) | ( ofs ))

#define	INTR_EMS				0x67

#define EMS_GET_MANAGER_STATUS			0x40
#define EMS_GET_PAGE_FRAME_SEGMENT		0x41
#define EMS_GET_NUMBER_OF_PAGES			0x42			
#define EMS_GET_HANDLE_AND_ALLOCATE_MEM         0x43
#define EMS_MAP_MEMORY                  	0x44
#define EMS_RELEASE_HANDLE_AND_MEMORY           0x45
#define EMS_GET_EMM_VERSION              	0x46
#define EMS_SAVE_MAPPING_CONTEXT                0x47
#define EMS_RESTORE_MAPPING_CONTEXT             0x48
#define EMS_GET_IO_PORT_ADDRESSES              	0x49
#define EMS_GET_TRANSLATION_ARRAY               0x4a
#define EMS_GET_NUMBER_OF_EMM_HANDLES           0x4b
#define EMS_GET_PAGES_OWNED_BY_HANDLE           0x4c
#define EMS_GET_PAGES_FOR_ALL_HANDLES           0x4d
#define EMS_GET_OR_SET_PAGE_MAP             	0x4e
#define EMS_GET_SET_PARTIAL_PAGE_MAP            0x4f
#define EMS_MAP_UNMAP_MLTPL_HANDLEPAGES     	0x50
#define EMS_REALLOCATE_PAGES                    0x51
#define EMS_GET_SET_HANDLE_ATTRIBUTES           0x52
#define EMS_GET_SET_HANDLE_NAME                 0x53
#define EMS_GET_HANDLE_DIRECTORY                0x54
#define EMS_ALTER_PAGE_MAP_AND_JUMP             0x55
#define EMS_ALTER_PAGE_MAP_AND_CALL             0x56
#define EMS_MOVE_EXCHANGE_MEMORY_REGION         0x57
#define EMS_GET_MAPPABLE_PHYS_ADDRARRAY 	0x58
#define EMS_GET_EXPANDED_MEM_HRDR_INFO       	0x59
#define EMS_ALLOCATE_STANDARD_RAW_PAGES        	0x5a
#define EMS_ALTERNATE_MAP_REGISTER_SET        	0x5b
#define EMS_PREPARE_EM_HRDW_WARM_BOOT 		0x5c
#define EMS_ENABLE_DISABLE_OS_FUNCTION          0x5d

/*Values for EMS function status: */
#define EMS_ERROR_00h   00h     /* successful														*/
#define EMS_NO_ERROR	EMS_ERROR_00h
#define EMS_ERROR_80h   80h     /* internal error                                                                                              		*/
#define EMS_ERROR_81h   81h     /* hardware malfunction                                                                                                 */
#define EMS_ERROR_82h   82h     /* busy -- retry later                                                                                                  */
#define EMS_ERROR_83h   83h     /* invalid handle                                                                                                       */
#define EMS_ERROR_84h   84h     /* undefined function requested by application                                                                          */
#define EMS_ERROR_85h   85h     /* no more handles available                                                                                            */
#define EMS_ERROR_86h   86h     /* error in save or restore of mapping context                                                                          */
#define EMS_ERROR_87h   87h     /* insufficient memory pages in system                                                                                  */
#define EMS_ERROR_88h   88h     /* insufficient memory pages available                                                                                  */
#define EMS_ERROR_89h   89h     /* zero pages requested                                                                                                 */
#define EMS_ERROR_8Ah   8Ah     /* invalid logical page number encountered                                                                              */
#define EMS_ERROR_8Bh   8Bh     /* invalid physical page number encountered                                                                             */
#define EMS_ERROR_8Ch   8Ch     /* page-mapping hardware state save area is full                                                                        */
#define EMS_ERROR_8Dh   8Dh     /* save of mapping context failed                                                                                       */
#define EMS_ERROR_8Eh   8Eh     /* restore of mapping context failed                                                                                    */
#define EMS_ERROR_8Fh   8Fh     /* undefined subfunction                                                                                                */
#define EMS_ERROR_90h   90h     /* undefined attribute type                                                                                             */
#define EMS_ERROR_91h   91h     /* feature not supported                                                                                                */
#define EMS_ERROR_92h   92h     /* successful, but a portion of the source region has been overwritten                                                  */
#define EMS_ERROR_93h   93h     /* length of source or destination region exceeds length of region allocated to either source or destination handle     */
#define EMS_ERROR_94h   94h     /* conventional and expanded memory regions overlap                                                                     */
#define EMS_ERROR_95h   95h     /* offset within logical page exceeds size of logical page                                                              */
#define EMS_ERROR_96h   96h     /* region length exceeds 1M                                                                                             */
#define EMS_ERROR_97h   97h     /* source and destination EMS regions have same handle and overlap                                                      */
#define EMS_ERROR_98h   98h     /* memory source or destination type undefined                                                                          */
#define EMS_ERROR_9Ah   9Ah     /* specified alternate map register or DMA register set not supported                                                   */
#define EMS_ERROR_9Bh   9Bh     /* all alternate map register or DMA register sets currently allocated                                                  */
#define EMS_ERROR_9Ch   9Ch     /* alternate map register or DMA register sets not supported                                                            */
#define EMS_ERROR_9Dh   9Dh     /* undefined or unallocated alternate map register or DMA register set                                                  */
#define EMS_ERROR_9Eh   9Eh     /* dedicated DMA channels not supported                                                                                 */
#define EMS_ERROR_9Fh   9Fh     /* specified dedicated DMA channel not supported                                                                        */
#define EMS_ERROR_A0h   A0h     /* no such handle name                                                                                                  */
#define EMS_ERROR_A1h   A1h     /* a handle found had no name, or duplicate handle name                                                                 */
#define EMS_ERROR_A2h   A2h     /* attempted to wrap around 1M conventional address space                                                               */
#define EMS_ERROR_A3h   A3h     /* source array corrupted                                                                                               */
#define EMS_ERROR_A4h   A4h     /* operating system denied access                                                                                       */
