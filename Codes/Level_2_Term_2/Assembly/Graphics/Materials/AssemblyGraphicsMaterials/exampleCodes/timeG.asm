.Model Small
.Stack 100h
.Data
time_buf 	db 	'00:00:00$'	; time buffer hh:mm:ss
cursor_pos 	dw 	? 		; (row:col)
new_vec 	dw 	?,?
old_vec 	dw 	?,?

.Code
main Proc
	MOV AX, @data
	MOV DS, AX
; save cursor position
	MOV AH, 3
	MOV BH, 0
	INT 10h
	MOV cursor_pos, DX
; setup int proc by placing seg:off time_int in new_vec
	MOV new_vec, offset time_int	; offset
	MOV new_vec+2, Seg time_int	; segment
	LEA DI, old_vec			; di points to vector buffer
	LEA SI, new_vec			; si points to new vector
	MOV AL, 1CH			; timer interrupt
	CALL setup_int		
; read keyboard
	MOV AH, 0
	INT 16h
; restore old int vec
	LEA DI, new_vec			; di points to vector buffer
	LEA SI, old_vec			; si points to old vec
	MOV AL, 1CH			; timer interrupt
	CALL setup_int
	
	MOV AH, 4CH
	INT 21h
main EndP

time_int Proc
; interrupt procedure activated by the timer
	PUSH DS
	MOV AX, @data
	MOV DS, AX
; get new time
	LEA BX, time_buf
	CALL get_time
; display time
	LEA DX, time_buf
	MOV AH, 09h
	INT 21h
; restore cursor
	MOV AH, 2	; move cursor
	MOV BH, 0
	MOV DX, cursor_pos
	INT 10h
	POP DS
	IRET
time_int EndP

get_time Proc
; get time of day and store ascii digits in time buffer
; input bx = address of time buffer
	MOV AH, 2CH		; get time
	INT 21h			; ch = hr, cl = min, dh = sec
; convert hr to ascii and store
	MOV AL, CH
	CALL convert
	MOV [BX], AX
; convert mm to ascii and store
	MOV AL, CL
	CALL convert
	MOV [BX+3], AX
; convert ss to ascii and store
	MOV AL, DH
	CALL convert
	MOV [BX+6], AX
	RET
get_time EndP

convert Proc
	MOV AH, 0
	MOV DL, 10
	DIV DL
	OR AX, 3030h
	RET
convert EndP

setup_int Proc
; save old vector and set up new vector
; input: al = interrupt number
;	 di = address of buffer for old vector
;	 si = address of buffer containing new vector
; save old interrupt vector
	MOV AH, 35h	; get vector
	INT 21h
	MOV [DI], BX	; save offset
	MOV [DI+2], ES  ; save segment
; setup new vector
	MOV DX, [SI]	; dx has offset
	PUSH DS		; save ds
	MOV DS, [SI+2]	; ds has the segment number
	MOV AH, 25h	; set vector
	INT 21h
	POP DS
	RET
setup_int EndP

End main