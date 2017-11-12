###############################################################################
#
#       MAKEFILE FOR:           EXPORT.EXE
#
#       Creation date:          1/8/91
#
#       Revision date:          1/8/91
#
#       Programmer:             B. W. Roeser
#
#       Notes:                  Compiled in small model of MSC
#
#               (C) Copyright 1991  The Software Link, Inc.
#                       All Rights Reserved
#
# ----------------------  >> Revision Log <<  --------------------------
#
# Date          Prog    Description of Revision
# ----          ----    -----------------------
#
###############################################################################
#
.c.obj:
        cl -c $<

.asm.obj:
        masm -Mx $*;

OBJECTS =       export.obj   expasm.obj 
OBJLIST =       export +expasm 
LIBRARIES = ..\libs\ULIB.LIB

export.exe : $(OBJECTS) $(LIBRARIES)
        link $(OBJLIST)/e,,, ulib

clean:
	-del *.obj *.pub *.exe *.map

