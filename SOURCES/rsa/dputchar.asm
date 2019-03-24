.model small, C
.code
	PUBLIC	dputchar

cursor_pos	dw 0
video_segment	dw 0

;void dputchar(int character);
dputchar proc
character	equ	[bp+4]
	push	bp
	mov	bp,sp
	push	es
	push	di
; check if color or mono display
	test	cs:video_segment,0ffffH
	jne	L$4
	int	11H
	and	ax,30H
	cmp	ax,30H
	jne	L$3
	mov	cs:video_segment,0b000H
	jmp	L$4
L$3:
	mov	cs:video_segment,0b800H
L$4:
	mov	ah,3
	xor	bh,bh
	push	bp
	int	10H		; VIDEO - GET CURSOR POSITION AND SIZE
	pop	bp
	mov	cs:cursor_pos,dx
	mov	es,cs:video_segment
	xor	di,di
	xor	cx,cx
	mov	ax,cs:cursor_pos
	xchg	al,ah
	xor	ah,ah
	mov	bx,ax
	xchg	al,ah
	shr	ax,1
	xchg	bl,bh
	shr	bx,1
	shr	bx,1
	shr	bx,1
	add	ax,bx
	mov	bx,cs:cursor_pos
	xor	bh,bh
	shl	bx,1
	add	ax,bx
	add	di,ax
	mov	al,character
	cmp	al,8
	jne	L$8
	cmp	cs:video_segment,0b000H
	je	L$7
	mov	dx,3daH
	cli
L$5:
	in	al,dx
	test	al,1
	jne	L$5
L$6:
	in	al,dx
	test	al,1
	je	L$6
L$7:
	mov	byte ptr es:-2[di],' '
	sti
	sub	di,2
	mov	dx,cs:cursor_pos
	dec	dl
	cmp	dl,0
	jae	L$12
	mov	dl,4fH
	dec	dh
	cmp	dh,0
	jae	L$12
	mov	dh,18H
	jmp	L$12
L$8:
	cmp	cs:video_segment,0b000H
	je	L$11
	mov	dx,3daH
	push	ax
	cli
L$9:
	in	al,dx
	test	al,1
	jne	L$9
L$10:
	in	al,dx
	test	al,1
	je	L$10
	pop	ax
L$11:
	stosb
	sti
	mov	dx,cs:cursor_pos
	inc	dl
	cmp	dl,4fH
	jbe	L$12
	xor	dl,dl
	inc	dh
	cmp	dh,18H
	jbe	L$12
	xor	dh,dh
L$12:
	mov	ah,2
	xor	bh,bh
	int	10H		; VIDEO - SET CURSOR POSITION
	pop	di
	pop	es
	pop	bp
	ret
dputchar endp
	END
