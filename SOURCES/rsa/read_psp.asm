.model small, C
.code
	PUBLIC	read_PSP

; NOTE! psp_buffer must be 80h words long
;	get psp segment via int 21, AX=62h
;	copy 80h words to buffer pointed by psp_buffer
;
;void	read_PSP(void *psp_buffer);
read_PSP	proc
psp_buffer	equ	[bp+4]
	push	bp
	mov	bp,sp
	push	ds
	push	si
	push	di
	mov	di,psp_buffer
	mov	ah,62H
	int	21H
	mov	ds,bx
	xor	si,si
	mov	cx,80H
	cld
rep 	movsw
	pop	di
	pop	si
	pop	ds
	pop	bp
	ret
read_PSP	endp

END
