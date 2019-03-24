.model small, C
.code

	PUBLIC	inkey

;int inkey(char * character, char * ext_character)
;0 if no character available
;1 if character read
inkey	proc
character	equ	[bp+4]
ext_character	equ	[bp+6]
	push	bp
	mov	bp,sp
	push	di
	mov	ah,6
	mov	dl,0ffH			; kbhit
	int	21H
	jne	L$1    			; no key available
	xor	ax,ax
	jmp	L$3            		
L$1:
	mov	di,character
	mov	byte ptr [di],al
	cmp	al,0                	; extended key
	jne	L$2
	mov	ah,6
	mov	dl,0ffH			; kbhit	
	int	21H
	mov	di,ext_character
	mov	byte ptr [di],al
L$2:
	mov	ax,1
L$3:
	pop	di
	pop	bp
	ret
inkey	endp
	END
