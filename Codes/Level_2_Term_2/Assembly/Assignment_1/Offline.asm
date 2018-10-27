
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

TITLE EXAMPLE:OFFLINE_1
.MODEL SMALL
.STACK 100H 

.DATA
;data definitions are here 
MSG1 DB "ENTER INPUT(2 DIGITS): $"
MSG2 DB "OUTPUT(4 DIGITS): $"
VAR1 DB ?     
VAR2 DW ?




.CODE
MAIN PROC
    ;SETTING UP THE DATA SEGMENT
    MOV DX,@DATA
    MOV DS,DX
    ;PRINTING THE FIRST MESSAGE
    MOV AH,9
    LEA DX,MSG1
    INT 21H
    ;ENTER THE TWO INPUTS
    MOV AH,1
    INT 21H
    MOV DL,AL
    MOV AH,1 
    INT 21H
    MOV DH,AL
    ;CONVERT THE NUMBER INTO A COUNT
    SUB DL,'0'
    SUB DH,'0'
    MOV CX,10 
    MOV BL,0
    TOP:
    ADD BL,DL
    LOOP TOP
    ADD BL,DH 
    MOV VAR1,BL
    ;PRINT NEW LINE
    MOV AH,2
    MOV DL,0DH
    INT 21H
    MOV DL,0AH
    INT 21H 
    ;PRINTING THE LAST MESSAGE
    MOV BX,0
    MOV AH,9
    LEA DX,MSG2
    INT 21H
    ;CALCULATING THE ANSWER 
    MOV BL,VAR1
    
    MOV CX,BX 
    MOV AX,0 
    MOV DX,1
    ANSWER: 
    CMP CX,0
    JLE JUMPER
    ADD AX,DX
    ADD DX,DX 
    DEC CX
    JMP ANSWER
    JUMPER: 
    MOV VAR2,AX
    ;PRINTING THE ANSWER 
    
    MOV BL,0 
    WHILE_1000:
    CMP VAR2,1000 
    JLE PRINT_1000
    SUB VAR2,1000     
    ADD BL,1
    JMP WHILE_1000
    PRINT_1000:
    ADD BL,'0'
    MOV AH,2
    MOV DL,BL
    INT 21H
    
    
    MOV BL,0
    WHILE_100:
    CMP VAR2,100 
    JLE PRINT_100
    SUB VAR2,100     
    ADD BL,1
    JMP WHILE_100
    PRINT_100:
    ADD BL,'0'
    MOV AH,2
    MOV DL,BL
    INT 21H 
    
    
    MOV BL,0
    WHILE_10:
    CMP VAR2,10 
    JLE PRINT_10
    SUB VAR2,10     
    ADD BL,1
    JMP WHILE_10
    PRINT_10:
    ADD BL,'0'
    MOV AH,2
    MOV DL,BL
    INT 21H
    
    MOV BL,0
    WHILE_1:
    CMP VAR2,1 
    JL PRINT_1
    SUB VAR2,1     
    ADD BL,1
    JMP WHILE_1
    PRINT_1:
    ADD BL,'0'
    MOV AH,2
    MOV DL,BL
    INT 21H
    
    
    
    
    
    
MAIN ENDP
END MAIN





