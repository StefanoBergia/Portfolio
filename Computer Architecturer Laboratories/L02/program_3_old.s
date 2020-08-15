; Architetture dei Sistemi di Elaborazione - Laboratorio 03	;
; author: 		Stefano Bergia - 276124           			;
; creation: 	22 October 2019								;
; last update:  22 October 2019								;

.data
;V:	  .byte 	43,6,1,15,17,43,31,3,11,4,2,8,7,34,39,15,16,29,45,7,4,50,32,31,25,17,9,45,42,40
V: 	  .byte		255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
ONES: .byte		1,2,4,8,16,32,64,128			

even_counter:	.space	1 	
odd_counter:	.space 	1		
		

.text         						

start:	
        daddui r1,r0,0		;indice V
		daddui r2,r0,1		;indice V+1
		daddui r3,r0,30		;totale valori
		daddui r8,r0,8		;per conteggio numero di bit a uno
		daddui r12,r0,0		;even_counter
		daddui r13,r0,0		;odd_conter
		daddui r15,r0,255	;switch
loop:

	lb r4, V(r1)
	lb r5, V(r2)
	daddui r7,r0,0
	daddui r10,r0,255	;flag even_counter
	daddui r11,r0,0		;flag odd_counter
	and r6,r4,r5
	
	count:
	    lb	r14,ONES(r7)
		daddui r7,r7,1
		and r9,r6,r14
		NOP							;stallo
		bne r14,r9,flag
			xor r10,r10,r15			;se numero di 1 è dispari, r13 a 1 e r12 a 0
			xor r11,r11,r15			;se numero di 1 è pari, r13 a 0 e r12 a 1
		flag: 
			bne r7,r8,count	
	
	daddui r1,r1,1				;incremento indici
	daddui r2,r2,1
	
	slt r10,r10,r15				;normalizzo i flag
	slt r11,r11,r15				; attenzione per evitare di aggiungere una not non inverto i valori trovati con una not ma ne scambio il significato
	
	daddu r12,r12,r11			;aggiorno evencounter
	daddu r13,r13,r10			;affiorno oddcounter
	bne r2,r3,loop
	
	sb r12,even_counter(r0)
	sb r13,odd_counter(r0)
	
block: j block 

;01 1110‬
;10 1011‬
;00 1010