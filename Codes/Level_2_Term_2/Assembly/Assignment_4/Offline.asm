.model small
.stack 100h
.data 
string1 db 80 dup(0) 
string2 db 80 dup(0)  
stringOutput db 80 dup(0)
length1 dw ?
length2 dw ? 
lengthOut dw ?
stop dw ? 
start dw ?
crlf db 0dh,0ah,'$'
.code
main proc
    mov ax,@data
    mov ds,ax
    mov es,ax
    
    ;read string 1
    
    lea di,string1
    call read_str  
    mov length1,bx
    
    ;go to a new line
    
    lea dx,crlf
    mov ah,9
    int 21h
    
    ;read string 2
    
    lea di,string2
    call read_str
    mov length2,bx
    
    ;compare whether the strings are null or string2 longer than string1     
    xor bx,bx
    xor dx,dx
    
    mov bx,length1
    cmp bx,0
    je no
    
    mov dx,length2
    cmp dx,0
    je no 
    
    cmp dx,bx
    jg no
    
       
    ;see if string2 is a substring of string1   
    mov dx,0 
   
    
    lea si,string1
    lea di,string2
    cld         
    
    ;compute stop
    mov stop,si
    mov bx,length1
    add stop,bx
    mov cx,length2
    sub stop,cx
    
    ;initialize start
    mov start,si
    
 repeat:
    mov cx,length2
    mov si,start
    lea di,string2
    repe cmpsb  
    je yes
    
    ;substring not found yet  
    mov si,start
    lea di,stringOutput 
    add di,dx
    cld
    movsb
    inc dx
    inc start
    
    ;see if start<=stop
    mov ax,start
    cmp ax,stop
    jnle no
    jmp repeat    
    
 yes:   
    mov ax,length2
    add start,ax
    jmp repeat
    
 no:
    mov si,start
    lea di,stringOutput  
    add di,dx
    
 last:
    movsb
    inc si  
    inc di
    inc start
    inc dx 
    mov ax,length1
    cmp start,ax
    jge exit
    jmp last
          
    
    
 exit: 
    mov lengthOut,dx  
    lea dx,crlf
    mov ah,9
    int 21h
    
    lea si,string1
    mov bx,length1
    call disp_str    
    
    lea dx,crlf
    mov ah,9
    int 21h
    
    lea si,string2
    mov bx,length2
    call disp_str     
    
    lea dx,crlf
    mov ah,9
    int 21h
    
    lea si,stringOutput
    mov bx,lengthOut
    call disp_str      
    
    
  
    ;dos exit
    
    mov ah,4ch
    int 21h
    
    main endp   


read_str proc 
    ;reads and store a string
    ;bx number of character read
    
    
    push ax
    push di
    
    cld
    xor bx,bx  
    mov ah,1
    int 21h
    while:
    cmp al,0dh
    je end_while
    cmp al,8h
    jne else
    dec di
    dec bx
    jmp read
    else:
    stosb
    inc bx
    read:
    int 21h
    jmp while
    end_while:
    pop di
    pop ax
    ret
    read_str endp 


disp_str proc
    push ax
    push bx
    push si
    push cx
    push dx
    mov cx,bx
    jcxz p_exit
    cld
    top:
    lodsb
    mov dl,al
    mov ah,2
    int 21h
    loop top
    p_exit:
    pop ax
    pop bx
    pop si
    pop cx
    pop dx
    ret
    disp_str endp
end main
    