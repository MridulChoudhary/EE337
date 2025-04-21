CSEG AT 100h
PUBLIC add_numbers

add_numbers:
    MOV A, R0       ; Load first number into accumulator
    ADD A, R1       ; Add second number
    MOV R2, A       ; Store result in R2
    RET  