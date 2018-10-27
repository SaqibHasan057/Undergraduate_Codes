.Model Small
.Stack 100h
.Code
main Proc
; set graphics mode 4
	MOV AH,0h
	MOV AL,4h
	INT 10h
; set bgd color to cyan
	MOV AH, 0BH
	MOV BH, 00h
	MOV BL, 3
    INT 10h
; select palette 0
	MOV BH, 1
	MOV BL, 0
	INT 10h
; move cursor to page 0, row 12, col 19
    	MOV AH, 02
    	MOV BH, 0
    	MOV DH, 12
    	MOV DL, 19
    	INT 10h
; write char    	
    	MOV AH, 9
    	MOV AL, 'X'
    	MOV BL, 2 ; color value from palette
    	MOV CX, 1
    	INT 10h
; getch    	
    	MOV AH, 0
    	INT 16h
; return to text mode
    	MOV AX, 3
    	INT 10h
    	
; return to dos
    	MOV AH, 4CH
    	INT 21h
main EndP
     End main