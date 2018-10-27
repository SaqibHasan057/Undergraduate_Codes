.Model Small
.Stack 100h
.Data
mychar db ?
.Code
main Proc
	MOV AX, @data
	MOV DS, AX
getch:
	MOV AH, 0
	INT 16h
	CMP AL, 0
	JE getch 
; store char
	MOV mychar, AL
; set video mode
	MOV AH, 0
	MOV AL, 3
	INT 10h
; clear window to red
	MOV AH, 6	; scroll up function
	MOV CX, 081AH	; upper left corner (1Ah, 08h)
	MOV DX, 1034h	; lower right corner (34h, 10h)
	MOV BH, 43h	; cyan chars on red background
	MOV AL, 0	; scroll all lines
	INT 10h		; clear window
; move cursor
	MOV AH, 2	; move cursor function
	MOV DX, 0C27h	; center of screen
	XOR BH, BH	; page 0
	INT 10h		; move cursor
	
; display character with attribute
	MOV AH, 09	; display character function
	MOV BH, 0	; page 0
	MOV BL, 0CBh	; blinking cyan char, red back
	MOV CX, 1	; display one character
	MOV AL, mychar	; character is 'A'
	INT 10h
; move cursor
	MOV AH, 2	; move cursor function
	MOV DX, 1827h	; row 24, col 39
	XOR BH, BH	; page 0
	INT 10h		; move cursor
; getch
	MOV AH, 1
	INT 21h
; dos exit
	MOV AH, 4CH
	INT 21h
main EndP
	End main