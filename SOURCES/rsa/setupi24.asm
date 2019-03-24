.model small, C

ERROR_VIDEO_OFFSET 	equ 5ccH
ERROR_SCREEN_OFFSET	equ 0a0H
INTR24_MSG_LENGTH	equ 22h
INTR24_MSG_ROWS		equ 5

.code                                   
	PUBLIC	setup_i24

itr24_busy	db	0
int24_msg 	db	0D6h, 12 dup (0C4h), ' Error ', 13 dup (0C4h), 0B7h	;upper_frame 				
err_place	db	0BAh, 32 dup (20h), 0BAh			
		db	0BAh, 32 dup (20h), 0BAh
ifndef	ORIGINAL_CODE
		db	0BAh, ' A)bort R)etry I)gnore F)ail:  ', 0BAh
else
		db	0BAh, ' (A)bort, (R)etry or (I)gnore:  ', 0BAh
endif
		db	0D3h, 32 dup (0C4h), 0BDh				;lower_frame
err_msgs	db	0BAh, '       Write protect error      ', 0BAh		;00H
		db	0BAh, '           Unknown unit         ', 0BAh          ;01H
		db	0BAh, '         Drive not ready        ', 0BAh          ;02H
		db	0BAh, '      Unknown device command    ', 0BAh          ;03H
		db	0BAh, '   Disk data error. (Bad CRC)   ', 0BAh          ;04H
		db	0BAh, '  Bad request structure length  ', 0BAh          ;05H
		db	0BAh, '         Disk seek error        ', 0BAh          ;06H
		db	0BAh, '        Unknown media type      ', 0BAh          ;07H
		db	0BAh, '      Disk sector not found     ', 0BAh          ;08H
		db	0BAh, '      Printer out of paper      ', 0BAh          ;09H
		db	0BAh, '         Disk write fault       ', 0BAh          ;0AH
		db	0BAh, '         Disk read fault        ', 0BAh          ;0BH
		db	0BAh, '         General failure        ', 0BAh          ;0CH
ifndef	ORIGINAL_CODE
		db	0BAh, '        Sharing violation       ', 0BAh          ;0DH
		db	0BAh, '         Lock violation         ', 0BAh          ;0EH
		db	0BAh, '       Invalid disk change      ', 0BAh          ;0FH
		db	0BAh, '         FCB unavailable        ', 0BAh          ;10H
		db	0BAh, '      Sharing buffer overflow   ', 0BAh          ;11H
		db	0BAh, '        Code page mismatch      ', 0BAh          ;12H
		db	0BAh, '          Out of input          ', 0BAh          ;13H
		db	0BAh, '     Insufficient disk space    ', 0BAh          ;14H
		db	0BAh, '        Undefined error         ', 0BAh          ;15H
endif

cursor_position	dw	?					
video_segment	dw	0					
video_buffer	dw	INTR24_MSG_LENGTH * INTR24_MSG_ROWS dup (?)

isr_24h	proc far
	pushf
	test	cs:itr24_busy,0ffH
	je	intr24_go
	jmp	intr24_leave
intr24_go:
	mov	cs:itr24_busy,0ffH
	cli
	cld
	push	bx
	push	cx
	push	dx
	push	ds
	push	es
	push	si
	push	di
	push	bp
	mov	ax,@code
	mov	ds,ax
	mov	es,ax
	mov	ax,di         				;di = error number
ifndef	ORIGINAL_CODE
	cmp	ax,14h
	jng	di_ok
	mov	ax,15h
di_ok:
endif
	mov	bx,INTR24_MSG_LENGTH		
	mul	bx
	add	ax,offset err_msgs
	;copy error msg
	mov	si,ax
	mov	di,offset err_place
	mov	cx,INTR24_MSG_LENGTH
rep 	movsb
	test	word ptr cs:video_segment,0ffffH
	jne	L$49
	; select video seg
	mov	word ptr cs:video_segment,0b800H
	int	11H					; Put equipment bits in ax
	and	ax,30H
	cmp	ax,30H
	jne	L$49
	mov	word ptr cs:video_segment,0b000H
	;sasve screen 
L$49:
	mov	ds,cs:video_segment
	mov	si,ERROR_VIDEO_OFFSET
	mov	di,offset video_buffer
	mov	cx,INTR24_MSG_ROWS
L$50:
	push	cx
	push	si
	mov	cx,INTR24_MSG_LENGTH
rep 	movsw
	pop	si
	add	si,ERROR_SCREEN_OFFSET
	pop	cx
	loop	L$50
	; display message onscreen
	mov	ax,@code
	mov	ds,ax
	mov	si,offset int24_msg
	mov	es,video_segment
	mov	di,ERROR_VIDEO_OFFSET	 
	mov	cx,INTR24_MSG_ROWS
	mov	al,7
L$51:
	push	cx
	push	di
	mov	cx,INTR24_MSG_LENGTH
L$52:
	movsb
	stosb
	loop	L$52
	; save cursor pos
	pop	di
	add	di,ERROR_SCREEN_OFFSET
	pop	cx
	loop	L$51
	mov	ah,3
	xor	bh,bh
	push	bp
	int	10H
	pop	bp
	mov	cursor_position,dx
L$53:
	; set cursor pos
	mov	ah,2
	xor	bh,bh
	mov	dh,0cH
	mov	dl,35H	
	push	bp
	int	10H
	pop	bp
	; kbdhit
	mov	ah,6
	mov	dl,0ffH
key_again:
	int	21H
	je	key_again	; special key pressed
	and	al,0dfH        	; uppercase letter
	cmp	al,'I'		; Ignore
	je	key_I
	cmp	al,'R'        	; Retry
	je	key_R
	cmp	al,'A'      	; Abort
	je	key_A
ifndef ORIGINAL_CODE
	cmp	al,'F'
	je	key_F	
endif
	jmp	L$53
	; Ignore scenario
key_I:
	xor	ax,ax
	jmp	L$58
	; Retry scenaro
key_R:
	mov	ax,1
	jmp	L$58
	; Abort scenario
key_A:
	mov	ax,2
ifndef	ORIGINAL_CODE
	jmp	L$58
	; Fail scenario
key_F:
	mov	ax,3
endif
	; Finalize
L$58:
	; set cursor pos
	push	ax
	mov	ah,2
	xor	bh,bh
	mov	dx,cursor_position
	push	bp
	int	10H
	pop	bp
	pop	ax
	mov	si,offset video_buffer
	mov	di,ERROR_VIDEO_OFFSET 
	mov	cx,INTR24_MSG_ROWS
L$59:
	push	cx
	push	di
	mov	cx,INTR24_MSG_LENGTH
rep 	movsw
	pop	di
	add	di,ERROR_SCREEN_OFFSET
	pop	cx
	loop	L$59
	pop	bp
	pop	di
	pop	si
	pop	es
	pop	ds
	pop	dx
	pop	cx
	pop	bx
	mov	cs:itr24_busy,0
intr24_leave:
	popf
	iret
isr_24h	endp
		
;void  	setup_i24(void);
setup_i24	proc
	push	bp
	mov	bp,sp
	push	ds
	mov	ax,@code
	mov	ds,ax
	lea	dx,isr_24h
	mov	ax,2524H
	int	21H    		; set int 24h routine
	pop	ds
	pop	bp
	ret
setup_i24	ENDP
	END
		