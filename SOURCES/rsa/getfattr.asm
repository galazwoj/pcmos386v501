.model small, C
.code
	PUBLIC	get_file_attributes

;int get_file_attributes(char *filename, int *attributes);
get_file_attributes proc
filename 	equ	[bp+4]
attributes      equ	[bp+6]
	push	bp
	mov	bp,sp
	mov	dx,filename
	mov	ax,4300H
	int	21H		; DOS 2+ - GET FILE ATTRIBUTES
	jc	L$1
	mov	bx,attributes
	mov	word ptr [bx],cx
	xor	ax,ax
L$1:
	pop	bp
	ret
get_file_attributes endp
	END
