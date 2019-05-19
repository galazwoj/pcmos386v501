ifdef _LARGE_
.model large, C
else
.model small, C
endif

.code
.386	

PUBLIC	get_CPU_type

;int  	get_CPU_type(void); 	
;#define CPU_8086	 0
;#define CPU_80186       1
;#define CPU_80286       2
;#define CPU_80386       3
;#define CPU_80486       4

get_CPU_type proc
	pushf	
	xor	ax,ax
	push	ax   
	popf
	pushf
	pop	ax
	and	ax,0f000H
	xor	bl,bl
	cmp	ax,0f000H
	je	L$1
	mov	bl,3
	mov	ax,0f000H
	push	ax
	popf
	pushf
	pop	ax
	and	ax,0f000H
	jne	L$2
	dec	bl
	push	sp
	pop	ax
	cmp	ax,sp
	je	L$2
	xor	bl,bl
L$1:
	mov	cx,21H
	mov	al,0ffH
	shl	al,cl
	je	L$2
	mov	bl,1
L$2:
	popf
	cmp	bl,3
	jne	L$3
	mov	edx,esp
	and	esp,0fffffffcH
	pushfd
	pop	eax
	mov	ecx,eax
	xor	eax,40000H
	push	eax
	popfd
	pushfd
	pop	eax
	xor	eax,40000H
	shr	eax,12H
	and	eax,1
	push	ecx
	popfd
	mov	esp,edx
	or	al,al
	jne	L$3
	inc	bl
L$3:
	xor	ah,ah
	mov	al,bl
	ret
get_CPU_type endp
	END
	