data	segment
		num dw 5h
		fact dw 1 dup(?)
data	ends

code	segment
		assume cs:code, ds:data
start:	mov ax, data
		mov ds, ax
		mov cx, num
		mov ax, 01h
factl:	mul cx
		loop factl
		mov fact, ax
		mov ah, 4ch
		int 21h
code	ends
		end start