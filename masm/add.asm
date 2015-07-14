data	segment
		num1 dw 1234h
		num2 dw 1234h
		sum dw 2 dup(0)
data	ends

code	segment
		assume cs:code, ds:data
start:	mov ax, data
		mov ds, ax
		mov cx, 0h
		mov ax, num1
		add ax, num2
		jnc labnc
		inc cx
labnc:	mov sum, ax
		mov sum+2, cx
		mov ah, 4ch
		int 21h
code	ends
		end start
