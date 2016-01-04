dptr equ r0

mov 70H, #99H ; input

mov dptr, #70H
mov a, @dptr

mov b, #64H
div ab
inc dptr
mov @dptr, a

mov a, b
mov b, #0AH
div ab
inc dptr
mov @dptr, a

inc dptr
mov a, b
mov @dptr, a

here: sjmp here