data	segment
		num equ 10h
		fib dw num dup(?)
data	ends

code	segment
		assume cs:code, ds:data
start:	mov ax, data
		mov ds, ax
		mov cx, num
		mov si, offset fib
		mov ax, 00h
		mov bx, 01h
fibl:	mov [si], bx
		add bx, ax
		mov ax, [si]
		inc si
		loop fibl
		mov ah, 4ch
		int 21h
code	ends
		end start