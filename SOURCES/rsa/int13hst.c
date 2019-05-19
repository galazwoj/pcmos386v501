#include "rsa.h"

#ifndef ORIGINAL_CODE
static char *status[100];

static void fill_table(void)
{
	int i;
	for(i=10; i <= 0xff; i++)
		status[i] = "unknownn ";	
	// known values for disk operation status

	status[0x00] = "successful completion";                                               	    
	status[0x01] = "invalid function in AH or invalid parameter";                               
	status[0x02] = "address mark not found";                                                    
	status[0x03] = "disk write-protected";                                                      
	status[0x04] = "sector not found/read error";                                               
	status[0x05] = "reset failed (hard disk)";                                                  
	status[0x06] = "disk changed (floppy)";                                                     
	status[0x07] = "drive parameter activity failed (hard disk)";                               
	status[0x08] = "DMA overrun";                                                               
	status[0x09] = "data boundary error (attempted DMA across 64K boundary or >80h sectors)";   
	status[0x0A] = "bad sector detected (hard disk)";                                           
	status[0x0B] = "bad track detected (hard disk)";                                            
	status[0x0C] = "unsupported track or invalid media";                                        
	status[0x0D] = "invalid number of sectors on format (PS/2 hard disk)";                      
	status[0x0E] = "control data address mark detected (hard disk)";                            
	status[0x0F] = "DMA arbitration level out of range (hard disk)";                            
	status[0x10] = "uncorrectable CRC or ECC error on read";                                    
	status[0x11] = "data ECC corrected (hard disk)";                                            
	status[0x20] = "controller failure";                                                        
	status[0x31] = "no media in drive (IBM/MS INT 13 extensions)";                              
	status[0x32] = "incorrect drive type stored in CMOS (Compaq)";                              
	status[0x40] = "seek failed";                                                               
	status[0x80] = "timeout (not ready)";                                                       
	status[0xAA] = "drive not ready (hard disk)";                                               
	status[0xB0] = "volume not locked in drive (INT 13 extensions)";                            
	status[0xB1] = "volume locked in drive (INT 13 extensions)";                                
	status[0xB2] = "volume not removable (INT 13 extensions)";                                  
	status[0xB3] = "volume in use (INT 13 extensions)";                                         
	status[0xB4] = "lock count exceeded (INT 13 extensions)";                                   
	status[0xB5] = "valid eject request failed (INT 13 extensions)";                            
	status[0xB6] = "volume present but read protected (INT 13 extensions)";                     
	status[0xBB] = "undefined error (hard disk)";                                               
	status[0xCC] = "write fault (hard disk)";                                                   
	status[0xE0] = "status register error (hard disk)";                                         
	status[0xFF] = "sense operation failed (hard disk)";                                       
};
 
char *int13h_status(int id)
{
	static table_completed = 0;
	if(!table_completed)
	{
		fill_table();
		table_completed = 1;
	}
	if (id > 0xff)
		id = 0xfe;
	return status[id];
}
#endif
