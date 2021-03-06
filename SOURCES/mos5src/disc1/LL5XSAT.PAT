;
; This patch is to be applied to the LANSAT.SYS program in
; LANLink 5X Release 2.1 for compatibility with PC-MOS Release 5.01
;
; To apply this patch, follow these steps:
;
; 1. Change into the directory that contains the file LANSAT.SYS.
;
; 2. Copy the file LL5XSAT.PAT into that subdirectory.
;
; 3. Enter the following command at the system prompt:
;
;         DEBUG LANSAT.SYS < LL5XSAT.PAT
;
;    (Make sure that the location of DEBUG.COM is in your
;     path statement, or the DEBUG program won't run.)
;
; This command will automatically load DEBUG, apply the following
; patch for you, and exit DEBUG.
;
;

E CS:01DE E9 B8 12 90 90
E CS:1499 81 3E 88 1F 01 05
E CS:149F 72 03
E CS:14A1 E9 4F ED
E CS:14A4 80 3E 83 1F 59
E CS:14A9 E9 37 ED

W
Q
                                                                                                           