ifdef _LARGE_
.model large, C
else
.model small, C
endif

.code
	PUBLIC	set_file_attributes

;int set_file_attributes(char *filename, int attributes);
set_file_attributes proc
if @DataSize eq 0
filename 	equ	[bp+4]
attributes      equ	[bp+6]
else
filename 	equ	[bp+6]
attributes      equ	[bp+0ah]
endif
	push	bp
	mov	bp,sp
if @DataSize eq 0
	mov	dx,filename
else
	push	ds
	lds	dx,filename
endif
	mov	ax,4301H
	mov	cx,attributes
	int	21H		; DOS 2+ - CHMOD - SET FILE ATTRIBUTES
	jc	L$1
	xor	ax,ax
L$1:
if @DataSize gt 0
	pop	ds
endif
	pop	bp
	ret
set_file_attributes endp
	END
