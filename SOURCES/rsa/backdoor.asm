ifdef _LARGE_
.model large, C
else
.model small, C
endif

.code
	PUBLIC	back_door_exec

;void  back_door_exec(char *command)
back_door_exec	proc
if @DataSize eq 0
buf	equ	[bp+4]
else
buf	equ	[bp+6]
endif
	push	bp
	mov	bp,sp
	push	ds
	push	es
	push	si
	push	di
	mov	ax,cs
	mov	es,ax
	lea	di,local_buf
if @DataSize eq 0
	mov	si,buf
else
	lds	si,buf
endif
	xor	dx,dx
L$1:
	lodsb
	cmp	al,0
	je	L$2
	stosb
	inc	dx
	jmp	L$1
L$2:
	mov	al,0dH
	stosb
	xor	al,al
	stosb
	mov	cs:local_buf_length,dl
	mov	ax,cs
	mov	ds,ax
	mov	si,offset cs:local_buf_length
	mov	cs:local_sp,sp
	mov	cs:local_ss,ss
	int	2eH      			; DOS 2+ - PASS COMMAND TO COMMAND INTERPRETER FOR EXECUTION
	mov	sp,cs:local_sp
	mov	ss,cs:local_ss
	pop	di
	pop	si
	pop	es
	pop	ds
	pop	bp
	ret
back_door_exec	endp

local_buf_length	db ?
local_buf		db 127 dup(0)
local_sp		dw ?
local_ss		dw ?
	END
