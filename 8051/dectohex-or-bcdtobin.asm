dptr equ r0

mov 70H, #92H ;=5CH input

mov dptr, #70H
mov a, @dptr
mov b, #10H
div ab
mov r1, b

mov b, #0AH
mul ab

add a, r1
inc dptr
mov @dptr, a

here: sjmp here