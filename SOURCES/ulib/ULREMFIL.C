/*
;,fs
;******** $.
;,fe
=====================================================================
               (c) copyright 1992, the software link inc.
                       all rights reserved

 module name:        ulremfil.c
 creation date:      04/01/92
 revision date:      
 author:             mjs
 description:        ulib module

======================================================================

mjs 04/01/92	created this module

=======================================================================
*/

#include <stdlib.h>
#include <dos.h>
#include <io.h>
#include <string.h>
#include "ulib.h"

/*======================================================================
;,fs
; byte ul_remove_files(byte *filespec, byte search_attr)
; 
; in:	filespec -> file specification string (e.g. "c:\\xyz\\abc*.*")
;	search_attr = attribute, using FA_NORMAL, FA_RDONLY, etc.
;
; out:	retval = 0 if successful
;	retval = 1 if an error occured
;
;,fe
========================================================================*/

#define MAXPATH   80
#define MAXDRIVE  3
#define MAXDIR    66
#define MAXFILE   9
#define MAXEXT    5

byte ul_remove_files(byte *filespec, byte search_attr) {

  word first;				// controls findfirst/next calls
  word err_stat;			// holds error status
  struct find_t ffblk;			// for findfirst/next
  byte drvstr[MAXDRIVE];		// for fnsplit
  byte pathstr[MAXDIR];			// for fnsplit
  byte fnamestr[MAXFILE];		// for fnsplit
  byte extstr[MAXEXT];			// for fnsplit
  byte wbuf[MAXPATH];			// holds d:\path filespec portion
  byte *trunc_ptr;			// used to maintain wbuf
  word attr;				// each file's attribute

  _splitpath(filespec,drvstr,pathstr,fnamestr,extstr);
  strcpy(wbuf,drvstr);
  strcat(wbuf,pathstr);
  trunc_ptr = strchr(wbuf,0);
  first = 1;
  while(1) {
    if(first) {
      err_stat = _dos_findfirst(filespec,search_attr, &ffblk);
      first = 0;
      }
    else {
      err_stat = _dos_findnext(&ffblk);
      }
    if(err_stat != 0) {
      if(_doserrno == 0x12) {
        return(0);
        }
      else {
        return(1);
        }
      }
    strcat(wbuf,ffblk.name);
    if(search_attr != _A_NORMAL) {
      attr = _chmod(wbuf,0);
      if(attr == 0xffff) {
        return(1);
        }
      if(attr & search_attr) {
        attr = _chmod(wbuf,1,_A_NORMAL);
        if(attr == 0xffff) {
          return(1);
          }
        }
      }
    if(remove(wbuf) != 0) {
      return(1);
      }
    *trunc_ptr = 0;
    }
  }

