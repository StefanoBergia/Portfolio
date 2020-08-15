; Architetture dei Sistemi di Elaborazione - Laboratorio 03	;
; author: 		Stefano Bergia - 276124           			;
; creation: 	27 October 2019								;
; last update:  27 October 2019								;

.data
V1:	.double 	1.62,3.06,8.12,8.75,2.21,7.26,7.82,2.40,2.78,0.54,3.97,0.56,2.44,5.47,8.07,1.10,5.90,7.56,4.50,0.49,1.86,1.88,4.33,2.44,2.05,2.08,2.08,8.15,5.29,4.85				
V2:	.double 	3.67,3.26,1.84,5.20,6.29,9.72,9.23,0.68,0.47,5.80,4.61,5.28,7.68,7.58,5.16,4.50,9.97,4.94,0.50,0.32,3.35,8.58,2.18,7.74,2.98,9.10,5.35,8.46,2.69,8.38
V3: .double		5.31,6.98,0.10,4.54,1.84,7.71,0.58,3.55,0.61,0.81,8.39,6.43,0.36,6.63,6.63,7.56,6.65,4.24,0.04,2.13,1.76,8.27,1.00,6.20,9.57,8.88,6.58,1.59,1.05,0.99			
V4: .double		6.51,1.12,3.86,4.42,2.63,1.09,3.16,5.00,8.63,4.17,2.49,5.24,5.88,6.55,7.42,9.53,0.00,0.45,4.48,9.03,0.40,0.87,6.76,7.91,0.04,9.36,6.69,1.51,7.22,9.73

V5:	.space	240 	;30*8 byte	
V6:	.space 	240		
		

.text         						;segnala all'asseblatore l'inizio del codice

start:	
		daddui	r1,r1,0	   ;FDEMW  																1
		daddui	r2,r2,8	    ;FDEMW 																2
		daddui	r3,r3,16	 ;FDEMW 															3
		
		daddui   r8,r8,216    ;FDEMW 

cycle:						 
		l.d f1,V1(r1)		   ;FDEMW 					      									1	  
		l.d f2,V2(r1)	        ;FDEMW	  				      									1
		l.d f3,V3(r1)			 ;FDEMW				      									    1
		mul.d f5,f1,f2		      ;FDEEEEEEEEMW			      									1
		l.d f4,V4(r1)	           ;FDEMW				      									1
		
		l.d f11,V1(r2)		        ;FDEMW			          									2
		l.d f12,V2(r2)		         ;FDEMW				      									2
		l.d f13,V3(r2)		          ;FDEMW			      									2
		mul.d f15,f11,f12		       ;FDEEEEEEEEMW          									2
		l.d f14,V3(r2)		            ;FDEMW			      									2

		l.d f21,V1(r3)		             ;FDEMW			      									3
		
		add.d  f5,f5,f3                   ;FDEEEEEEMW	      									1		
		mul.d  f6,f3,f4                    ;FDEEEEEEEEMW      									1
		
		l.d f22,V2(r3)		                ;FDEMW                   							3
		l.d f23,V3(r3)					     ;FDEMW                  							3
		mul.d f16,f13,f14					  ;FDEEEEEEEEMW          							2
		mul.d f25,f21,f22		               ;FDEEEEEEEEMW         							3 
		l.d f24,V4(r3)						    ;FDEMW               							3
		mul.d f26,f23,f24						 ;FDEEEEEEEEMW       							3
		add.d  f15,f15,f13                        ;FDEEEEEEMW        							2
		
		div.d f6,f6,f5							   ;FDEEEEEEEEEEEEMW 							1
		add.d  f25,f25,f23						    ;FDE---EEEEEMW      						3	
		
		
		div.d f16,f16,f15							 ;FD----------EEEEEEEEEEEEMW 				2
		
		s.d f5,V5(r1)             					  ;F----------DEMW							1
		s.d f6,V6(r1)		          				   ;----------FDEMW							1
		daddui r1,r1,24									;----------FDEMW						1
		s.d f15,V5(r2)									 ;----------FDEMW						2
		s.d f25,V5(r2) 									  ;----------FDEMW						3
		
		div.d f26,f26,f25							       ;----------FD------EEEEEEEEEEEEMW 	3
											             
		s.d f16,V6(r2)										;----------F------DEMW		        2 	
		daddui r2,r2,24										 ;----------------FDEMW				2
		              
		s.d f26,V6(r3)		          						  ;----------------FDE---------MW	3
		daddui r3,r3,24										   ;----------------FD---------EMW   3
		
		bne r1,r8,cycle                 						;----------------F---------DEMW	
		
halt 							 

;8+54*10=548

;fp add 4
;fp mult 8
;fp div 12