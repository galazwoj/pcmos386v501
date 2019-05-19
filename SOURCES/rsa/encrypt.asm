ifdef _LARGE_
.model large, C
else
.model small, C
endif

.code
	PUBLIC	encrypt

;void encrypt(char *buf, int key);
encrypt proc
if @DataSize eq 0
buf	equ	[bp+4]
key	equ	[bp+6]
else
buf	equ	[bp+6]
key	equ	[bp+0ah]
endif
	push	bp
	mov	bp,sp
	push	si
if @DataSize eq 0
	mov	si,buf
else
	push	ds
	lds	si,dword ptr buf
endif
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
if @DataSize gt 0
	pop	ds
endif
	pop	si
	pop	bp
	ret     
encrypt endp
	END
