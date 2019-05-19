ifdef _LARGE_
.model large, C
else
.model small, C
endif


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
		db	0BAh, '(A)bort (R)etry (I)gnore (F)ail ', 0BAh
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
	pop	di
	add	di,ERROR_SCREEN_OFFSET
	pop	cx
	loop	L$51
	; save cursor pos
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
ifndef	ORIGINAL_CODE
	mov	dl,36H	
else
	mov	dl,35H	
endif
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

comment $
source:	http://www.ousob.com/ng/asm/ng641fc.php
INT 24h (36)             Critical-Error Handler Address

    Contains the address to which control is passed in response to a
    "critical" (usually hardware) error. When a program is executed, DOS
    copies this address into offset 12h through 15h of the Program Segment
    Prefix.

    When the critical error handling routine is invoked, the following
    diagnostic information is available:

     1.  Bit 7 of AH is clear if the error is related to a disk operation.
         If bit 7 of AH is set, it usually means the error is not a disk
         error (although an error in a disk's FAT can still result in bit
         7 of AH being set).

     2.  If Bit 7 of AH is clear, AL returns the disk drive ID number
         (0=A, 1=B, etc.), and bits 0 through 2 of AH provide further
         information, as follows:

               Bit 2 1 0
                   . . 0     Read error
                   . . 1     Write error
                   0 0 .     Error involving DOS system files
                   0 1 .     Error involving the FAT

     3.  BP:SI point to a device header control block.

     4.  The low-order byte of DI provides the following information (the
         high-order byte of DI is undefined):

              00h      Write-protect error
              01h      Invalid drive number
              02h      Drive not ready
              03h      Invalid command
              04h      CRC error
              05h      Bad request structure length
              06h      Seek error
              07h      Unknown medium; disk format not recognized
              08h      Sector not found
              09h      Printer out of paper
              0Ah      Write error
              0Bh      Read error
              0Ch      General, nonspecific error

     5.  The stack contains the complete register set of the program that
         issued the DOS function call that ended in the critical error. To
         retrieve this information, first perform the following
         instructions:

              PUSH     BP
              MOV      BP,SP

         The stack will then be structured as follows:

          BP offset     Stack contents
             00h        BP value that you PUSHed
             02h        IP:CS of DOS service invoking critical error handler
             06h        Flags of DOS service invoking critical error handler
             08h        AX of program invoking DOS service
             0Ah        BX of program invoking DOS service
             0Ch        CX of program invoking DOS service
             0Eh        DX of program invoking DOS service
             10h        SI of program invoking DOS service
             12h        DI of program invoking DOS service
             14h        BP of program invoking DOS service
             16h        DS of program invoking DOS service
             18h        ES of program invoking DOS service
             1Ah        IP:CS of program invoking DOS service
             1Eh        Flags of program invoking DOS service

    In reporting the condition to your program's user, do not use DOS
    function calls above 0Ch. Doing so will destroy DOS's internal stack
    and result in unpredictable behavior.

    On exit from your error-handling routine, DOS will look for an return
    code in AL and behave as follows:

              AL        DOS action
              0         Ignore the error
              1         Retry the operation
              2         Abort the program (issue INT 23h)
	      3         Fail the operation	
        $
	END
		