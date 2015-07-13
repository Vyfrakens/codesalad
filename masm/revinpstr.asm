.model small
.stack 1000h

inp macro
	mov ah, 01
	int 21h
endm

inpstr macro s
	mov cx, 0
	lea si, s 
rst:	mov ah, 01
	int 21h
	mov [si], al
	inc si
	inc cx
	cmp al, cr
	jne rst
endm

disp macro arg
	mov dl, arg
	mov ah, 02
	int 21h
endm

revstr macro s
	dec si
l1: disp [si]
	dec si
	loop l1
endm

dispstr macro s
	lea dx, s
	mov ah, 09
	int 21h
endm

data segment
cr equ 0dh
lf equ 0ah
str db 0fh dup('$')
data ends


code segment
	assume cs:code, ds:data
start:
	mov ax, data
	mov ds, ax
	inpstr str
	revstr str
	;dispstr str
	mov ah, 4ch
	int 21h
code ends

end start
