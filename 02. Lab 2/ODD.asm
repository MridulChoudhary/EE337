 ORG 0H
 LJMP MAIN
 ORG 100H
 MAIN:
 CALL ODDSUM
 HERE: SJMP HERE
 ORG 130H
	 
 ODD:
 MOV A, 70H
 ADD A, @R0
 MOV 70H, A
 RET
 
 ODDSUM:
 CLR A 
 MOV 70H, A
 // MOV 0x70H, #00H
 MOV R0, #60H
 MOV R3, #08H  
 
 LOOP1:
 MOV A, @R0
 ANL A, #01H
 JZ LOOP2
 CALL ODD
 
 LOOP2: 
 INC R0
 DJNZ R3, LOOP1
 
 RET
 END 