ifdef _LARGE_
.model large, C
else
.model small, C
endif

.code
	PUBLIC	bios_disk_reset
	PUBLIC	bios_disk_status
	PUBLIC	bios_disk_read
	PUBLIC	bios_disk_write

if @DataSize eq 0
drive	equ	[bp+4]
else
drive	equ	[bp+6]
endif

;int  	bios_disk_reset(int drive);
bios_disk_reset proc
	push	bp
	mov	bp,sp
	xor	ah,ah
	mov	dl,drive
	int	13H
	jc	L$1
	xor	ax,ax
	jmp	L$2
L$1:
	xor	al,al
	xchg	al,ah
L$2:
	pop	bp
	ret
bios_disk_reset endp	

;int 	bios_disk_status(int drive);  
bios_disk_status proc
	mov	ah,1
	mov	dl,drive
	int	13H
	xor	al,al
	xchg	al,ah
	ret
bios_disk_status endp

;int	bios_disk_read(int drive, int cylinder, int head, int sector, int num_of_sectors, char *buffer);
bios_disk_read	proc
	push	bp
	mov	bp,sp
if @DataSize gt 0
	push	es
endif
	mov	ah,2
	call	near ptr set_parameters
	int	13H
	jc	L$3
	xor	ax,ax
	jmp	L$4
L$3:
	xor	al,al
	xchg	al,ah
L$4:
if @DataSize gt 0
	pop	es
endif
	pop	bp
	ret
bios_disk_read	endp

;int	bios_disk_write(int drive, int cylinder, int head, int sector, int num_of_sectors, char *buffer);
bios_disk_write proc
	push	bp
	mov	bp,sp
if @DataSize gt 0
	push	es
endif
	mov	ah,3
	call	near ptr set_parameters
	int	13H
	jc	L$5
	xor	ax,ax
	jmp	L$6
L$5:
	xor	al,al
	xchg	al,ah
L$6:
if @DataSize gt 0
	pop	es
endif
	pop	bp
	ret
bios_disk_write endp

set_parameters proc	near
if @DataSize eq 0
drive		equ	[bp+4]
cylinder	equ     [bp+6]
head		equ   	[bp+8]
sector		equ	[bp+0ah]
num_of_sectors	equ     [bp+0ch]
buffer		equ   	[bp+0eh]
else
drive		equ	[bp+6]
cylinder	equ     [bp+8]
head		equ   	[bp+0ah]
sector		equ	[bp+0ch]
num_of_sectors	equ     [bp+0eh]
buffer		equ   	[bp+10h]
endif
	mov	al,num_of_sectors
	mov	bx,buffer
	mov	cx,cylinder
	xchg	cl,ch
	and	cl,3
	ror	cl,1
	ror	cl,1
	mov	dl,sector
	and	dl,3fH                                                       
	add	cl,dl                                                        
	mov	dh,head
	mov	dl,drive
	ret
set_parameters endp
	END
