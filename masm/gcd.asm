data	segment
		num1 dw 0030h
		num2 dw 0040h
		gcd dw 1 dup(0)
data	ends

code	segment
		assume cs:code, ds:data
start:	mov ax, data
		mov ds, ax
		mov ax, num1
		mov cx, num2
rpt:	cmp ax,cx
		je store
		jnc skip
		xchg ax, cx
skip:	mov dx, 0000h
		div cx
		cmp dx, 0000h
		je store
		mov ax, dx
		jmp rpt
store:	mov gcd, cx
		mov ah, 4ch
		int 21h
code	ends
		end start