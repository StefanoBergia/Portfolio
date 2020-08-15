; Architetture dei Sistemi di Elaborazione - Laboratorio 03	;
; author: 		Stefano Bergia - 276124           			;
; creation: 	29 October 2019								;
; last update:  29 October 2019								;

.data
V1:	.double 	1.62,3.06,8.12,8.75,2.21,7.26,7.82,2.40,2.78,0.54,3.97,0.56,2.44,5.47,8.07,1.10,5.90,7.56,4.50,0.49,1.86,1.88,4.33,2.44,2.05,2.08,2.08,8.15,5.29,4.85				
V2:	.double 	3.67,3.26,1.84,5.20,6.29,9.72,9.23,0.68,0.47,5.80,4.61,5.28,7.68,7.58,5.16,4.50,9.97,4.94,0.50,0.32,3.35,8.58,2.18,7.74,2.98,9.10,5.35,8.46,2.69,8.38
V3: .double		5.31,6.98,0.10,4.54,1.84,7.71,0.58,3.55,0.61,0.81,8.39,6.43,0.36,6.63,6.63,7.56,6.65,4.24,0.04,2.13,1.76,8.27,1.00,6.20,9.57,8.88,6.58,1.59,1.05,0.99			
V4: .double		6.51,1.12,3.86,4.42,2.63,1.09,3.16,5.00,8.63,4.17,2.49,5.24,5.88,6.55,7.42,9.53,0.00,0.45,4.48,9.03,0.40,0.87,6.76,7.91,0.04,9.36,6.69,1.51,7.22,9.73

V5:	.space	240 	;30*8 byte	
V6:	.space 	240		
		

.text         						;segnala all'asseblatore l'inizio del codice

start:	
		daddui	r7,r7,0	   ;FDEMW 
		daddui   r8,r8,240  ;FDEMW 
		l.d f1,V1(r7)		 ;FDEMW
cycle:						 
		l.d f3,V3(r7)		  ;FDEMW
		mul.d f5,f1,f2		   ;FDEEEEEEEEMW   
		l.d f4,V4(r7)			;FDEMW
		add.d  f5,f5,f3          ;FDE------EEEMW	 							
		mul.d f6,f3,f4			  ;FDEEEEEEEEMW	   							
		div.d f6,f6,f5			   ;FD-----E---EEEEEEEEEEEMW		
		s.d f5,V5(r7)               ;F-----DE--MW
		s.d f6,V6(r7)		         ;-----FD--E-----------MW		
		daddui r7,r7,8			  	  ;-----F--D-----------EMW	
		bne r7,r8,cycle                ;-------F-----------DEMW	
		l.d f1,V1(r7)		 		    ;-------F-----------DEMW
halt;						;FDEMW					 

;8+30*29=878

;fp add 4
;fp mult 8
;fp div 12