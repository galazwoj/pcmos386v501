ifdef _LARGE_
.model large, C
else
.model small, C
endif

.code
	PUBLIC	set_volume_label

drive_character		db	'?:\'			
label_buf		db	13 dup (0)
FCB			db	0FFh        		; extended FCB
			db	0, 0, 0, 0, 0        	; reservved
			db	8                      	; filename attribute - volume label
drive_number		db	0			; drive number 
			db	11 dup ('?')		; blank padded file name
			db	25 dup (0)  		; should be set to zero        	

; int set_volume_label(int drive, char *label_name);
set_volume_label proc
if @DataSize eq 0
drive		equ [bp+4]
label_name	equ [bp+6]                                      			
else
drive		equ [bp+6]
label_name	equ [bp+8]                                      			
endif
	push	bp						                	
	mov	bp,sp                                                           
	push	ds                                                              
	push	es                                                              
	push	si                                                              
	push	di                                                              
	cld                                                                     
	mov	ax,drive                                                 	
	or	al,al                                                           
	jne	L$5                                                             
	mov	ah,19H                                                          
	int	21H		; DOS 1+ - GET CURRENT DEFAULT DRIVE            
	inc	al                                                              
L$5:                                                                            
	mov	cs:drive_number,al								
	dec	al                                                             	
	add	al,'A'                                                          
	mov	cs:drive_character,al                                           	
if @DataSize eq 0
	mov	si,label_name                                                   ;
else
	lds	si,label_name                                                   ;
endif
	mov	ax,cs                                                           
	mov	es,ax                                                           
	lea	di,label_buf                                                   ;
	xor	cx,cx                                                           
L$6:                                                                            
	lodsb                                                                   
	inc	cx                                                              
	cmp	cx,9                                                            
	jne	L$7                                                             
	mov	byte ptr es:[di],'.'                                          	
	inc	di                                                              
	xor	cx,cx                                                           
L$7:                                                                            
	stosb                                                                   
	or	al,al                                                           
	jne	L$6			; copy labelname -> labelspace           
	mov	ax,cs                                                           
	mov	ds,ax                                                           
	mov	ah,13H                                                          
	lea	dx,FCB
	int	21H			; DOS 1+ - DELETE FILE USING FCB	
	mov	ah,3cH			
	mov	cx,8                    ; attribute: volumen label
	lea	dx,drive_character	; ASCIZ filename
	int	21H         		; DOS 2+ - CREAT - CREATE OR TRUNCATE FILE
	jc	L$8
	mov	bx,ax
	mov	ah,3eh			; DOS 2+ - CLOSE - CLOSE FILE
	int	21h			
	xor	ax,ax

L$8:
	pop	di
	pop	si
	pop	es
	pop	ds
	pop	bp
	ret     
set_volume_label endp
	END
	                		