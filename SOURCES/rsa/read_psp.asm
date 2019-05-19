ifdef _LARGE_
.model large, C
else
.model small, C
endif

.code
	PUBLIC	read_PSP

; NOTE! psp_buffer must be 80h words long
;	get psp segment via int 21, AX=62h
;	copy 80h words to buffer pointed by psp_buffer
;
;void	read_PSP(void *psp_buffer);
read_PSP	proc
if @DataSize eq 0
psp_buffer	equ	[bp+4]
else
psp_buffer	equ	[bp+6]
endif
	push	bp
	mov	bp,sp
	push	ds
	push	si
	push	di
if @DataSize eq 0
	mov	di,psp_buffer
else
	push	es
	les	di,psp_buffer
endif
	mov	ah,62H
	int	21H
	mov	ds,bx
	xor	si,si
	mov	cx,80H
	cld
rep 	movsw
if @DataSize gt 0
	pop	es
endif
	pop	di
	pop	si
	pop	ds
	pop	bp
	ret
read_PSP	endp

END
