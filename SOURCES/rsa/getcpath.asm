.model small, C
.code
	PUBLIC	get_current_path

; void get_current_path(char *path);
get_current_path proc
path	equ	[bp+4]
	push	bp
	mov	bp,sp
	push	si
	mov	si,path
	mov	ah,19H
	int	21H			; DOS 1+ - GET CURRENT DEFAULT DRIVE
	mov	dl,al
	add	al,41H			; convert to a letter
	mov	byte ptr [si],al  	; a
	mov	byte ptr 1[si],3aH     	; :
	mov	byte ptr 2[si],5cH     	; \
	add	si,3
	mov	ah,47H
	inc	dl
	int	21H			; DOS 2+ - CWD - GET CURRENT DIRECTORY
	pop	si
	pop	bp
	ret
get_current_path endp
	END
