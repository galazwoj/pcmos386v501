rem
rem	create help.exe
rem
@echo off
cl /c /Zp /W3 main.c
cl /c /W3 misc.c
\masm51\bin\masm sound.asm,,;
\masm51\bin\masm scroll.asm,,;
link /map scroll.obj + sound.obj + misc.obj + main.obj, help,, graphics.lib

