.Model Small
draw_row Macro x
	Local l1
; draws a line in row x from col 10 to col 300
	MOV AH, 0CH
	MOV AL, 1
	MOV CX, 10
	MOV DX, x
L1:	INT 10h
	INC CX
	CMP CX, 301
	JL L1
	EndM

draw_col Macro y
	Local l2
; draws a line col y from row 10 to row 189
	MOV AH, 0CH
	MOV AL, 1
	MOV CX, y
	MOV DX, 10
L2:	INT 10h
	INC DX
	CMP DX, 190
	JL L2
	EndM

.Stack 100h
.Data
new_timer_vec	dw	?,?
old_timer_vec 	dw	?,?
timer_flag 	db	0
vel_x 		dw 	1
vel_y 		dw 	1
.Code

set_display_mode Proc
; sets display mode and draws boundary
	MOV AH, 0
	MOV AL, 04h; 320x200 4 color
	INT 10h
; select palette	
	MOV AH, 0BH
	MOV BH, 1
	MOV BL, 1
	INT 10h
; set bgd color
	MOV BH, 0
	MOV BL, 1; cyan
	INT 10h
; draw boundary
	draw_row 10
	draw_row 189
	draw_col 10
	draw_col 300
	
	RET
set_display_mode EndP

display_ball Proc
; displays ball at col CX and row DX with color given in AL
; input: AL = color of ball
;	 CX = col
;	 DX = row
	MOV AH, 0CH	; write pixel
	INT 10h
	INC CX		; pixel on next col
	INT 10h
	INC DX		; down 1 row
	INT 10h
	DEC CX		; prev col
	INT 10h
	DEC DX		; restore dx
	RET 
display_ball EndP

timer_tick Proc
	PUSH DS
	PUSH AX
	
	MOV AX, Seg timer_flag
	MOV DS, AX
	MOV timer_flag, 1
	
	POP AX
	POP DS
	
	IRET
timer_tick EndP

move_ball Proc
; erase ball at current position and display at new position
; input: CX = col of ball position
;	 DX = rwo of ball position
; erase ball
	MOV AL, 0
	CALL display_ball
; get new position
	ADD CX, vel_x
	ADD DX, vel_y
; check boundary
	CALL check_boundary
; wait for 1 timer tick to display ball
test_timer:
	CMP timer_flag, 1
	JNE test_timer
	MOV timer_flag, 0
	MOV AL, 3
	CALL display_ball
	RET	
move_ball EndP

check_boundary Proc
; determine if ball is outside screen, if so move it back in and 
; change ball direction
; input: CX = col of ball
;	 DX = row of ball
; output: CX = valid col of ball
;	  DX = valid row of ball
; check col value
	CMP CX, 11
	JG LP1
	MOV CX, 11
	NEG vel_x
	JMP LP2 
LP1:	CMP CX, 298
	JL LP2
	MOV CX, 298
	NEG vel_x
; check row value
LP2:	CMP DX, 11
	JG LP3
	MOV DX, 11
	NEG vel_y
	JMP done
LP3:	CMP DX, 187
	JL done
	MOV DX, 187
	NEG vel_y
done:
	RET 
check_boundary EndP

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

main Proc
	MOV AX, @data
	MOV DS, AX
	
; set graphics display mode & draw border
	CALL set_display_mode
; set up timer interrupt vector
	MOV new_timer_vec, offset timer_tick
	MOV new_timer_vec+2, CS
	MOV AL, 1CH; interrupt type
	LEA DI, old_timer_vec
	LEA SI, new_timer_vec
	CALL setup_int
; start ball at col = 298, row = 100
; for the rest of the program CX = ball row, DX = ball col
	MOV CX, 298
	MOV DX, 100
	MOV AL, 3
	CALL display_ball
; wait for timer tick before moving the ball
tt:
	CMP timer_flag, 1
	JNE tt
	MOV timer_flag, 0
	CALL move_ball
tt2:
	CMP timer_flag, 1
	JNE tt2
	MOV timer_flag, 0
	JMP tt
main EndP
End main
