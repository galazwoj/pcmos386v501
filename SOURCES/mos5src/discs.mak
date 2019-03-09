all:		\
	disc1 	\
	disc2 	\
	disc3 	\
	disc4	\
	delfiles

#
#	disc 1
#
disc1:	$$$$MOS.SYS 		\
	$$$$SHELL.SYS   	\
 	disc1\AUTOEXEC.BAT 	\
	COMMAND.COM   		\
	disc1\CONFIG.SYS   	\
	..\export\EXPORT.EXE    \
	FORMAT.COM  		\
	..\cutils\HDSETUP.EXE  	\
	disc1\HDSETUP.HLP  	\
	..\cutils\HDSETUP.MSG   \
	..\cutils\INSTALL.EXE  	\
	..\cutils\INSTALL.MSG  	\
	MOSFILES.EXE 		\
	MSYS.COM 		\
	disc1\README  		\
	UPDAT501.SYS
	&copy $? ..\..\install\disc1\.

$$$$SHELL.SYS:	__SHELL.SYS   	
	copy $? $*.sys

MOSFILES.EXE:			\
	ADDDEV.COM   		\
	ADDTASK.COM   		\
	ALIAS.COM    		\
	CLASS.COM     		\
	COMPFILE.EXE 		\
	DEBUG.COM      		\
	DIRMAP.COM    		\
	DISKCOPY.COM   		\
	DISKID.COM    		\
  	disc1\E31_P2.PAT	\
	ED.EXE 			\
        ..\export\EXPORT.EXE   	\
	FILEMODE.COM    	\
	FILTER.COM     		\
	FORMAT.COM     		\
	..\cutils\HDSETUP.EXE 	\
        disc1\HDSETUP.HLP   	\
	..\cutils\HDSETUP.MSG   \
	..\import\IMPORT.EXE    \
	INIT.COM    		\
	KEYMAP.COM 		\
	disc1\LL5M.PAT  	\
	disc1\LL5MDEMO.PAT	\
	disc1\LL5XSAT.PAT 	\
	disc1\LLLAP5M.PAT  	\
	disc1\LLLAPSAT.PAT 	\
        MISPEED.COM   		\
	disc1\MODEM.COM  	\
	MONITOR.COM    		\
	MORE.COM      		\
	MOS.COM 		\
        MOSADM.COM 		\
	disc1\MSORT.EXE		\
	MSYS.COM      		\
	NETNAME.COM   		\
        disc1\NULL.KEY        	\
	PATCHID.COM 		\
        PRINT.COM       	\
	REMDEV.COM    		\
	REMTASK.COM    		\
	SEARCH.COM 		\
	SERINFO.COM 		\
       	SETMOUSE.COM 		\
	SFT.COM       		\
	SPOOL.COM    		\
	VERIFY.EXE    		\
	VIDPATCH.COM 		
	-del MOSFILES.ZIP
	pkzip MOSFILES.ZIP @MOSFILES.cfg
	zip2exe MOSFILES.ZIP
	del MOSFILES.ZIP

#
#	disc 2
#
disc2:	auxfiles.exe
	copy $? ..\..\install\disc2\.

auxfiles.exe:			\
	$$286N.SYS		\
	$$386.SYS   		\
	$$ALL.SYS       	\
	$$ARNET.SYS     	\
	$$CHARGE.SYS    	\
	$$EMS.SYS       	\
	$$GIZMO.SYS     	\
	$$KBBE.SYS      	\
	$$KBCF.SYS      	\
	$$KBDK.SYS      	\
	$$KBFR.SYS      	\
	$$KBGR.SYS      	\
	$$KBIT.SYS     	 	\
	$$KBLA.SYS      	\
	$$KBNL.SYS      	\
	$$KBNO.SYS      	\
	$$KBPO.SYS      	\
	$$KBSF.SYS      	\
	$$KBSG.SYS      	\
	$$KBSP.SYS      	\
	$$KBSV.SYS      	\
	disc2\$$KBUK3.SYS     	\
	$$KBUK4.SYS     	\
	$$MOUSE.SYS     	\
	$$NETBIOS.SYS   	\
	$$PIPE.SYS      	\
	$$RAMDISK.SYS   	\
	$$SERIAL.SYS    	\
	19TERM.SYS      	\
	31TERM.SYS      	\
	3ATERM.SYS      	\
	52TERM.SYS      	\
	..\acu\ACU-HELP.HLP    	\
	..\acu\ACU.EXE         	\
	..\acu\ACU.MNU         	\
	ANTERM.SYS      	\
	ATTERM.SYS      	\
	AVTERM.SYS      	\
	disc2\BOX.BIN   	\
	disc2\BOX2.BIN        	\
	ELTERM.SYS      	\
	EXTERM.SYS      	\
	HELP.EXE        	\
	HELP.NDX        	\
	HELP.TXT        	\
	disc2\HGTERM.SYS      	\
	MINBRDPC.SYS    	\
	disc2\PATCH.BIN       	\
	disc2\PATCH2.BIN      	\
	PCTERM.SYS      	\
	SRTERM.SYS      	\
	T1TERM.SYS      	\
	TRTERM.SYS      	\
	TTTERM.SYS      	\
	TVTERM.SYS      	\
	UNTERM.SYS      	\
	VGNA.SYS        	\
	disc2\VGNAPLUS.ROM    	\
	VNA.SYS         	\
	W7TERM.SYS      
	-del AUXFILES.ZIP
	pkzip AUXFILES.ZIP @AUXFILES.cfg
	zip2exe AUXFILES.ZIP
	del AUXFILES.ZIP

$$286N.SYS:	    _286N.SYS	  
	copy $? $*.sys

$$386.SYS:          _386.SYS          
	copy $? $*.sys

$$ALL.SYS:          _ALL.SYS          
	copy $? $*.sys

$$ARNET.SYS:        _ARNET.SYS        
	copy $? $*.sys

$$CHARGE.SYS:       _CHARGE.SYS       
	copy $? $*.sys

$$EMS.SYS:          _EMS.SYS          
	copy $? $*.sys

$$GIZMO.SYS:        _GIZMO.SYS        
	copy $? $*.sys

$$KBBE.SYS:         _KBBE.SYS         
	copy $? $*.sys

$$KBCF.SYS:         _KBCF.SYS         
	copy $? $*.sys

$$KBDK.SYS:         _KBDK.SYS         
	copy $? $*.sys

$$KBFR.SYS:         _KBFR.SYS         
	copy $? $*.sys

$$KBGR.SYS:         _KBGR.SYS         
	copy $? $*.sys

$$KBIT.SYS:         _KBIT.SYS         
	copy $? $*.sys

$$KBLA.SYS:         _KBLA.SYS         
	copy $? $*.sys

$$KBNL.SYS:         _KBNL.SYS         
	copy $? $*.sys

$$KBNO.SYS:         _KBNO.SYS         
	copy $? $*.sys

$$KBPO.SYS:         _KBPO.SYS         
	copy $? $*.sys

$$KBSF.SYS:         _KBSF.SYS         
	copy $? $*.sys

$$KBSG.SYS:         _KBSG.SYS         
	copy $? $*.sys

$$KBSP.SYS:         _KBSP.SYS         
	copy $? $*.sys

$$KBSV.SYS:         _KBSV.SYS         
	copy $? $*.sys

$$KBUK4.SYS:        _KBUK.SYS        
	copy $? $*.sys

$$MOUSE.SYS:        _MOUSE.SYS        
	copy $? $*.sys

$$NETBIOS.SYS:      _NETBIOS.SYS      
	copy $? $*.sys

$$PIPE.SYS:         _PIPE.SYS         
	copy $? $*.sys

$$RAMDISK.SYS:      _RAMDISK.SYS      
	copy $? $*.sys

$$SERIAL.SYS:       _SERIAL.SYS       
	copy $? $*.sys

#$$KBUK3.SYS:        _KBUK3.SYS        	

#
#	disc 3
#
disc3:  	\
	disc3\BOOSTER.001	\
	disc3\INSTALL.EXE	\
	disc3\MOSCFG.DOC      	\
	disc3\PATCH9.501      	\
	disc3\PATCHER.EXE     	\
	disc3\README.DOC    	\
	disc3\UPDATE6.DOC
	&copy $? ..\..\install\disc3\.
#
#	disc 4
#
disc4:  			\
	$$$$MOS.SYS		\
	$$$$SHELL.SYS           \
	$$286N.SYS              \
	$$386.SYS               \
	$$ALL.SYS               \
	$$ARNET.SYS             \
	$$CHARGE.SYS            \
	$$EMS.SYS               \
	$$GIZMO.SYS             \
	$$KBBE.SYS              \
	$$KBCF.SYS              \
	$$KBDK.SYS              \
	$$KBFR.SYS              \
	$$KBGR.SYS              \
	$$KBIT.SYS              \
	$$KBLA.SYS              \
	$$KBNL.SYS              \
	$$KBNO.SYS              \
	$$KBPO.SYS              \
	$$KBSF.SYS              \
	$$KBSG.SYS              \
	$$KBSP.SYS              \
	$$KBSV.SYS              \
	disc2\$$KBUK3.SYS       \
	$$KBUK4.SYS             \
	$$MOUSE.SYS             \
	$$NETBIOS.SYS           \
	$$PIPE.SYS              \
	$$RAMDISK.SYS           \
	$$SERIAL.SYS            \
	19TERM.SYS              \
	31TERM.SYS              \
	3ATERM.SYS              \
	52TERM.SYS              \
	..\acu\ACU-HELP.HLP     \
	..\acu\ACU.EXE          \
	..\acu\ACU.MNU          \
	ADDDEV.COM              \
	ADDTASK.COM             \
	ALIAS.COM               \
	ANTERM.SYS              \
	ATTERM.SYS              \
	disc1\AUTOEXEC.BAT      \
	AUXFILES.EXE            \
	AVTERM.SYS              \
	disc2\BOX.BIN           \
	disc2\BOX2.BIN          \
	CLASS.COM               \
	COMMAND.COM             \
	COMPFILE.EXE            \
	disc1\CONFIG.SYS        \
	DEBUG.COM               \
	DIRMAP.COM              \
	DISKCOPY.COM            \
	DISKID.COM              \
	disc1\E31_P2.PAT        \
	ED.EXE                  \
	ELTERM.SYS              \
	..\export\EXPORT.EXE    \
	EXTERM.SYS              \
	FILEMODE.COM            \
	FILTER.COM              \
	FORMAT.COM              \
	..\cutils\HDSETUP.EXE   \
	disc1\HDSETUP.HLP       \
	..\cutils\HDSETUP.MSG   \
	disc4\HDSETUP.SUM       \
	HELP.EXE          	\
	HELP.NDX          	\
	HELP.TXT          	\
	disc2\HGTERM.SYS        \
	..\import\IMPORT.EXE    \
	INIT.COM                \
	..\cutils\INSTALL.EXE   \
	..\cutils\INSTALL.MSG   \
	KEYMAP.COM              \
	disc1\LL5M.PAT          \
	disc1\LL5MDEMO.PAT      \
	disc1\LL5XSAT.PAT       \
	disc1\LLLAP5M.PAT       \
	disc1\LLLAPSAT.PAT      \
	MINBRDPC.SYS            \
	MISPEED.COM             \
	disc1\MODEM.COM         \
	MONITOR.COM             \
	MORE.COM                \
	MOS.COM                 \
	MOSADM.COM              \
	MOSFILES.EXE            \
	disc1\MSORT.EXE         \
	MSYS.COM                \
	NETNAME.COM             \
	disc1\NULL.KEY          \
	disc2\PATCH.BIN         \
	disc2\PATCH2.BIN        \
	PATCHID.COM             \
	PCTERM.SYS              \
	PRINT.COM               \
	disc1\README            \
	REMDEV.COM              \
	REMTASK.COM             \
	SEARCH.COM              \
	SERINFO.COM             \
	SETMOUSE.COM            \
	SFT.COM                 \
	SPOOL.COM               \
	SRTERM.SYS              \
	T1TERM.SYS              \
	TRTERM.SYS              \
	TTTERM.SYS              \
	TVTERM.SYS              \
	UNTERM.SYS              \
	UPDAT501.SYS            \
	VERIFY.EXE              \
	VGNA.SYS                \
	disc2\VGNAPLUS.ROM      \
	VIDPATCH.COM            \
	VNA.SYS                 \
	W7TERM.SYS              
	&copy $? ..\..\install\disc4\.

delfiles:
	del $$$$SHELL.SYS
	del MOSFILES.EXE
	del AUXFILES.EXE
	del $$286N.SYS	
	del $$386.SYS   	
	del $$ALL.SYS       
	del $$ARNET.SYS     
	del $$CHARGE.SYS    
	del $$EMS.SYS       
	del $$GIZMO.SYS     
	del $$KBBE.SYS      
	del $$KBCF.SYS      
	del $$KBDK.SYS      
	del $$KBFR.SYS      
	del $$KBGR.SYS      
	del $$KBIT.SYS      
	del $$KBLA.SYS      
	del $$KBNL.SYS      
	del $$KBNO.SYS      
	del $$KBPO.SYS      
	del $$KBSF.SYS      
	del $$KBSG.SYS      
	del $$KBSP.SYS      
	del $$KBSV.SYS      
	del $$KBUK4.SYS     
	del $$MOUSE.SYS     
	del $$NETBIOS.SYS   
	del $$PIPE.SYS      
	del $$RAMDISK.SYS   
	del $$SERIAL.SYS    

clean:
	cd ..\..\install
	-rmdir /S /Q disc1
	-rmdir /S /Q disc2
	-rmdir /S /Q disc3
	-rmdir /S /Q disc4
	-md disc1
	-md disc2
	-md disc3
	-md disc4
