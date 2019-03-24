.model small, C
.code
	PUBLIC	get_file_date
	PUBLIC	set_file_date

lastdate	dw 0
lasttime	dw 0

filename	equ	[bp+4]
datetime	equ	[bp+6]

;int get_file_date(char *filename, struct DATETIME *datetime);
get_file_date	proc
	push	bp
	mov	bp,sp
	push	ds
	push	si
	mov	ax,3d00H
	mov	dx,filename
	int	21H			; DOS 2+ - OPEN - OPEN EXISTING FILE
	jc	L$3
	mov	bx,ax
	mov	ax,5700H				
	int	21H                     ; DOS 2+ - GET FILE'S LAST-WRITTEN DATE AND TIME
	mov	cs:lasttime,cx
	mov	cs:lastdate,dx
	mov	ax,3e00H
	int	21H                 	; DOS 2+ - CLOSE - CLOSE FILE
	mov	si,datetime
	mov	ax,cs:lastdate      	
	and	ax,0fe00H
	mov	cx,7
	rol	ax,cl
	add	ax,7bcH             	
	mov	[si],ax        ; years
	add	si,2
	mov	ax,cs:lastdate
	and	ax,1e0H
	mov	cx,5
	shr	ax,cl
	mov	[si],ax        ; months	
	add	si,2
	mov	ax,cs:lastdate         	
	and	ax,1fH
	mov	[si],ax        ; days
	add	si,2
	mov	ax,cs:lasttime            	
	and	ax,0f800H
	mov	cx,5
	rol	ax,cl
	mov	[si],ax        ; hours	
	add	si,2
	mov	ax,cs:lasttime           	
	and	ax,7e0H
	mov	cx,5
	shr	ax,cl
	mov	[si],ax        ; minutes
	add	si,2
	mov	ax,cs:lasttime		
	and	ax,1fH
	shl	ax,1
	mov	[si],ax        ; seconds
	xor	ax,ax
L$3:
	pop	si
	pop	ds
	pop	bp
	ret
get_file_date	endp

;int set_file_date(char *filename, struct DATETIME datetime);
set_file_date	proc
	push	bp
	mov	bp,sp
	push	ds
	push	si
	mov	si,datetime
	xor	ax,ax
	mov	bx,[si]
	sub	bx,7bcH
	mov	cx,7
	ror	bx,cl
	or	ax,bx
	mov	bx,2[si]
	mov	cx,5
	rol	bx,cl
	or	ax,bx
	or	ax,4[si]
	mov	cs:lastdate,ax
	xor	ax,ax
	mov	bx,6[si]
	mov	cx,5
	ror	bx,cl
	or	ax,bx
	mov	bx,8[si]
	mov	cx,5
	shl	bx,cl
	or	ax,bx
	mov	bx,0aH[si]
	shr	bx,1
	or	ax,bx
	mov	cs:lasttime,ax
	mov	ax,3d02H
	mov	dx,filename
	int	21H          		; DOS 2+ - OPEN - OPEN EXISTING FILE
	jb	L$4
	mov	bx,ax
	mov	ax,5701H
	mov	cx,cs:lasttime
	mov	dx,cs:lastdate
	int	21H			; DOS 2+ - SET FILE'S LAST-WRITTEN DATE AND TIME
	mov	ax,3e00H
	int	21H             	; DOS 2+ - CLOSE - CLOSE FILE
	xor	ax,ax
L$4:
	pop	si
	pop	ds
	pop	bp
	ret
set_file_date	endp
	END
