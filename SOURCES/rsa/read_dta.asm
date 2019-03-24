.model small, C
.code
	PUBLIC	read_DTA

;void   read_DTA(void *buf, int count);
read_DTA proc
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
	int	21H			; DOS 2+ - GET DISK TRANSFER AREA ADDRESS ES:BX
	push	es
	push	bx
	mov	ax,ds
	mov	es,ax
	mov	di,buf
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
