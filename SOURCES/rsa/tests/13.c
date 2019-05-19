#include "rsa.h"
#include <dos.h>
#include <stdlib.h>
#include <string.h>

/* EMS_TEST 

  This program is an example of the basic EMS functions that you need to execute in order to use EMS memory with the RSA library 

  Loosely based on a Pascal program by
    Peter Immarco.
    Thought Dynamics
    Manhattan Beach, CA
    Compuserve ID# 73770,123
     *** Public Domain ***

  Translated to C to use RSA lib in 2019.

*/

//	We'll say we need 1 EMS page for our application 
#define  APPLICATION_PAGE_COUNT 	1

#define MK_FP( seg,ofs ) (void far * )(((unsigned long)((unsigned long)(seg) << 16)) + ((unsigned long)(ofs)))

int main(void)
{
	int error;
	int version;
	int handles;
	int pages_needed;
	int total_EMS_pages;
	int available_EMS_pages;
	int EMM_handle;
	int logical_page; 
	int physical_page;
	int logical_pages;
#ifdef  ORIGINAL_CODE
	void far *page_frame;
#endif
	unsigned page_frame_segment;
	unsigned offset;
	unsigned int *map;
	int table_size;

//  	Determine if the Expanded Memory Manager is installed.
 	if (!EMM_present()) 
	{
   		puts("The LIM Expanded Memory Manager is not installed.");
		return 1;  
	}

//  	Get LIM Manager status and display it.
	if ((error = EMM_status()) != EMM_NO_ERROR)
	{
		printf("LIM Expanded Memory Manager status is not OK. %s\n", EMM_error(error));
		return 1;
	}
	else
		printf("LIM Expanded Memory Manager status is fine.\n");

//  	Get the version number and display it.	
	if ((error = EMM_get_version(&version)) != EMM_NO_ERROR)
	{
		printf("Error trying to get the EMS version number. %s\n", EMM_error(error));
		return 1;
	}
	else
		printf("LIM Expanded Memory Manager, version %d, is ready for use.\n", version);

//	Determine number of EMM handles
	if ((error = EMM_get_handle_count(&handles)) != EMM_NO_ERROR)
	{
		printf("Error trying to get the number of EMM handles. %s\n", EMM_error(error));
		return 1;
	}
	else
		printf("Number of EMM handles %d, ready for use.\n", handles);

// 	Determine if there are enough expanded memory pages for this application.
  	pages_needed = APPLICATION_PAGE_COUNT;
  	if ((error = EMM_get_page_count(&total_EMS_pages,&available_EMS_pages)) != EMM_NO_ERROR)
	{
    		printf("Error trying to determine the number of EMS pages available. %s\n", EMM_error(error));
		return 1;
	}
	else
	 	printf("There are a total of %d expanded memory pages present in this system.\n"
		       "of which %d pages are available for your usage.\n",total_EMS_pages, available_EMS_pages);
  	if (pages_needed > available_EMS_pages)
	{
    		printf("We need %d EMS pages. There are not that many available. %s\n", pages_needed, EMM_error(error));
         	return 1;
	}

//	Allocate expanded memory pages for our usage                                                                                                                            
  	if((error= EMM_allocate_pages(pages_needed, &EMM_handle)) != EMM_NO_ERROR)
	{
		printf("EMS test program failed trying to allocate %d pages for usage. %s\n", pages_needed, EMM_error(error));
		return 1;
	}
	else
  		printf("%d EMS page(s) allocated for the EMS test program.\n", APPLICATION_PAGE_COUNT);

//   Map in the required logical pages to the physical pages given to us, in this case just one page                    
  	logical_page  = 0;
  	physical_page = 0;
  	if ((error = EMM_map_page(EMM_handle, logical_page, physical_page)) != EMM_NO_ERROR)
	{
    		printf("EMS test program failed trying to map logical pages onto physical pages. %s", EMM_error(error));
		return 1;
	}
	else
  		printf("Logical Page %d successfully mapped onto Physical Page %d.\n", logical_page, physical_page);

//	Get the number of logical pages
  	if ((error = EMM_get_handle_pages(EMM_handle, &logical_pages)) != EMM_NO_ERROR)
	{
    		printf("EMS test program failed trying to get the number of logical pages. %s", EMM_error(error));
		return 1;
	}
	else
  		printf("Number of logical pages %d.\n", logical_pages);

//	Get pages for all handles
	if ((map = malloc(1024)))
	{
		int active_handles;
		if ((error = EMM_get_handle_map(&active_handles, map)) != EMM_NO_ERROR)
	    		printf("EMS test program failed trying to get the number of activre handles. %s", EMM_error(error));	
		else
  			printf("Number of active handles %d.\n", active_handles);
		free(map);
	}
	else
		puts("Not enough memory to get handle map.");

//	Save page mapping and then restore it
  	if((error = EMM_save_page_map(EMM_handle)) != EMM_NO_ERROR)
    		printf("EMS test program unable to save page mapping. %s\n",EMM_error(error));
	else
	{
  		printf("Page mapping saved.\n");
	  	if((error = EMM_restore_page_map(EMM_handle)) != EMM_NO_ERROR)
	    		printf("EMS test program unable to restore page mapping. %s\n",EMM_error(error));
		else
	  		printf("Page mapping restored.\n");
	}
	                  
//	Get the expanded memory page frame address
#ifdef ORIGINAL_CODE
	page_frame = NULL;	
	error = EMM_ERROR_80h;
  	page_frame = EMM_get_page_frame();
	error = EMM_status();
	page_frame_segment = FP_SEG(page_frame);   
  	if(page_frame = NULL || page_frame_segment == 0 || error != EMM_NO_ERROR)
#else
  	if((error = EMM_get_page_frame(&page_frame_segment)) != EMM_NO_ERROR)
#endif
	{
    		printf("EMS test program unable to get the base Page Frame Address. %s\n",EMM_error(error));
		return 1;
	}
	else
  		printf("The base address of the EMS page frame is %x.\n", page_frame_segment);

//	Write a test pattern to expanded memory
	for(offset = 4; offset <= 16382; offset ++) 
	{
	    	unsigned char far *value = MK_FP(page_frame_segment, offset);
		*value = (unsigned char)(offset % 256);
	}

//	Make sure that what is in EMS memory is what we just wrote
  	printf("Testing EMS memory.\n");

  	for (offset = 4; offset <= 16382; offset ++) 
	{
	    	unsigned char far *value = MK_FP(page_frame_segment, offset);
		if (*value != (unsigned char)(offset % 256))
      			break;
	}
  	if(offset < 16382)
    		printf("WRONG, inconsistency in EMS memory found during memory verification at pos %d.\n", offset);
	else
 		puts("EMS memory test successful.");

//	Save / restore page  map
  	if((error = EMM_get_page_map_size(&table_size)) != EMM_NO_ERROR)
    		printf("EMS test program unable to get page mapping table size. %s\n",EMM_error(error));
	else
	{
		char *source_table;
		char *target_table;
  		printf("Page mapping table size %d.\n", table_size);
		if ((source_table = malloc(table_size)))
		{
			if ((target_table = malloc(table_size)))
			{
			  	if((error = EMM_get_page_map(target_table)) != EMM_NO_ERROR)
			    		printf("EMS test program unable to get page mapping. %s\n",EMM_error(error));
				else
			  		printf("Page mapping saved.\n");

				memcpy(source_table, target_table, table_size);

			  	if((error = EMM_set_page_map(source_table)) != EMM_NO_ERROR)
			    		printf("EMS test program unable to set page mapping. %s\n",EMM_error(error));
				else
			  		printf("Page mapping restored.\n");

			  	if((error = EMM_get_set_page_map(source_table, target_table)) != EMM_NO_ERROR)
			    		printf("EMS test program unable to get/set page mapping. %s\n",EMM_error(error));
				else
			  		printf("Page mapping saved/restored.\n");	

				free(target_table);
			}
			else
				puts("Not enough memory to set target handle map.");
			free(source_table);
		}
		else
			puts("Not enough memory to get/set handle map.");
	}
	
//	Return the expanded memory pages given to us back to the EMS memory pool before terminating our test program 
  	if ((error = EMM_free_pages(EMM_handle)) != EMM_NO_ERROR)
    		printf("EMS test program was unable to deallocate the EMS pages in use. %s", EMM_error(error));
	else
	  	printf("%d page(s) deallocated.\n", APPLICATION_PAGE_COUNT);
  	puts("EMS test program completed.");
	return 0;
}
