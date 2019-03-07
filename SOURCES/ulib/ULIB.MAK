#======================================================================
#
#	makefile for:	ulib.lib
#	creation date:	01/31/92
#	revision date:	05/21/92
#	programmer:	mjs
#
#======================================================================
#
# mjs 05/21/92	added data for ulexptab.obj/.c
#
#======================================================================
#
# this make file uses the ulib.xxx file as a flag to control the
# rebuilding of the extracted text index for ulib.  when any implicit
# rule fires, the ulib.xxx file is deleted.  this will force the
# command body for the rule with the ulib.xxx target to be executed.
# this execution will run the genlbndx batch file and then create
# a new copy of ulib.xxx.
#
# the genlbndx batch file is required since the extract command that
# is run from this batch file requires the '#' character as one
# of its parameters.
#
#======================================================================

#==== implicit rules

# Microsoft LIB does not work under Windows Vista, 
# vas a teporary workaround Borland TLIB is used

.c.obj:
    cl -c -I. -I..\include $&.c
    lib ulib -+$&.obj;

.asm.obj:
    masm /mx /z $&;
    lib ulib -+$&.obj;

#==== the main target

ulib.lib :	ulbeep.obj   ulstr2v.obj  ulclrbox.obj uldrwbox.obj \
		ulsetvpt.obj uldrwhbr.obj uldrwvbr.obj uldspdec.obj \
		ulsetatr.obj ulscrlup.obj ulsetcur.obj ulgetkey.obj \
		ulchar2v.obj ulgetkst.obj ulscrldn.obj ulgetcur.obj \
		ulsvrswn.obj ulmessag.obj ulfilbox.obj ulopclwn.obj \
		ulcls.obj    ulview.obj   ulifkey.obj  uleatkey.obj \
		ulgetstr.obj ulgetxy.obj  ulgetcho.obj ulanyfil.obj \
		ulremfil.obj ulexptab.obj ultrdir.obj  ultrdirl.obj \
		ulwalktr.obj ulismos.obj  ulmkpth.obj  ulfsize.obj  \
		ulwrlbl.obj  ulrdlbl.obj  ulformt.obj  ulqualt.obj  \
		misc.obj
	-del ulib.bak
	copy ulib.lib ..\libs
#==== c dependencies

ulbeep.obj	: ulbeep.c	..\include\ulib.h
ulstr2v.obj	: ulstr2v.c	..\include\ulib.h
ulclrbox.obj	: ulclrbox.c	..\include\ulib.h
ulcls.obj	: ulcls.c	..\include\ulib.h
uldrwbox.obj	: uldrwbox.c	..\include\ulib.h
ulfilbox.obj	: ulfilbox.c	..\include\ulib.h
ulsetvpt.obj	: ulsetvpt.c	..\include\ulib.h
uldrwhbr.obj	: uldrwhbr.c	..\include\ulib.h
uldrwvbr.obj	: uldrwvbr.c	..\include\ulib.h
uldspdec.obj	: uldspdec.c	..\include\ulib.h
ulsetatr.obj	: ulsetatr.c	..\include\ulib.h
ulscrlup.obj	: ulscrlup.c	..\include\ulib.h
ulsetcur.obj	: ulsetcur.c	..\include\ulib.h
ulgetcur.obj	: ulgetcur.c	..\include\ulib.h
ulgetkey.obj	: ulgetkey.c	..\include\ulib.h
uleatkey.obj	: uleatkey.c	..\include\ulib.h
ulifkey.obj	: ulifkey.c	..\include\ulib.h
ulchar2v.obj	: ulchar2v.c	..\include\ulib.h
ulgetkst.obj	: ulgetkst.c	..\include\ulib.h
ulscrldn.obj	: ulscrldn.c	..\include\ulib.h
ulmessag.obj	: ulmessag.c	..\include\ulib.h
ulopclwn.obj	: ulopclwn.c	..\include\ulib.h
ulview.obj	: ulview.c	..\include\ulib.h
ulgetstr.obj	: ulgetstr.c	..\include\ulib.h
ulgetxy.obj	: ulgetxy.c	..\include\ulib.h
ulgetcho.obj	: ulgetcho.c	..\include\ulib.h
ulanyfil.obj	: ulanyfil.c	..\include\ulib.h
ulremfil.obj	: ulremfil.c	..\include\ulib.h
ulexptab.obj	: ulexptab.c	..\include\ulib.h
ultrdir.obj	: ultrdir.c	..\include\ulib.h
ultrdirl.obj	: ultrdirl.c	..\include\ulib.h
ulwalktr.obj	: ulwalktr.c	..\include\ulib.h
ulismos.obj	: ulismos.c	..\include\ulib.h
ulmkpth.obj	: ulmkpth.c	..\include\ulib.h
ulfsize.obj	: ulfsize.c	..\include\ulib.h
ulwrlbl.obj	: ulwrlbl.c	..\include\ulib.h
ulrdlbl.obj	: ulrdlbl.c	..\include\ulib.h
ulformt.obj	: ulformt.c	..\include\ulib.h
ulqualt.obj	: ulqualt.c	..\include\ulib.h
                                
#==== asm dependencies

ulsvrswn.obj	: ulsvrswn.asm
misc.obj	: misc.asm
	
clean:
	-del *.lib *.obj
