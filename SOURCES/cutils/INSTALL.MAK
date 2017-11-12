#======================================================================
#
#	makefile for:	install
#	creation date:	04/01/92
#	revision date:	04/01/92
#	programmer:	mjs
#
#======================================================================
#
# mjs 04/01/92	dlg mods: created this module.
# 
#======================================================================
#

.c.obj:
        cl -c $<

.asm.obj:
        masm -Mx $*;

all:	install.exe

OBJECTS =       install.obj insasm.obj
OBJLIST =       install +insasm
LIBRARIES = ..\libs\ULIB.LIB

install.exe : $(OBJECTS) $(LIBRARIES)
        link $(OBJLIST)/e,,, ulib

install.obj : install.c insasm.h vidattr.h ..\include\asmtypes.h \
	      dskstruc.h  ..\include\ulib.h summary.h

clean:
	-del *.obj *.pub *.exe *.map
