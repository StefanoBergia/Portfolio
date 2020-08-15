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
volatile int down0=0;
volatile int down0_supp=0;
volatile unsigned int count_2s=0;
extern int Note1;
extern int Note2;
extern unsigned char status_byte;
extern void MoveToFloor(char floor);
extern void ResetTimerProxy(int n);
extern void EnableTimerReposition();
extern void EnableTimerWait();
extern void Blink2Hz();
extern void Blink4Hz();
extern void ResumeTimerBlink();
extern void PauseTimerBlink();
extern void EnableTimerAlarm(int );
extern int block_alarm;
void StartBell(int);





void RIT_IRQHandler (void)
{					
	//static int count_2s=0;			//attesa 2s per pulsante di emergenza
	//static int toggle_bell=0;		//per cambiamento nota della campanella
	//static int * curNote=&Note1;
	
	//	alto 			29
	//	basso 		26
	// 	sinistra 	27
	//	desta 		28
	// 	premuto 	25
	
	
	if(((LPC_GPIO1->FIOPIN & (31<<25)) ^ (31<<25)) !=0 ){		//controllo che almeno uno input del joystick sia attivo 
																													// con la and estraiamo i 5 bit corrispondent agli input
																													// con la xor verifichiamo che almeno uno sia attivo (ovvero il bit è a 0)
				
		if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
			
			//INSERITO BLOCCO IN CASO DI EMERGENZA
			//INSERITO CONTROLLO DI OCCUPATO
			
			if((status_byte & (1<<1))==0 && (status_byte & (1))==0 &&  (status_byte & (1<<6))==0 ){			
																						//se l'ascensore non è in movimento la pressione del joystick 
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
				
					block_alarm=0;
			}
			
		}else  if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	
			//basso
			//si muove se l'ascensore è in movimento ma non automatico!!! (e non si è in stato di emergenza)
			if((status_byte & (1<<1))!=0 && (status_byte & (1<<5))==0 &&(status_byte & (1<<6))==0 && (status_byte & (1<<7))==0){
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
			//si muove se l'ascensore è in movimento ma non automatico!!! (e non si è in stato di emergenza) (e non sto facndo il blinkin a 5 Hz)
			if((status_byte & (1<<1))!=0 && (status_byte & (1<<5))==0 && (status_byte & (1<<6))==0 && (status_byte & (1<<7))==0){
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
	}else if((status_byte & (1<<1))!=0 && (status_byte & (1))!=0 && (status_byte & (1<<5))==0 && (status_byte & (1<<7))==0 && (status_byte & (1<<6))==0){
			// sono fermo e non sto usando la funzione di blinking a 5Hz e non sono in emergenza	
			PauseTimerBlink();
			LED_On(7);
		}else if((status_byte & (1))==0 && (status_byte &(1<<6))==0){
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
						
						//disattivo stato di allame e disabilito la sirena!!!
						if((status_byte & (1<<6))!=0){
							status_byte &=~(1<<6);
							status_byte |=(1<<3);
							ResetTimerProxy(0);
							ResetTimerProxy(3);
							LED_Off(1);
							LED_Off(3);
						
						}
						
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
							
						
						
						
							//disattivo stato di allame e disabilito la sirena!!!
							if((status_byte & (1<<6))!=0){
							status_byte &=~(1<<6);
							status_byte &=~(1<<3);
							ResetTimerProxy(0);
							ResetTimerProxy(3);
								
							LED_Off(1);
							LED_Off(3);
						
						}
						
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
		
	//pulsante 0
		if(down0!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){	/* KEY1 pressed */
			if(down0_supp==0)
			{
				count_2s=0;
			}
			down0_supp=1;
			count_2s++;					//incremento contatore di attesa 2s		
			
			//gestione manuale allarme
			ResetTimerProxy(1);	//disabilito il timer dell'allarme
			if((status_byte & (1))==0 && (status_byte & (1<<6))!=0 && count_2s<=1){
				//annullamento allarme
				ResetTimerProxy(0);			//blocco il movimento automatico
				status_byte |=(1);
				LED_Off(1);
				LED_Off(3);
				LED_On(0);
				LED_On(2);
				status_byte &=~(1<<6);
				ResetTimerProxy(3);			//diabilito blinkin
				LED_On(7);
				EnableTimerAlarm(2); 		//riabilito il timer di allarme
			}
			
			else if(count_2s==1){
				status_byte |=(1<<6);		//imposto il flag di allarme			
				LED_On(1);
				LED_On(3);
				Blink4Hz();
			}
			else if(count_2s==40){
				status_byte &=~(1);			//solo dopo che passano 2 secondi entro ufficialmente in stato di allarme, rendendo l'ascensore richiamabile
				LED_Off(0);
				LED_Off(2);
			
			}
		}
		else {	/* button released */
			down0=0;
			down0_supp=0;
			if(count_2s<40 && (status_byte & (1<<6))!=0 ){
				status_byte |=(1);
				status_byte &=~(1<<6);
				LED_On(0);
				LED_On(2);
				LED_Off(1);
				LED_Off(3);			
				ResetTimerProxy(3);
				ResetTimerProxy(0);
				LED_Off(7);
				EnableTimerAlarm(2);//riabilito il timer dell'allarme		
				count_2s=0;
			}	
			NVIC_EnableIRQ(EINT0_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
		}
	}
	
	/*if((status_byte & (1<<6))!=0){ //ogni volta che sono in stato di allarme faccio partire la cmpanella
		//CODICE PER LA CAMPANELLA
		toggle_bell++;
		if(toggle_bell==1){  							//inizio campanella
			StartBell(frequency[*curNote]);
		}else if (toggle_bell==3){				//cambio nota ogni ottavo di secondo
			ResetTimerProxy(0);
			toggle_bell=1;
			if(*curNote==Note1)
				curNote=&Note2;
			else
				curNote=&Note1;
			StartBell(frequency[*curNote]);
		}
		
		
	}*/
			
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
