#include "_rsa.h"
#include "rsa.h"
#include <string.h>
#include <stdlib.h>

static char EMM_message[80];
char *EMM_message_start   = "EMM status: ";
char *EMM_message_ok      = "successful";                            
char *EMM_message_unknown = "unknown, code: ";
char *EMM_message_err[]     = {
  "internal error" 
 ,"hardware malfunction" 
 ,"busy -- retry later" 
 ,"invalid handle" 
 ,"undefined function requested by application" 
 ,"no more handles available" 
 ,"error in save or restore of mapping context" 
 ,"insufficient memory pages in system" 
 ,"insufficient memory pages available" 
 ,"zero pages requested" 
 ,"invalid logical page number encountered" 
 ,"invalid physical page number encountered" 
 ,"page-mapping hardware state save area is full " 
 ,"save of mapping context failed" 
 ,"restore of mapping context failed " 
 ,"undefined subfunction" 
 ,"undefined attribute type" 
 ,"feature not supported" 
 ,"successful, but a portion of the source region has been overwritten" 
 ,"length of source or destination region exceeds length of region allocated to either source or destination handle" 
 ,"conventional and expanded memory regions overlap" 
 ,"offset within logical page exceeds size of logical page" 
 ,"region length exceeds 1M" 
 ,"source and destination EMS regions have same handle and overlap" 
 ,"memory source or destination type undefined" 
 ,"specified alternate map register or DMA register set not supported" 
 ,"all alternate map register or DMA register sets currently allocated" 
 ,"alternate map register or DMA register sets not supported" 
 ,"undefined or unallocated alternate map register or DMA register set" 
 ,"dedicated DMA channels not supported" 
 ,"specified dedicated DMA channel not supported" 
 ,"no such handle name" 
 ,"a handle found had no name, or duplicate handle name" 
 ,"attempted to wrap around 1M conventional address space" 
 ,"source array corrupted" 
 ,"operating system denied access"}; 
 
char *EMM_error(int status)
{
	char number[4];
	strcpy(EMM_message, EMM_message_start);
	if (status == EMM_NO_ERROR)
		strcat(EMM_message, EMM_message_ok);
	else 
	{
		if (status < 0 || status < EMM_ERROR_80h || status > EMM_ERROR_A4h) 
		{
			itoa(status, number, 16);	
			strcat(EMM_message, EMM_message_unknown);
			strcat(EMM_message, number);
		} else 
			strcat(EMM_message, EMM_message_err[status - EMM_ERROR_80h]);			
	}
	return EMM_message;
}
