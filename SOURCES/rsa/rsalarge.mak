
#==== implicit rules

.c.obj:
    	cl -c -AL -W3 -I. $&.c
    	lib rsalarge -+$&.obj;

.asm.obj:
    	\masm51\bin\masm /Ml /z /D_LARGE_ $&;
    	lib rsalarge -+$&.obj;

#==== the main target

rsalarge.lib :	emm string display misc file bios usr
	-del rsalarge.bak
	copy rsalarge.lib ..\libs

emm:		emm_40.obj emm_41.obj emm_42.obj emm_43.obj \
		emm_44.obj emm_45.obj emm_46.obj emm_47.obj \
		emm_48.obj emm_4b.obj emm_4c.obj emm_4d.obj \
		emm_4e.obj emm_err.obj emm_pres.obj

string:		center.obj crc16.obj cvt_tabs.obj decrypt.obj dumpbuff.obj encrypt.obj get_str.obj hash.obj htoi.obj index.obj just.obj \
		squeze.obj squezen.obj strip_l.obj strip_t.obj strstri.obj zap.obj

display:	chg_vid.obj cursor.obj cv2tmono.obj dispcopy.obj dputchar.obj dputs.obj draw_box.obj get_vid.obj input.obj iscolor.obj putscr.obj \
		put_cpos.obj putfld.obj rdcpos.obj rest_vid.obj rw_video.obj save_vid.obj scr.obj scroll.obj set_stan.obj 

misc:		abs2seg.obj backdoor.obj compress.obj delay.obj get_cpu.obj globals.obj mouse.obj normaliz.obj seg2abs.obj

file:		archive.obj copyfile.obj countfil.obj da_close.obj da_open.obj da_read.obj da_write.obj de_arc.obj ffill.obj get_line.obj \
		killpath.obj makepath.obj treewalk.obj

bios:		biosdisk.obj diskfree.obj filedate.obj find_1st.obj findnext.obj getcpath.obj getfattr.obj getfsize.obj getlabel.obj gtime.obj\
		inkey.obj is_mos.obj int13hst.obj mos_wait.obj read_dta.obj read_psp.obj setfattr.obj setlabel.obj setupi24.obj wait4key.obj writedta.obj

usr:		conred.obj disphelp.obj readed.obj select_o.obj up_time.obj usr_clr.obj usr_conn.obj usr_disc.obj \
		usr_menu.obj usr_msg.obj usr_read.obj usr_writ.obj

#==== c dependencies

abs2seg.obj	: abs2seg.c	rsa.h  	_rsa.h
archive.obj	: archive.c	rsa.h	
center.obj	: center.c	rsa.h
compress.obj	: compress.c	rsa.h
conred.obj 	: conred.c	rsa.h	
copyfile.obj	: copyfile.c	rsa.h
countfil.obj	: countfil.c    rsa.h	
crc16.obj	: crc16.c	rsa.h
cursor.obj	: cursor.c	rsa.h	_rsa.h
cv2tmono.obj	: cv2tmono.c	rsa.h
cvt_tabs.obj	: cvt_tabs.c	rsa.h
da_close.obj	: da_close.c	rsa.h	_rsa.h
da_open.obj	: da_open.c	rsa.h	_rsa.h
da_read.obj	: da_read.c	rsa.h   _rsa.h
da_write.obj	: da_write.c	rsa.h	_rsa.h	
delay.obj	: delay.c	rsa.h
de_arc.obj 	: de_arc.c	rsa.h
diskfree.obj	: diskfree.c	rsa.h	_rsa.h	
dispcopy.obj	: dispcopy.c	rsa.h
disphelp.obj	: disphelp.c	rsa.h	_rsa.h
dputs.obj	: dputs.c	rsa.h
draw_box.obj	: draw_box.c	rsa.h   _rsa.h
dumpbuff.obj	: dumpbuff.c	rsa.h
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
get_str.obj	: get_str.c	rsa.h
globals.obj	: globals.c     rsa.h	_rsa.h
gtime.obj	: gtime.c	rsa.h	_rsa.h
hash.obj	: hash.c	rsa.h
htoi.obj	: htoi.c	rsa.h
index.obj	: index.c	rsa.h
input.obj 	: input.c	rsa.h
int13hst.obj	: int13hst.c	rsa.h
iscolor.obj	: iscolor.c	rsa.h	_rsa.h		
just.obj	: just.c	rsa.h
killpath.obj	: killpath.c	rsa.h
makepath.obj	: makepath.c   	rsa.h
mouse.obj	: mouse.c       rsa.h	_rsa.h	
normaliz.obj	: normaliz.c    rsa.h	_rsa.h	
putfld.obj 	: putfld.c	rsa.h	_rsa.h
putscr.obj	: putscr.c	rsa.h	_rsa.h
put_cpos.obj	: put_cpos.c  	rsa.h	_rsa.h	
readed.obj	: readed.c	rsa.h	_rsa.h
rdcpos.obj	: rdcpos.c	rsa.h	_rsa.h	
rest_vid.obj	: rest_vid.c	rsa.h	_rsa.h
save_vid.obj	: save_vid.c	rsa.h	_rsa.h
scr.obj 	: scr.c         rsa.h	_rsa.h
scroll.obj	: scroll.c      rsa.h   _rsa.h
seg2abs.obj	: seg2abs.c	rsa.h	_rsa.h	
select_o.obj 	: select_o.c	rsa.h	_rsa.h
set_stan.obj	: set_stan.c	rsa.h	_rsa.h
squeze.obj	: squeze.c	rsa.h
squezen.obj	: squezen.c	rsa.h                                
strip_l.obj	: strip_l.c     rsa.h
strip_t.obj	: strip_t.c     rsa.h
strstri.obj	: strstri.c     rsa.h
treewalk.obj	: treewalk.c	rsa.h
up_time.obj	: up_time.c	rsa.h	_rsa.h
usr_clr.obj	: usr_clr.c	rsa.h	_rsa.h
usr_conn.obj	: usr_conn.c	rsa.h	_rsa.h
usr_disc.obj	: usr_disc.c    rsa.h	_rsa.h
usr_menu.obj	: usr_menu.c	rsa.h	_rsa.h
usr_msg.obj	: usr_msg.c	rsa.h	_rsa.h
usr_read.obj	: usr_read.c	rsa.h	_rsa.h
usr_writ.obj	: usr_writ.c	rsa.h	_rsa.h
wait4key.obj	: wait4key.c	rsa.h
zap.obj		: zap.c         rsa.h

#==== asm dependencies
backdoor.obj 	: backdoor.asm
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
