	page	255,132
;,fs
;******** $.
;,fe

	.model small,c

	.data
delayinitialized	dw 0
delaycnt		dd ?

	.code

	subttl nosound - turns off the speaker
	page
;======================================================================
;,fs
; nosound - turns off the speaker
;
; prototype: 
;
; void nosound(void);
;
; in:	
;
; out:	
;
;,fe
;======================================================================
public nosound
nosound proc 
	in      al, 61H
 	and     al, 0fcH
	out     61H, al
	ret
nosound endp

	subttl sound - outputs a sound of a specified frequency to the speaker
	page

;======================================================================
;,fs
; sound - outputs a sound of a specified frequency to the speaker
;
; prototype: 
;
; void sound(unsigned frequency);
;
; in:	frequency = sound of a specified frequency emitted to the speaker
;
; out:	
;
;,fe
;======================================================================
public sound
sound proc frequency:word
	mov     ax,  frequency
	or	ax,  ax
	jnz	m_sound
	call	nosound
	ret	                                                 
m_sound:          
	push	cx                         
	push	dx	
	mov	cx,  ax		   
	mov     ax,  3456h                 
	mov     dx,  0012h                 	                   		                   
	div     cx                         
	mov     cx,  ax                    
	in      al,  61h                   
	test    al,  3                     
	jne     m_soundnext                     
	or      al,  3                     
	out    	61h, al                    
	mov     al,  0B6h                  
	out    	43h, al                    
m_soundnext:                                    
	mov  	al,  cl                    
	out     42h, al                    
	mov     al,  ch                    
	out     42h, al                    
m_exit:                                                                 
	pop	dx                           
	pop	cx                           
	ret                                  
sound endp                                   

	subttl delay - delay rotines
	page

;======================================================================
; delayloop - loop over
;
; in:   es:di = $40:$6c
;    	bx    = value of [es:dx] before the call
;	dx:ax = counter 
;
; out:	
;
;======================================================================

Delayloop proc near
LDelayLoop1:
	sub     ax, 1
       	sbb     dx, 0
        jc      LDelayLoop2
        cmp     bx, word ptr es:[di]
        je      LDelayLoop1
LDelayLoop2:
Delayloop  endp

;======================================================================
; div32 - divide 32 bit value by 16 bit value
;
; in:   dx:ax	= x
;	cx	= y
;
; out:	dx:ax	x/y quotient
;	cx 	x/y remainder
;
;======================================================================
div32	proc near	
	push	si
	push	di
	mov	si, ax
	mov	ax, dx
	xor	dx, dx
	div	cx
	mov	di, ax
	mov	ax, si
	div	cx
	mov	cx, dx
	mov	dx, di
	pop	di
	pop	si
	ret
div32	endp

;======================================================================
; initdelay - initialize delay
;
; in:   es:di = 40h:6ch
;    	bx    = value of [es:dx] before the call
;	dx:ax = counter 
;
; out:	
;
;======================================================================

initdelay proc
	push	bx
	pop	cx
	push	dx
	push	di
	push	es
        sti
        mov     ax, 40h
        mov     es, ax
        mov     di, 6ch
        mov     bx, es:[di]
LInitDel1:
        cmp     bx, es:[di]
        je      LInitDel1
        mov     bx, es:[di]
        mov     ax, 0FFFFh
        mov     dx, 0FFFFh
        call    near ptr DelayLoop
;       ax = [DelayCnt]
;       dx = [DelayCnt + 2]
;  	DelayCnt := DelayCnt div $55
	mov	cx, 55h
	call	near ptr div32
;  	DelayCnt := -DelayCnt 
	not	dx
	not	ax
	add	ax, 1
	adc	dx, 0
        mov     word ptr [DelayCnt], ax
        mov     word ptr [DelayCnt + 2], dx
	pop	es
	pop	di
	pop	dx
	pop	cx
	pop	bx
	ret
initdelay endp

;======================================================================
;,fs
; delay - wait for specified period
; The current thread of execution is suspended for the specified
; number of milliseconds.
;
; prototype: 
;
; void delay(unsigned milliseconds);
;
; in:	miliseconds = number of miliseconds delayed
;
; out:	
;
;,fe
;======================================================================
public delay
delay proc miliseconds:word
	cmp	delayinitialized, 1
	je	LSkipInitDelay
	call	initdelay
	mov	delayinitialized, 1
LSkipInitDelay:
	push	bx
	push	si
	push	di
	push	es
        mov     ax, 40h                              
        mov     es, ax                               
        xor     di, di                               
                                                     
        mov     cx, miliseconds                      
        test    cx, cx                               
        jz      LDelay2                              
        mov     si, word ptr [DelayCnt + 2]                   
        mov     bx, es:[di]                          
LDelay1:                                             
        mov     ax, word ptr [DelayCnt]                       
        mov     dx, si                               
        call    DelayLoop                            
        loop    LDelay1                              
LDelay2:                                             
	pop	es
	pop	di
	pop	si
	pop	bx
	ret	
delay endp

	end
