				
				
				AREA asm_functions, CODE, READONLY				
                EXPORT  average
average
				
				MOV   r12, sp
				STMFD sp!,{r4-r8,r10-r11,lr}				
				
				MOV   R6,#0
				MOV   R5,#0	
				MOV	  R4,#0			;registro che conterrà la media

loop			CMP R6,R1
				BEQ end_loop
				
				LDR R3,[R0,R5]
				ADD R4,R4,R3
				MOVVS R4,#0
				ADD R5,#4
				ADD R6,#1
				
				B loop			
				
end_loop		CMP R4,#0
				UDIVNE R0,R4,R1
				MOVEQ R0,#0
				

				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END