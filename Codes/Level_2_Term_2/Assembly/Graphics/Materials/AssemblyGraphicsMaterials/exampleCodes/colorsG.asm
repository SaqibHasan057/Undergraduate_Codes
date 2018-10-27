.Model Small
.Stack 100h
.Code
main Proc
; set VGA 320x200 256 color mode
	MOV AH, 0h
	MOV AL, 13h
	INT 10h
; draw 256 color band	
	MOV AH, 0CH ; write pixel function
	MOV AL, 0 ; start pixel color 0
	MOV BH, 0 ; page 0
	MOV DX, 50 ; row
OL1:	MOV CX, 31 ; col
L1:	INT 10h
	INC AL	; next color
	INC CX	; next col
	CMP CX, 287
	JL L1
	INC DX; next row
	CMP DX, 151
	JL OL1
; getch    	
    	MOV AH, 0
    	INT 16h
; return to text mode    	
    	MOV AX, 3
    	INT 10h
; return to DOS
    	MOV AH, 4CH
    	INT 21h
main EndP
     End main
