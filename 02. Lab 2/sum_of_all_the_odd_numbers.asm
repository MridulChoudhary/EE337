ORG 0H
LJMP MAIN
ORG 100H

MAIN:
    CALL ODDSUM
HERE: 
    SJMP HERE

ORG 130H
ODD:
    ANL A, #01H     
    CJNE A, #00H, ADDITION 
    CJNE A, #01H, SKIP_ADD 
ODD_RET:


ODDSUM:
    MOV R0, #60H    
    MOV R7, #08H    
    CLR A           
    MOV 70H, A      

ODDSUM_LOOP:
    MOV A, @R0     
	SJMP ODD      

ADDITION:
	MOV A, @R0
	ADD A, 70H      
    MOV 70H, A      

SKIP_ADD:
    INC R0          
    DJNZ R7, ODDSUM_LOOP 

    RET

END