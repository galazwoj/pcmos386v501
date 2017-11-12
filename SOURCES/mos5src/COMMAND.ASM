;===============================================================;
;					                        ;          
;			COMMAND	                        	;          
;					                        ;
;===============================================================;         

seg_a		segment	byte public 'CODE'
		assume	cs:seg_a, ds:seg_a

		org	100h

COMMAND		proc	far
start:
		mov	sp, offset stack_start
		push	es
		mov	ah,34h
		int	21h			; DOS Services  ah=function 34h
						;  get DOS INDOS flag ptr es:bx
		sub	bx,2D9h
		mov	ax,es:data_2[bx]
		pop	es
		xor	bx,bx			; Zero register
		push	ax
		push	bx
		retf				; Return far
		nop

		db	84 dup ('stack')
data_2		label	word
		db	16 dup ('stack')
stack_start	label byte
COMMAND		endp

seg_a		ends

		end	start
