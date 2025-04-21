            NAME MAC_OPERATION
            PUBLIC mac_operation
            EXTRN XDATA (num1, num2, a1, a2, sum)

            CSEG AT 0100H

mac_operation:

            ; Load num1 and a1
            MOV     DPTR, #num1
            MOVX    A, @DPTR       ; A = num1

            MOV     DPTR, #a1
            MOVX    A, @DPTR       ; B = a1
			MOV B, A
            MUL     AB             ; A * B ? A (low), B (high)
            MOV     R0, A          ; Store result of num1*a1 in R0
            ; We ignore B (high byte) to keep it 8-bit only

            ; Load num2 and a2
            MOV     DPTR, #num2
            MOVX    A, @DPTR

            MOV     DPTR, #a2
            MOVX    A, @DPTR
			MOV B, A
            MUL     AB             ; A * B ? A (low), B (high)
            ADD     A, R0          ; Add previous result
            ; Again ignoring B for 8-bit only

            ; Store final result in sum
            MOV     DPTR, #sum
            MOVX    @DPTR, A

            RET

            END
