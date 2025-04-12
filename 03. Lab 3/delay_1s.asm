// -- DO NOT CHANGE ANYTHING UNTIL THE **** LINE--//
ORG 0H
LJMP MAIN
ORG 100H
MAIN:
MOV P1, #01H
CALL delay_1sec
MOV P1, #00H
HERE: SJMP HERE

ORG 130H
// *****************
delay_1sec:
push 00h
mov r0, #100
h3: acall delay_10ms
djnz r0, h3
pop 00h
ret
delay_10ms:
push 00h
mov r0, #40
h2: acall delay_250us
djnz r0, h2
pop 00h
ret
delay_250us:
push 00h
mov r0, #244
h1: djnz r0, h1
pop 00h
ret
//DELAY_1s:
// ADD YOUR CODE HERE
//RET
END