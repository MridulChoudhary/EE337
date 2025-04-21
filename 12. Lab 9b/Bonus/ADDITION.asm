            NAME    ADDITION
            PUBLIC  add_numbers
            EXTRN   XDATA (num1, num2, sum)

            CSEG AT 100H ; Code Segment

add_numbers:
            ; Load num1 into R2:R3
            MOV     DPTR, #num1
            MOVX    A, @DPTR
            MOV     R2, A           ; Low byte
            INC     DPTR
            MOVX    A, @DPTR
            MOV     R3, A           ; High byte

            ; Load num2 into A and add to R2:R3
            MOV     DPTR, #num2
            MOVX    A, @DPTR
            ADD     A, R2           ; Add low bytes
            MOV     R4, A           ; Low byte of result
            JNC     NO_CARRY
            INC     R3              ; Carry -> increment high byte

NO_CARRY:   INC     DPTR
            MOVX    A, @DPTR
            ADD     A, R3           ; Add high bytes
            MOV     R5, A           ; High byte of result

            ; Store result in sum
            MOV     DPTR, #sum
            MOV     A, R4
            MOVX    @DPTR, A
            INC     DPTR
            MOV     A, R5
            MOVX    @DPTR, A

            RET
            END
