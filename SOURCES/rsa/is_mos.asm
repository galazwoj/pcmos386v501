ifdef _LARGE_
.model large, C
else
.model small, C
endif

.code
	PUBLIC	is_MOS

;int  	is_MOS(void);
; system is running PC_MOS if return > 0
is_MOS	proc
	mov	ah,30H
	xor	bx,bx
	int	21H		; get DOS version
	push	ax
	mov	ah,30H
	mov	bx,ax
	mov	cx,ax
	mov	dx,ax
	int	21H     	;PC-MOS/386 v3.0 - INSTALLATION CHECK/GET VERSION
	pop	bx
	cmp	ax,bx
	je	L$1
	xchg	al,ah
	ret
L$1:
	xor	ax,ax
	ret
is_MOS	endp
	END
