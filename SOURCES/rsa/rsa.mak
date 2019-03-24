
#==== implicit rules

.c.obj:
    cl -c -W3 -I. $&.c
    lib rsasmall -+$&.obj;

.asm.obj:
    \masm51\bin\masm /mx /z $&;
    lib rsasmall -+$&.obj;

#==== the main target

rsasmall.lib :	emm string display misc
	-del rsasmall.bak
	copy rsasmall.lib ..\libs

emm:		emm_40.obj emm_41.obj emm_42.obj emm_43.obj \
		emm_44.obj emm_45.obj emm_46.obj emm_47.obj \
		emm_48.obj emm_4b.obj emm_4c.obj emm_4d.obj \
		emm_4e.obj emm_err.obj emm_pres.obj

string:		center.obj crc16.obj decrypt.obj encrypt.obj index.obj squeze.obj squezen.obj strip_l.obj strip_t.obj \
		strstri.obj zap.obj

display:	chg_vid.obj cursor.obj cv2tmono.obj dispcopy.obj dputchar.obj \
		dputs.obj get_vid.obj iscolor.obj putscr.obj put_cpos.obj rdcpos.obj rest_vid.obj rw_video.obj save_vid.obj scr.obj scroll.obj \
		set_stan.obj usr_disc.obj

misc:		abs2seg.obj copyfile.obj countfil.obj delay.obj get_cpu.obj globals.obj mouse.obj normaliz.obj seg2abs.obj

file:		da_close.obj da_open.obj ffill.obj get_line.obj

bios:		biosdisk.obj diskfree.obj filedate.obj find_1st.obj findnext.obj getcpath.obj getfattr.obj getfsize.obj getlabel.obj gtime.obj\
		inkey.obj is_mos.obj mos_wait.obj read_dta.obj read_psp.obj setfattr.obj setlabel.obj setupi24.obj wait4key.obj writedta.obj

#==== c dependencies

abs2seg.obj	: abs2seg.c	rsa.h  	_rsa.h
center.obj	: center.c	rsa.h
copyfile.obj	: copyfile.c	rsa.h
countfil.obj	: countfil.c    rsa.h	
crc16.obj	: crc16.c	rsa.h
cursor.obj	: cursor.c	rsa.h	_rsa.h
cv2tmono.obj	: cv2tmono.c	rsa.h
da_close.obj	: da_close.c	rsa.h	_rsa.h
da_open.obj	: da_open.c	rsa.h	_rsa.h
delay.obj	: delay.c	rsa.h
diskfree.obj	: diskfree.c	rsa.h	_rsa.h	
dispcopy.obj	: dispcopy.c	rsa.h
dputs.obj	: dputs.c	rsa.h
emm_40.obj	: emm_40.c	rsa.h	_rsa.h
emm_41.obj	: emm_41.c	rsa.h	_rsa.h
emm_42.obj	: emm_42.c	rsa.h	_rsa.h
emm_43.obj	: emm_43.c	rsa.h	_rsa.h
emm_44.obj	: emm_44.c	rsa.h	_rsa.h
emm_45.obj	: emm_45.c	rsa.h	_rsa.h
emm_46.obj	: emm_46.c	rsa.h	_rsa.h
emm_47.obj	: emm_47.c	rsa.h	_rsa.h
emm_48.obj	: emm_48.c	rsa.h	_rsa.h
emm_4b.obj	: emm_4b.c	rsa.h	_rsa.h
emm_4c.obj	: emm_4c.c	rsa.h	_rsa.h
emm_4d.obj	: emm_4d.c	rsa.h	_rsa.h
emm_4e.obj	: emm_4e.c	rsa.h	_rsa.h
emm_err.obj	: emm_err.c	rsa.h   _rsa.h
emm_pres.obj	: emm_pres.c	rsa.h	_rsa.h
ffill.obj	: ffill.c	rsa.h
getfsize.obj	: getfsize.c	rsa.h
getlabel.obj	: getlabel.c	rsa.h
get_line.obj	: get_line.c	rsa.h
globals.obj	: globals.c     rsa.h	_rsa.h
gtime.obj	: gtime.c	rsa.h	_rsa.h
index.obj	: index.c	rsa.h
iscolor.obj	: iscolor.c	rsa.h	_rsa.h		
mouse.obj	: mouse.c       rsa.h	_rsa.h	
normaliz.obj	: normaliz.c    rsa.h	_rsa.h	
putscr.obj	: putscr.c	rsa.h	_rsa.h
put_cpos.obj	: put_cpos.c  	rsa.h	_rsa.h	
rdcpos.obj	: rdcpos.c	rsa.h	_rsa.h	
rest_vid.obj	: rest_vid.c	rsa.h	_rsa.h
save_vid.obj	: save_vid.c	rsa.h	_rsa.h
scr.obj 	: scr.c         rsa.h	_rsa.h
scroll.obj	: scroll.c      rsa.h   _rsa.h
seg2abs.obj	: seg2abs.c	rsa.h	_rsa.h	
set_stan.obj	: set_stan.c	rsa.h	_rsa.h
squeze.obj	: squeze.c	rsa.h
squezen.obj	: squezen.c	rsa.h                                
strip_l.obj	: strip_l.c     rsa.h
strip_t.obj	: strip_t.c     rsa.h
strstri.obj	: strstri.c     rsa.h

usr_disc.obj	: usr_disc.c    rsa.h	_rsa.h
wait4key.obj	: wait4key.c	rsa.h
zap.obj		: zap.c         rsa.h

#==== asm dependencies
biosdisk.obj	: biosdisk.asm
chg_vid.obj	: chg_vid.asm
decrypt.obj	: decrypt.asm
dputchar.obj	: dputchar.asm
encrypt.obj	: encrypt.asm
filedate.obj	: filedate.asm
find_1st.obj	: find_1st.asm	
findnext.obj	: findnext.asm
getcpath.obj	: getcpath.asm
get_cpu.obj	: get_cpu.asm
get_vid.obj	: get_vid.asm
getfattr.obj	: getfattr.asm	
inkey.obj	: inkey.asm
is_mos.obj	: is_mos.asm
mos_wait.obj	: mos_wait.asm	
read_dta.obj	: read_dta.asm
read_psp.obj	: read_psp.asm
rw_video.obj	: rw_video.asm
setfattr.obj	: setfattr.asm	
setlabel.obj	: setlabel.asm
setupi24.obj	: setupi24.asm
writedta.obj	: writedta.asm

clean:
	-del *.lib *.obj
