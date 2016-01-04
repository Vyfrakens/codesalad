dptr equ r0

mov 20H, #37H ; input

mov dptr, #20H
mov a, @dptr

subb a, #30H
cjne a, #0AH, temp
temp:
jc skip ; a < 10
subb a, #07H
skip: 

inc dptr
mov @dptr, a

here: sjmp here
