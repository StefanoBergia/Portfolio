; Architetture dei Sistemi di Elaborazione - Laboratorio 03	;
; author: 		Stefano Bergia - 276124           			;
; creation: 	22 October 2019								;
; last update:  22 October 2019								;

.data
V:	  .byte 	43,6,1,15,17,43,31,3,11,4,2,8,7,34,39,15,16,29,45,7,4,50,32,31,25,17,9,45,42,40	


even_counter:	.space	1 	
odd_counter:	.space 	1		
		

.text         						

start:	
        daddui r1,r0,0		;indice V
		daddui r2,r0,1		;indice V+1
		daddui r3,r0,30		;totale valori
		daddui r12,r0,0		;odd_counter			+8
loop:

	lb r4, V(r1)	
	lb r5, V(r2)
	daddui r10,r0,0	
	and r6,r4,r5							;+4			
	
	count:
		andi r14,r6,1 
		dsrl r6,r6,1
		dadd r10,r10,r14		
	bne r6,r0,count				;numero di cicli dipende dai dati  +5
	
	daddui r1,r1,1				;incremento indici   
	daddui r2,r2,1
	
	andi r14,r10,1				;determio se il numero di 1 è pari o dispari
	daddu r12,r12,r14			;aggiorno oddcounter
	
	bne r2,r3,loop										;+4
	
	
	sb r12,odd_counter(r0)
	daddui r12,r12,1
	dsub r12,r3,r12
	sb r12,even_counter(r0)
	
block: j block 


;cicli totali= 8+ (4+5*8 +4)*30 =1598