.model small, C
.code
	PUBLIC	set_volume_label

			db	128 dup (0)
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
drive		equ [bp+4]
label_name	equ [bp+6]                                      			
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
	add	al,41H                                                          
	mov	cs:drive_character,al                                           	
	mov	si,label_name                                                   ;
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
	mov	ax,0
	jnc	L$8
	mov	ax,2
L$8:
	pop	di
	pop	si
	pop	es
	pop	ds
	pop	bp
	ret     
set_volume_label endp
	END
