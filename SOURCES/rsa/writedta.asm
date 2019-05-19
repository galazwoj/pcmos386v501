ifdef _LARGE_
.model large, C
else
.model small, C
endif

.code
	PUBLIC	write_DTA

;void        write_DTA(void *buf, int count);
write_DTA proc
if @DataSize eq 0
buf	equ	[bp+4]
count	equ	[bp+6]
else
buf	equ	[bp+6]
count	equ	[bp+0ah]
endif
	push	bp
	mov	bp,sp
	push	ds
	push	es
	push	si
	push	di
	cld
	mov	ah,2fH
	int	21H         	; DOS 2+ - GET DISK TRANSFER AREA ADDRESS
	mov	di,bx
if @DataSize eq 0
	mov	si,buf
else
	lds	si,buf
endif
	mov	cx,count
rep 	movsb
	pop	di
	pop	si
	pop	es
	pop	ds
	pop	bp
	ret
write_DTA endp
	END
