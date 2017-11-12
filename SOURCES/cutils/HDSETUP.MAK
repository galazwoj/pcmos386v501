#======================================================================
#
#	makefile for:	hdsetup
#	creation date:	04/01/92
#	revision date:	04/01/92
#	programmer:	mjs
#
#======================================================================
#
# mjs 04/01/92	dlg mods: created this module.
# 
#======================================================================

.c.obj:
        cl -c $<

.asm.obj:
        masm -Mx -I..\kernel $*;

all:	hdsetup.exe

hdsetup.exe :  hdsetup.obj ..\libs\ULIB.LIB
	link  hdsetup/e,,, ulib

hdsetup.obj  : hdsetup.c vidattr.h  dskstruc.h mbrbuf.inc summary.h \
		..\include\ulib.h ..\include\asmtypes.h     

mbrbuf.inc : genmbr.exe
	genmbr > mbrbuf.inc

genmbr.exe : genmbr.obj
	link genmbr/e,,,;

genmbr.obj : genmbr.asm mbr.inc

clean:
	-del *.obj *.pub *.exe *.map mbrbuf.inc
