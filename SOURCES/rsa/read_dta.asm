ifdef _LARGE_
.model large, C
else
.model small, C
endif

.code
	PUBLIC	read_DTA

;void   read_DTA(void *buf, int count);
read_DTA proc
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
	int	21H			; DOS 2+ - GET DISK TRANSFER AREA ADDRESS ES:BX
	push	es
	push	bx
if @DataSize eq 0
	mov	ax,ds
	mov	es,ax
	mov	di,buf
else
	les	di,dword ptr buf
endif
	pop	si
	pop	ds
	mov	cx,count
rep 	movsb			
	pop	di
	pop	si
	pop	es
	pop	ds
	pop	bp
	ret
read_DTA endp
	END
