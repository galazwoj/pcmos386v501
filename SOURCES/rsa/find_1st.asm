.model small, C
.code
	PUBLIC	find_first_file

DTA_ofs	dw 0
DTA_seg	dw 0
;int find_first_file(char *filespec, char *filename, unsigned *attribute);
find_first_file proc
filespec	equ	[bp+4]
filename	equ	[bp+6]
attribute	equ	[bp+8]
	push	bp
	mov	bp,sp
	push	ds
	push	es
	push	si
	push	di
	push	es
	mov	ax,2f00H
	int	21H			; DOS 2+ - GET DISK TRANSFER AREA ADDRESS
	mov	cs:DTA_ofs,bx
	mov	cs:DTA_seg,es
	pop	es
	mov	cx,18H
	mov	dx,filespec
	mov	ax,4e00H
	int	21H                     ; DOS 2+ - FINDFIRST - FIND FIRST MATCHING FILE
	jnc	L$3			
	xor	ax,ax
	jmp	L$5
L$3:
	mov	di,attribute
	lds	si,dword ptr cs:DTA_ofs
	xor	ah,ah
	mov	al,15H[si]    		; file attribute
	stosw            		; al => attribute
	add	si,1eH      		; file name.ext
	cld
	mov	di,filename
L$4:
	lodsb
	stosb
	cmp	al,0
	jne	L$4
	mov	ax,0ffffH		; file found
L$5:
	pop	di
	pop	si
	pop	es
	pop	ds
	pop	bp
	ret
find_first_file endp
	END
