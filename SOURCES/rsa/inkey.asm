ifdef _LARGE_
.model large, C
else
.model small, C
endif

.code

	PUBLIC	inkey
;int inkey(char * character, char * ext_character)
;0 if no character available
;1 if character read

inkey	proc
if @DataSize eq 0
character	equ	[bp+4]
ext_character	equ	[bp+6]
else
character	equ	[bp+6]
ext_character	equ	[bp+0ah]
endif
	push	bp
	mov	bp,sp
	push	di
	mov	ah,6
	mov	dl,0ffH			; kbhit
	int	21H
	jnz	L$1    			
	xor	ax,ax                   ; no key available
	jmp	L$3            		
L$1:
if @DataSize eq 0
	mov	di,character
	mov	[di],al
else
	les	di,character
	stosb
endif
	cmp	al,0                	; extended key
	jne	L$2
	mov	ah,6
	mov	dl,0ffH			; kbhit	
	int	21H
if @DataSize eq 0
	mov	di,ext_character
	mov	[di],al
else
	les	di,ext_character
	stosb
endif
L$2:
	mov	ax,1
L$3:
	pop	di
	pop	bp
	ret
inkey	endp
	END
