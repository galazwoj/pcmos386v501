.model small, C
.code
	PUBLIC	write_DTA

;void        write_DTA(void *buf, int count);
write_DTA proc
buf	equ	[bp+4]
count	equ	[bp+6]
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
	mov	si,buf
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
