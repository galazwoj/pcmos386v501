.model small, C
.code
	PUBLIC	find_next_file

DTA_ofs	dw 0
DTA_seg	dw 0
;int find_next_file(char *filename, unsigned *attribute);
find_next_file proc
filename	equ	[bp+4]
attribute	equ	[bp+6]
	push	bp
	mov	bp,sp
	push	ds
	push	es
	push	si
	push	di
	push	es
	mov	ax,2f00H		; DOS 2+ - GET DISK TRANSFER AREA ADDRESS
	int	21H
	mov	cs:DTA_ofs,bx
	mov	cs:DTA_seg,es
	pop	es
	mov	ax,4f00H
	int	21H			; DOS 2+ - FINDNEXT - FIND NEXT MATCHING FILE
	jnc	L$3
	xor	ax,ax
	jmp	L$5
L$3:
	mov	di,attribute
	lds	si,dword ptr cs:DTA_ofs
	xor	ah,ah
	mov	al,byte ptr 15H[si]  	; file attribute
	stosw				; al => attribute
	add	si,1eH 			; file name.ext
	cld
	mov	di,filename
L$4:
	lodsb
	stosb
	cmp	al,0			; copy all file name.ext
	jne	L$4
	mov	ax,0ffffH		; file found
L$5:
	pop	di
	pop	si
	pop	es
	pop	ds
	pop	bp
	ret
find_next_file endp
	END
