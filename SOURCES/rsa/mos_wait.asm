ifdef _LARGE_
.model large, C
else
.model small, C
endif

.code
	PUBLIC	MOS_wait

; int MOS_wait(int timer_ticks);
; function returns nonzero on error
MOS_wait proc
if @DataSize eq 0
timer_ticks	equ	[bp+4]
else
timer_ticks	equ	[bp+6]
endif
	push	bp
	mov	bp,sp
	mov	ah,7                  	; PC-MOS/386 v3.0+ - WAIT FOR EVENT
	mov	al,3      		; event to monitor - keystroke timeout
	mov	bx,timer_ticks		; number of timer ticks until timeout if AL bit 1 set
	int	0d4H
	jc	L$1
	xor	ax,ax
L$1:
	pop	bp
	ret
MOS_wait endp
	END
