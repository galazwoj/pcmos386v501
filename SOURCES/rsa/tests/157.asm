.model small
.stack 100h
.code

	extrn	_setup_i24:proc

; based on idea from Forever Young Software www page 
DoErr  	proc                    ; make an error (deliberately)
	push ax
	push dx

        mov  ah,19h              ; get disk drive
        int  21h                 ;
        push ax                  ; and save it for later

        mov  ah,0Eh              ; set drive to a:
        xor  dl,dl               ;
        int  21h                 ;

        mov  ah,39h              ; try to create a dir on drv a:
        mov  dx,offset testdir  ;
        int  21h                 ;

        pop  dx                  ; restore current drive
        mov  ah,0Eh              ; set drive to the saved drive
        int  21h                 ;

	pop  dx
	pop  ax
        ret                      
DoErr   endp

start:
	mov  ax, @data
	mov  ds, ax

        mov  dx,offset msg1       
        mov  ah,09h               
        int  21h                  

	call _setup_i24
	call DoErr

        mov  dx,offset msg2       
        mov  ah,09h               
        int  21h                  

	mov  ah, 4ch
	int  21h

.data
msg1	db 'testing ...','$'	  
msg2  	db 'done','$'
testdir db  'testcd',0

end	start
