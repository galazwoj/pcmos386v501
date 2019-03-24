.model small, C
.code
	PUBLIC	set_file_attributes

;int set_file_attributes(char *filename, int attributes);
set_file_attributes proc
filename 	equ	[bp+4]
attributes      equ	[bp+6]
	push	bp
	mov	bp,sp
	mov	dx,filename
	mov	ax,4301H
	mov	cx,attributes
	int	21H		; DOS 2+ - CHMOD - SET FILE ATTRIBUTES
	jb	L$1
	xor	ax,ax
L$1:
	pop	bp
	ret
set_file_attributes endp
	END
