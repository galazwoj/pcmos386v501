# -----------------------------------
# makefile(C) Copright Bill Buckels 2008. All rights reserved.
# 
# The Aztec C86 version 5.2a compiler CC.EXE when run in Windows XP either from
# the XP cmd window or from the DOSBox emulator cannot load pass 2 of the
# compiler (CGEN.EXE) and also cannot load the assembler AS.EXE which converts
# the pass 2 assembler to an Aztec C .o (object) file prior to linking unless
# these two executables are in the current directory. Pathing is apparently not
# working and the problem seems to stem from the fact that this compiler is
# designed to spawn CGEN.EXE and AS.EXE from withing CC.EXE.
# 
# I have devised a work-around in my MAKEFILEs to address this problem after
# trying different permutations of pathing and reviewing the string data in the
# CC.EXE binary to see if I could spot a direct call to command.com which I
# cannot. I assume that the path string is being used in some way but it is not
# obvious what the error is otherwise I would have tried to patch-it.
# 
# Despite this problem, which may or may not have existed in MS-DOS in 1992
# when this compiler was released, this compiler seems to be working correctly
# with my workaround which is to copy the missing CGEN.EXE and AS.EXE into the
# build directory and then to delete them after the build. This solution is
# admittedly less elegant than a patch which fixes the problem, but still
# enables the use of this compiler under Windows XP. Alternately, if one wishes,
# compile to ASM first by using CC -A and then assemble with AS.EXE in which
# case it is only necessary to copy CGEN.EXE to the current directory.
# 
# -----------------------------------
PRG=modem
$(PRG).exe: $(PRG).o
            ln $(PRG).o -ls -lc 
#            del $(PRG).o
            @echo All Done!

$(PRG).o: $(PRG).c
           copy $(CBIN)CGEN.EXE .
           cc -A +C $(PRG).c
           as $(PRG).asm
           del $(PRG).asm
           del CGEN.EXE
