
PAGE  59,132

;===============================================================;
;					                        ;          
;			SFT                        		;          
;								;
; 05/11/2917	source code restored				;
;					                        ;
;===============================================================;         

seg_a		segment	byte public 'CODE'
		assume	cs:seg_a, ds:seg_a, es:seg_a

		org	100h

main		proc	far

start:
		jmp	real_start
SFT_ENTRY_SIZE	equ	3Bh
SFT_ENTRIES	equ	63h
sft_entry	struc
	sft_next_offset	dw 0
	sft_next_seg 	dw 0
	sft_files     	dw 0	
	placeholder	db (SFT_ENTRY_SIZE-6) dup(0)				
sft_entry	ends 

sft		sft_entry SFT_ENTRIES dup(<>)		

msg_info	db	'SFT Fake Version 1.00 (910624)', 0Dh,0Ah, '$'
msg_not_on_mos	db	'NOT on PC-MOS', 0Dh, 0Ah, '$'
res_area_size	dw 	offset sft
sft_offset	dw	offset sft	
		
real_start:
		mov	dx, offset msg_info		
		mov	ah,9
		int	21h			; DOS Services  ah=function 09h
						;  display char string at ds:dx
		call	is_pcmos
		jnc	short loc_2		
		mov	dx, offset msg_not_on_mos	
		mov	ah,9
		int	21h			; DOS Services  ah=function 09h
						;  display char string at ds:dx
		mov	ax,4C01h
		int	21h			; DOS Services  ah=function 4Ch
						;  terminate with al=return code
loc_2:
		call	get_sft
		call	set_sft
		mov	dx,cs:res_area_size
		int	27h			; Terminate & stay resident
						;  dx=offset last byte+1, cs=PSP
main		endp

get_sft		proc	near
		mov	cx,SFT_ENTRIES
		mov	di,offset sft
		push	cs
		pop	es

locloop_1:
		mov	sft_offset,di
		mov	es:[di.sft_next_offset],di
		add	word ptr es:[di.sft_next_offset],SFT_ENTRY_SIZE
		mov	es:[di.sft_next_seg],cs
		mov	word ptr es:[di.sft_files],1
		add	di,SFT_ENTRY_SIZE
		add	res_area_size,SFT_ENTRY_SIZE
		loop	locloop_1	
		retn
get_sft		endp

set_sft		proc	near
		mov	ah,52h
		int	21h			; DOS Services  ah=function 52h
						;  get DOS data table ptr es:bx
		mov	ax,es:[bx+4]		; dos sft offset
		mov	cx,es:[bx+6]          	; dos sft segment
		mov	di,sft_offset
		mov	cs:[di.sft_next_offset],ax		
		mov	cs:[di.sft_next_seg],cx
		mov	word ptr es:[bx+4],offset sft	;link to our sft, offset
		mov	es:[bx+6],cs			;link to our sft, segment
		retn
set_sft		endp

is_pcmos		proc	near
		mov	ah,30h			
		mov	bx,ax
		mov	cx,ax
		mov	dx,ax
		int	21h			; DOS Services  ah=function 30h
						;  get PC MOS version number ax
		push	ax
		mov	ah,30h			
		mov	bx,0FFFFh
		int	21h			; DOS Services  ah=function 30h
						;  get DOS version number ax
		pop	bx
		cmp	ax,bx
		je	short loc_3		
		clc				; PC MOS
		retn
loc_3:
		stc				; not PC MOS				
		retn
is_pcmos		endp

seg_a		ends
		end	start
