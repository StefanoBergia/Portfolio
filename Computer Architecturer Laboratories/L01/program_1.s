; Architetture dei Sistemi di Elaborazione - Laboratorio 01	;
; author: 		Stefano Bergia - 276124           			;
; creation: 	15 October 2019								;
; last update:  15 October 2019								;

.data
VectorA:	.byte 	5,1,2,8,3,7,1,6		; vettore a
			.byte 	1,2,8,3,7,1,6,5
			.byte 	2,8,3,7,1,6,3,4
			.byte 	8,3,7,1,6,7,4,3
			.byte 	5,1,2,8,3,7,1,6
			.byte 	5,1,2,8,3,7,1,6
			.byte 	5,1
			
VectorB:	.byte 	6,7,1,2,3,4,1,2		; vettore b
			.byte 	5,1,2,8,3,7,1,6		
			.byte 	2,8,3,7,1,6,3,4
			.byte 	8,3,7,1,6,7,4,3
			.byte 	1,2,8,3,7,1,6,5
			.byte 	6,7,1,2,3,4,1,2
			.byte 	7,4
			
VectorC:	.space	50					; vettore c
Min:		.space 1
Max:		.space 1
		

.text         						;segnala all'asseblatore l'inizio del codice

start:	
		
		daddui r1, r0, 0			; indice vettor1
		daddui r2, r0, 50			; indica il numero totale di byte  per ogni vettore
		daddui r3, r0, 0			;min
		daddui r4, r0, 0			;max
		daddui r5, r0, 0			;registro supporto somma
		daddui r6, r0, 0			;registro supporto somma
		daddui r7, r0, 0			;flag di salto
		daddui r8,r0,1
		
		;calcolo prima somma
		lb r5, VectorA(r1)
		lb r6, VectorB(r1)
		dadd r5, r5, r6
		sb r5, VectorC(r1)
		
		dadd r3, r3, r5		;imposto il primo minimo
		dadd r4, r4, r5		;imposto il primo massimo
		
		daddui r1,r1,1
		
cycle:
		lb r5, VectorA(r1)
		lb r6, VectorB(r1)
		dadd r5, r5, r6
		sb r5, VectorC(r1)
	
		slt r7,r5, r3
		beq r7,r8,min
		
		slt r7,r4, r5
		beq r7,r8,max
		
		j end

min:
		daddui r3, r0, 0
		dadd r3, r3, r5		;imposto il minimo
		j end

max:	
		daddui r4, r0, 0
		dadd r4, r4, r5		;imposto il massimo
		
end:
		
		daddui r1,r1,1
		bne r1, r2, cycle
	
sb r3, Min(r0)
sb r4, Max(r0)


	
block: j block 	
