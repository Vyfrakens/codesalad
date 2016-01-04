dptr equ r0

mov dptr, #80H
mov a, #00h
mov @dptr, a
mov a, #0ccH
mov @dptr, a
mov a, #90h
mov @dptr, a

mov dptr, #90h
mov a, #88h
mov @dptr, a
mov r1, #03h
mov a, #0ffh
l1:
mov @dptr, a
djnz r1, l1

here: sjmp here
