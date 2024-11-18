data segment
    msg1 db 10,13, 'Enter the string :$'
    msg2 db 10,13, 'String is palindrome $'
    msg3 db 10,13, 'String is not palindrome$'
    strg db ?<50>
    
data ends

code segment
    assume cs:code, ds:data
    start:
        mov ax, data
        mov ds, ax
        
        lea dx, msg1
        mov ah, 09h
        int 21h
        
        lea si, strg
        lea di , strg
    
    next:
        mov ah, 01h
        int 21h
        cmp al, 13
        je terminate
        mov [di], al
        inc di
        jmp next
    
    terminate:
        mov al, '$'
        mov [di], al
        dec di
        jmp checkpalindrome
    
    checkpalindrome:
        mov al, [si]
        cmp al, [di]
        jne notpalindrome
        inc si
        dec di
        cmp si, di
        jl checkpalindrome
    
    palindrome:
        lea dx, msg2
        mov ah, 09h
        int 21h
        jmp endprogram
        
    notpalindrome:
        lea dx, msg3
        mov ah, 09h
        int 21h
        jmp endprogram
                          
    
    endprogram:
        mov ah, 4ch
        int 21h
code ends
end start