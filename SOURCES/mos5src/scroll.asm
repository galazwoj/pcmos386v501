.model  small, C

.code
	public	scroll

;extern void scroll(int direction, int x1, int y1, int x3, int y2, int numlines, int attribute);
direction	equ [bp+4 ]
x1              equ [bp+6 ]
y1              equ [bp+8 ]
x2              equ [bp+10]
y2              equ [bp+12]
numlines        equ [bp+14]
attribute       equ [bp+16]
scroll	proc
	push	bp	
	mov	bp, sp
	push	ds
	mov	ah, direction
	mov	cl, x1
	mov	ch, y1
	mov	dl, x2
	mov	dh, y2
	mov	al, numlines
	cmp	ch, dh
	jne	l1
	xor	al, al
l1:	mov	bh, attribute
	int	10h
	pop	ds
	pop	bp
	ret
scroll	endp

end
