data	segment
		src db "India is my country"
		db 100 dup(0)
		strlen equ $-src
		dst db strlen dup(0)
data	ends

code	segment
		assume cs:code, ds:data, es:data
start:	mov ax, data
		mov ds, ax
		mov es, ax

		lea si, src
		lea di, dst
		mov cx, strlen
		cld
		rep movsb

		mov ah, 4ch
		int 21h
code	ends
		end start
