ifdef _LARGE_
.model large, C
else
.model small, C
endif

.code
	PUBLIC	_$read_video_region
	PUBLIC	_$write_video_region

video_segment	dw	0

if @DataSize eq 0
row    		equ	[bp+4]
column		equ	[bp+6]
num_of_columns	equ	[bp+8]
num_of_rows	equ	[bp+0ah]
buf		equ	[bp+0ch]
video_mode	equ	[bp+0eh]
else
row    		equ	[bp+6]
column		equ	[bp+8]
num_of_columns	equ	[bp+0ah]
num_of_rows	equ	[bp+0ch]
buf		equ	[bp+0eh]
video_mode	equ	[bp+12h]
endif

;void	_$read_video_region(int row, int column, int num_of_columns, int num_of_rows, int * buf, int video_mode);	

;	for (i=0; i < num_of_rows; i++) {              
;		for(j=0; j < num_of_columns; j++)    
;	        	[video_seg:vide_ofs] => buf      
;	     	[video_seg:vide_ofs] ++ 160     	 
;	}                                                

_$read_video_region proc	
	push	bp
	mov	bp,sp
	push	ds
	push	es
	push	si
	push	di
	cld
	call	near ptr set_video_segment          
	mov	cs:video_segment,ax
	mov	ds,ax                                
	mov	ax,row
	dec	ax
	mov	bx,ax
	xchg	al,ah
	shr	ax,1            			;128 * row
	shl	bx,1					;32  * row
	shl	bx,1
	shl	bx,1
	shl	bx,1
	shl	bx,1
	add	ax,bx          				;(32 + 128)*row = 160*row   
	mov	bx,column     	
	dec	bx        		
	shl	bx,1       	  	
	add	bx,ax        				;bx = row * 160 + column * 2
if @DataSize eq 0
	mov	di,buf      				;[ES:DI] = seg buf : ofs buf
else
	les	di,buf      				;[ES:DI] = seg buf : ofs buf
endif
	mov	cx,num_of_rows
	mov	dx,3daH                            	;VGA register
L$2:                                                    
	push	cx                                      
	mov	si,bx        	                        
	mov	cx,num_of_columns                       
	cmp	cs:video_segment,0b000H               	
	je	L$6
	test	byte ptr video_mode,0ffH
	je	L$6
	shl	cx,1
L$3:
	cli
L$4:
	in	al,dx
	test	al,1
	jne	L$4
L$5:
	in	al,dx
	test	al,1
	je	L$5
	movsb
	sti
	loop	L$3
	jmp	L$7
L$6:
rep 	movsw
L$7:
	add	bx,0a0H					;160
	pop	cx
	loop	L$2
	pop	di
	pop	si
	pop	es
	pop	ds
	pop	bp
	ret
_$read_video_region endp

;void	_$write_video_region(int row, int column, int num_of_columns, int num_of_rows, int * buf, int video_mode);	

;	for (i=0; i < num_of_rows; i++) {              
;		for(j=0; j < num_of_columns; j++)    
;	        	buf => [video_seg:vide_ofs]
;	     	[video_seg:vide_ofs] ++ 160     	 
;	}                                                

_$write_video_region proc
	push	bp
	mov	bp,sp
	push	ds
	push	es
	push	si
	push	di
	cld
	call	near ptr set_video_segment
	mov	cs:video_segment,ax
	mov	es,ax
	mov	ax,row
	dec	ax
	mov	bx,ax
	xchg	al,ah
	shr	ax,1
	shl	bx,1
	shl	bx,1
	shl	bx,1
	shl	bx,1
	shl	bx,1
	add	ax,bx
	mov	bx,column
	dec	bx
	shl	bx,1
	add	bx,ax
if @DataSize eq 0
	mov	si,buf
else
	lds	si,buf
endif
	mov	cx,num_of_rows
	mov	dx,3daH
L$8:
	push	cx
	mov	di,bx
	mov	cx,num_of_columns
	cmp	cs:video_segment,0b000H
	je	L$12
	test	byte ptr video_mode,0ffH
	je	L$12
	shl	cx,1
L$9:
	cli
L$10:
	in	al,dx
	test	al,1
	jne	L$10
L$11:
	in	al,dx
	test	al,1
	je	L$11
	movsb
	sti
	loop	L$9
	jmp	L$13
L$12:
	rep movsw
L$13:
	add	bx,0a0H
	pop	cx
	loop	L$8
	pop	di
	pop	si
	pop	es
	pop	ds
	pop	bp
	ret
_$write_video_region endp

set_video_segment proc	near
	push	bx
	mov	bx,0b800H
	int	11H
	and	ax,30H
	cmp	ax,30H
	jne	L$15
	mov	bx,0b000H
L$15:
	xchg	ax,bx
	pop	bx
	ret
set_video_segment endp
	END
