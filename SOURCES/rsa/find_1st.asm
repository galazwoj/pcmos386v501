ifdef _LARGE_
.model large, C
else
.model small, C
endif

.code
	PUBLIC	find_first_file

DTA_ofs	dw 0
DTA_seg	dw 0
;int find_first_file(char *filespec, char *filename, unsigned *attribute);
find_first_file proc
if @DataSize eq 0
filespec	equ	[bp+4]
filename	equ	[bp+6]
attribute	equ	[bp+8]
else
filespec	equ	[bp+6]
filename	equ	[bp+0ah]
attribute	equ	[bp+0eh]
endif
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
if @DataSize eq 0
	mov	dx,filespec
else
	lds	dx,filespec
endif
	mov	ax,4e00H
	int	21H                     ; DOS 2+ - FINDFIRST - FIND FIRST MATCHING FILE
	jnc	L$3			
	xor	ax,ax
	jmp	L$5
L$3:
if @DataSize eq 0
	mov	di,attribute
else
	les	di,attribute
endif
	lds	si,dword ptr cs:DTA_ofs
	xor	ah,ah
	mov	al,15H[si]    		; file attribute
	stosw            		; al => attribute
	add	si,1eH      		; file name.ext
	cld
if @DataSize eq 0
	mov	di,filename
else
	les	di,filename
endif
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
