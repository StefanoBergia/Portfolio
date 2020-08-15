/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../led/led.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile int down1=0;
volatile int down2=0;
extern unsigned char status_byte;
extern void MoveToFloor(char floor);
extern void ResetTimerProxy(int n);
extern void EnableTimerReposition();
extern void EnableTimerWait();
extern void Blink2Hz();
extern void ResumeTimerBlink();
extern void PauseTimerBlink();

void RIT_IRQHandler (void)
{					
	
	//	alto 			29
	//	basso 		26
	// 	sinistra 	27
	//	desta 		28
	// 	premuto 	25
	
	
	if(((LPC_GPIO1->FIOPIN & (31<<25)) ^ (31<<25)) !=0 ){		//controllo che almeno uno input del joystick sia attivo 
																													// con la and estraiamo i 5 bit corrispondent agli input
																													// con la xor verifichiamo che almeno uno sia attivo (ovvero il bit è a 0)
				
		if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
			if((status_byte & (1<<1))==0 ){			//se l'ascensore non è in movimento la pressione del joystick 
																					//è abilitata in quanto ciò significa che l'ascensore 
																					//è già fermo ad un piano
				
					ResetTimerProxy(1);							//riavvio il timer di occupato
					EnableTimerWait();
				
					Blink2Hz();											//inizializzo il timer per il blinking senza avviarlo
					LED_On(7);
				
					status_byte |=1;								//imposto il bit di occupato
					LED_On(0);
					LED_On(2);
					status_byte |=(1<<1);						//imposto il bit di movimento (il joystick non sarà più premibile)
					status_byte &=~(1<<5); 						//movimento manuale
					LED_On(7);
			}
			
		}else  if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	
			//basso
			//si muove se l'ascensore è in movimento ma non automatico!!!
			if((status_byte & (1<<1))!=0 && (status_byte & (1<<5))==0){
				status_byte |=1;								//imposto il bit di occupato
				LED_On(0);
				LED_On(2);
				if((status_byte & (1<<4))==0){
					//il timer del movimento non è attivo
					// imposto il flag del timer, il flag della direzione e lo avvio
					status_byte &=~(1<<2);
					status_byte |=(1<<4);
					
					//RESET TIMER ATTESA PIANO
					ResetTimerProxy(1);
					
					//AVVIO DEL TIMER PER IL RIPOSIZIONAMENTO
					 EnableTimerReposition();
				}
				
				//RESET TIMER ALLARME !!!!!!!!!
			}
		}else if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	
			//alto
			//si muove se l'ascensore è in movimento ma non automatico!!!
			if((status_byte & (1<<1))!=0 && (status_byte & (1<<5))==0){
				status_byte |=1;								//imposto il bit di occupato
				LED_On(0);
				LED_On(2);
				if((status_byte & (1<<4))==0){
					//il timer del movimento non è attivo
					// imposto il flag del timer, il flag della direzione e lo avvio
					status_byte |=(1<<2);
					status_byte |=(1<<4);
					
					//RESET TIMER ATTESA PIANO
					ResetTimerProxy(1);
					//AVVIO DEL TIMER PER IL RIPOSIZIONAMENTO
					 EnableTimerReposition();
				}
			}
		}
	}else if((status_byte & (1<<1))!=0 && (status_byte & (1))!=0 && (status_byte & (1<<5))==0 && (status_byte & (1<<7))==0){
			// sono fermo e non sto usando la funzione di blinking a 5Hz	
			PauseTimerBlink();
			LED_On(7);
		}else if((status_byte & (1))==0){
			LED_Off(7);
		}
	
	if(down1!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){	/* KEY1 pressed */
			down1++;				
			switch(down1){
				case 2:
					//key 1
					// piano terra
					if((status_byte & (1))== 0){
						//ascensore libero
						status_byte |=1;
						LED_On(0);
						LED_On(2);
						Blink2Hz();
						MoveToFloor(0);
					}
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			down1=1;			
			NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
		}
	}
		if(down2!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){	/* KEY2 pressed */
			down2++;				
			switch(down2){
				case 2:
					//key 2
					//primo piano
					if((status_byte & (1))== 0){
						//ascensore libero
							status_byte |=1;
							LED_On(0);
							LED_On(2);
							Blink2Hz();
							MoveToFloor(1);
					}
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			down2=1;			
			NVIC_EnableIRQ(EINT2_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
		}
	}
			
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
