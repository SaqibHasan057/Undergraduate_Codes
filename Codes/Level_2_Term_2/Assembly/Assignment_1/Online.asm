
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

TITLE EXAMPLE:ONLINE_1
.MODEL SMALL
.STACK 100H 

.DATA
;data definitions are here 
MSG1 DB "ENTER INPUT(2 DIGITS): $"
MSG2 DB "OUTPUT(5 DIGITS): $"
VAR1 DB ?     
VAR2 DW ? 
SUM  DW ?

INPUT1 DW 1
INPUT2 DW 2




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
    MOV BX,0
    MOV BL,VAR1
    
    CMP VAR1,1
    JLE EXIT_3
    
    CMP VAR1,2
    JLE EXIT_4
    
    MOV AX,3
    FIRST_LOOP: 
    MOV CX,INPUT1
    SUB CX,1  
    MOV BX,INPUT2
    SECOND_LOOP:
    CMP CX,0
    JLE EXIT1
    ADD BX,INPUT2
    DEC CX
    JMP SECOND_LOOP 
    EXIT1:
    MOV CX,INPUT1
    MOV DX,INPUT2
    MOV INPUT1,DX
    MOV INPUT2,BX
    ADD AX,BX 
    SUB VAR1,1
    CMP VAR1,2
    JLE EXIT_2
    JMP FIRST_LOOP 
    
    EXIT_2:
    MOV VAR2,AX
    JMP PRINTING
    
    EXIT_3:
    MOV VAR2,1
    JMP PRINTING
    
    EXIT_4:
    MOV VAR2,3
    JMP PRINTING  
    
    ;PRINTING THE ANSWER 
    PRINTING:
    
    MOV BL,0 
    WHILE_10000:
    CMP VAR2,10000 
    JLE PRINT_10000
    SUB VAR2,10000     
    ADD BL,1
    JMP WHILE_10000
    PRINT_10000:
    ADD BL,'0'
    MOV AH,2
    MOV DL,BL
    INT 21H
    
    
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





