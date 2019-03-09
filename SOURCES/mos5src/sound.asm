.model small, C

.code
	public	sound
	public	nosound
	public	readtimer

;void sound(unsigned frequency)
frequency	equ [bp+4]
sound	proc
	push	bp
	mov	bp,sp
	mov     bx,  frequency
	mov     ax,  34DDh
	mov     dx,  0012h
	cmp     dx,  bx
	jnb     stop
	div     bx
	mov     bx,  ax
	in      al,  61h
	test    al,  3
	jne     j1
	or      al,  3
	out     61h, al
	mov     al,  0B6h
	out     43h, al
j1:
	mov     al,  bl
	out     42h, al
	mov     al,  bh
	out     42h, al
stop:
	pop	bp
	ret
sound	endp

;void nosound(void)
nosound	proc
	in      al,61H
	and     al, 0fcH
	out     61H, al
	ret
nosound endp

;Name            readtimer - read the complemented value of timer 0
;
;Description     Obtain the complement of the value in timer 0.  The
;                complement is used so that the timer will appear to
;                count up rather than down.  The value returned will
;                range from 0 to 0xffff.
;
;Return value    The complement of the value in timer 0.

readtimer	proc near	
	pushf                   ; /* Save interrupt flag                       */
	cli                     ; /* Disable interrupts                        */
	mov  al,0h              ; /* Latch timer 0                             */
	out  43h,al             ;
	jmp  $+2                ; /* Waste some time */
	in   al,40h             ; /* Counter --> bx                            */
	mov  bl,al              ; /* LSB in BL                                 */
	jmp  $+2                ; /* Waste some time */
	in   al,40h             ;
	mov  bh,al              ; /* MSB in BH                                 */
	not  bx                 ; /* Need ascending counter                    */
	popf             	; /* Restore interrupt flag                    */
	ret
readtimer	endp

end
