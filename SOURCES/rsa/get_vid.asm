.model small, C
.code
	PUBLIC	get_video_type

;#define VIDEO_TYPE_VGA  0
;#define VIDEO_TYPE_EGA  1
;#define VIDEO_TYPE_CGA  2
;#define VIDEO_TYPE_HGC  3
;#define VIDEO_TYPE_NONE 4

;int get_video_type(void)
get_video_type proc
	push	bp
	push	es
	push	si
	mov	ax,1a00H		; VIDEO - GET DISPLAY COMBINATION CODE (PS,VGA/MCGA)
	int	10H
	xor	ah,ah
	cmp	al,1aH
	jne	L$1     		; function not supported
	xor	ax,ax                 	; 0 = VGA
	jmp	L$6
L$1:				
	mov	ah,12H
	mov	bl,10H
	int	10H        		; VIDEO - ALTERNATE FUNCTION SELECT (PS, EGA, VGA, MCGA) - GET EGA INFO
	mov	ax,1
	cmp	bl,10H
	jne	L$6			; 1 = EGA or better
	mov	ax,40H     			
	mov	es,ax
	mov	ax,word ptr es:[63H]	; cga port 
	and	ax,0ff0H
	cmp	ax,3d0H  		
	jne	L$2                    	; no CGA
	mov	ax,2                 	; 2 = CGA
	jmp	L$6                	
L$2:                                      	
	mov	dx,3baH 		; CRT status register MDA  / Hercules	
	xor	bx,bx
	xor	ah,ah
	mov	si,word ptr es:[6cH] 	; time tick counter
L$3:
	in	al,dx
	and	al,80H
	or	ah,al
	cmp	si,word ptr es:[6cH]
	je	L$3
	mov	si,6cH
	inc	bx
	cmp	bx,3
	je	L$4
	jmp	L$3			; loop three tick times 
L$4:
	cmp	ah,0
	jne	L$5
	mov	ax,3       		; 3 = MDA
	jmp	L$6
L$5:
	mov	ax,4    		; 4 = unknown
L$6:
	pop	si
	pop	es
	pop	bp
	ret
get_video_type endp
	END
