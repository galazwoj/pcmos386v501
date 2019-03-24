.model small, C
.code
	PUBLIC	change_video_attribute

;void change_video_attribute(void far *pixel, int attribute, int count);
change_video_attribute proc
pixel_seg	equ [bp+4]
pixel_ofs     	equ [bp+6]
attribute	equ [bp+8]
count		equ [bp+0ah]
	push	bp
	mov	bp,sp
	push	es
	push	di
	mov	es,pixel_seg
	mov	di,pixel_ofs
	inc	di          		; points to attribute now
	int	11H			; BIOS - GET EQUIPMENT LIST
	and	ax,30H
	cmp	ax,30H
	je	L$3			; mono
	mov	dx,3daH
L$1:					; some delay toavoid flicker
	in	al,dx
	test	al,8
	jne	L$1
L$2:
	in	al,dx
	test	al,8
	je	L$2
L$3:
	mov	al,attribute
	mov	cx,count
L$4:
	stosb
	inc	di
	loop	L$4
	pop	di
	pop	es
	pop	bp
	ret
change_video_attribute endp
	END
