dptr equ r0

mov 20H, #0BH ; input

mov dptr, #20H
mov a, @dptr

cjne a, #0AH, temp
temp:
jc skip ; a < 10
add a, #07H
skip: 
add a, #30H

inc dptr
mov @dptr, a

here: sjmp here
