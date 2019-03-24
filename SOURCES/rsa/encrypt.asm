.model small, C
.code
	PUBLIC	encrypt

;void encrypt(char *buf, int key);
encrypt proc
buf	equ	[bp+4]
key	equ	[bp+6]
	push	bp
	mov	bp,sp
	push	si
	mov	si,buf
	mov	cx,key
	and	cx,7
	cmp	cx,0
	jne	L$1
	mov	cx,1
L$1:
	cmp	byte ptr [si],0
	je	L$2
	rol	byte ptr [si],cl
	inc	si
	jmp	L$1
L$2:
	pop	si
	pop	bp
	ret     
encrypt endp
	END
