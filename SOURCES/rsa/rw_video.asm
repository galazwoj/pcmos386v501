.model small, C
.code
	PUBLIC	_$read_video_region
	PUBLIC	_$write_video_region

video_segment	dw	0

column1		equ	[bp+4]
row1		equ	[bp+6]
column2		equ	[bp+8]
row2		equ	[bp+0ah]
buf		equ	[bp+0ch]
video_mode	equ	[bp+0eh]

;void	_$read_video_region (int column1, int row1, int column2, int row2, void * buf, int video_mode);
_$read_video_region proc
	push	bp
	mov	bp,sp
	push	ds
	push	es
	push	si
	push	di
	cld
	call	near ptr set_video_segment
	mov	cs:video_segment,ax
	mov	ds,ax
	mov	ax,column1
	dec	ax
	mov	bx,ax
	xchg	al,ah
	shr	ax,1
	shl	bx,1
	shl	bx,1
	shl	bx,1
	shl	bx,1
	shl	bx,1
	add	ax,bx
	mov	bx,row1
	dec	bx
	shl	bx,1
	add	bx,ax
	mov	di,buf
	mov	cx,video_mode
	mov	dx,3daH
L$2:
	push	cx
	mov	si,bx
	mov	cx,column2
	cmp	cs:video_segment,0b000H
	je	L$6
	test	byte ptr video_mode,0ffH
	je	L$6
	shl	cx,1
L$3:
	cli
L$4:
	in	al,dx
	test	al,1
	jne	L$4
L$5:
	in	al,dx
	test	al,1
	je	L$5
	movsb
	sti
	loop	L$3
	jmp	L$7
L$6:
rep 	movsw
L$7:
	add	bx,0a0H
	pop	cx
	loop	L$2
	pop	di
	pop	si
	pop	es
	pop	ds
	pop	bp
	ret
_$read_video_region endp

;void	_$write_video_region(int column1, int row1, int column2, int row2, void * buf, int video_mode);
_$write_video_region proc
	push	bp
	mov	bp,sp
	push	ds
	push	es
	push	si
	push	di
	cld
	call	near ptr set_video_segment
	mov	cs:video_segment,ax
	mov	es,ax
	mov	ax,column1
	dec	ax
	mov	bx,ax
	xchg	al,ah
	shr	ax,1
	shl	bx,1
	shl	bx,1
	shl	bx,1
	shl	bx,1
	shl	bx,1
	add	ax,bx
	mov	bx,row1
	dec	bx
	shl	bx,1
	add	bx,ax
	mov	si,buf
	mov	cx,video_mode
	mov	dx,3daH
L$8:
	push	cx
	mov	di,bx
	mov	cx,column2
	cmp	cs:video_segment,0b000H
	je	L$12
	test	byte ptr video_mode,0ffH
	je	L$12
	shl	cx,1
L$9:
	cli
L$10:
	in	al,dx
	test	al,1
	jne	L$10
L$11:
	in	al,dx
	test	al,1
	je	L$11
	movsb
	sti
	loop	L$9
	jmp	L$13
L$12:
	rep movsw
L$13:
	add	bx,0a0H
	pop	cx
	loop	L$8
	pop	di
	pop	si
	pop	es
	pop	ds
	pop	bp
	ret
_$write_video_region endp

set_video_segment proc
	push	bx
	mov	bx,0b800H
	int	11H
	and	ax,30H
	cmp	ax,30H
	jne	L$15
	mov	bx,0b000H
L$15:
	xchg	ax,bx
	pop	bx
	ret
set_video_segment endp
	END
