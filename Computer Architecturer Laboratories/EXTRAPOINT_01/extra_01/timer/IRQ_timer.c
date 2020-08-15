/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"




extern unsigned int interval_number;
extern unsigned int position;
extern unsigned int status_byte;
extern unsigned int speedup;
extern void LED_On_Proxy (unsigned int num);
extern void LED_Off_Proxy (unsigned int num);
extern void EnableTimerAlarm(int min);
void Blink5Hz();
void Blink2Hz();
void ResumeTimerBlink();
void PauseTimerBlink();
unsigned int i=0;

//timer usato per il movimento dell'ascensore
//4 Km/H=1,11 m/s
//tempo totale percorrenza = 8m / 1,11 m/s=7,2 s
//ipotizzo incremento minimo di 10 cm
// totale cicli->800cm/10cm=80
//tempo singolo periodo= 7,2s/80=0.09s
// count =0,09s * 25 Mhz=0x225510

void TIMER0_IRQHandler (void)
{
	ResumeTimerBlink();
	if((status_byte &(1<<2))==0)
		position--;
	else
		position++;
	
	
	if(position==interval_number || position==0){
		
		reset_timer(0);
		disable_timer(0);
		
			if((status_byte & (1<<6))!=0){ 		//se ero precedentemente in uno stato di allarme, lo disattivo e torno in stato normale
				LED_Off_Proxy(1);
				LED_Off_Proxy(3);
				status_byte &=~(1<<6);
			}
		
		if((status_byte &(1<<2))==0)
			status_byte &=~(1<<3);
		else
			status_byte |=(1<<3);
		
		status_byte &=~(1<<5); 	//disabilito movimento senza joystick
		status_byte &=~(1<<1); 	//ascensore fermo
	
		
		init_timer(1,0x59682f00);	/* TIMER0 Initialization   frequenza 25MHz           */
		enable_timer(1);
		
		
		reset_timer(3);					//blocco il blinking a 2Hz nel momento in cui arrivo al piano
		PauseTimerBlink();
		
		Blink5Hz();							//avvio il blink per l'arrivo al piano
		
	}
	
	LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}



//timer con singolo interrupt
//usato per l'attesa di 1 minuto quando l'ascensore è occupato e fermo ad un piano
// 60s * 25 Mhz=0x59682f00
// usato anche come timer per rilevare la situazione di allarme
void TIMER1_IRQHandler (void)
{
	if(position==0 || position==interval_number){
		status_byte &=~(1<<1); 	//ascensore fermo
		status_byte &=~(1); 	 //ascensore non occupato
		status_byte &=~(1<<4);	// resetto il flag del timer di movimento
		LED_Off_Proxy(0);
		LED_Off_Proxy(2);
		LED_Off_Proxy(0);
		reset_timer(1);
		disable_timer(1);
	}else{
		//STATO DI ALLARME
		status_byte |=(1<<6);
		LED_Off_Proxy(0);
		LED_Off_Proxy(2);
		LED_On_Proxy(1);
		LED_On_Proxy(3);
		status_byte &=~(1);
	}
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}


//timer per il movimento manuae, dopo il reset non riparte
void TIMER2_IRQHandler (void)
{
	if((status_byte & (1<<2))==0){
		//vado in basso
		if(position>0){
			position --;
			ResumeTimerBlink();
			if((status_byte & (1<<6))==0)
				EnableTimerAlarm(2);		//ogni volta che la posizione viene aggiornata resetto e faccio ripartire il timer di allarme
		}else{
			reset_timer(1);					//quando arrivo al piano disabilito il timer di allarme
			disable_timer(1);
			if((status_byte & (1<<6))!=0){ 		//se ero precedentemente in uno stato di allarme, lo disattivo e torno in stato normale
				LED_Off_Proxy(1);
				LED_Off_Proxy(3);
				status_byte &=~(1<<6);
			}
			status_byte &=~(1<<3); //imposto il piano corretto
			//lancio timer attesa piano (libera l'ascensore dopo un minuto di attesa
			init_timer(1,0x59682f00);	/* TIMER0 Initialization   frequenza 25MHz           */
			enable_timer(1);
			
			reset_timer(3);
			PauseTimerBlink();
			Blink5Hz();
			LED_Off_Proxy(7);
		}
	}else{
		//vado in alto
		if(position<80){
			position ++;
			ResumeTimerBlink();
			if((status_byte & (1<<6))==0)
				EnableTimerAlarm(2);		//ogni volta che la posizione viene aggiornata resetto e faccio ripartire il timer di allarme
		}else{
			reset_timer(1);					//quando arrivo al piano disabilito il timer di allarme
			disable_timer(1);
			
			if((status_byte & (1<<6))!=0){ 	//se ero precedentemente in uno stato di allarme, lo disattivo e torno in stato normale
				LED_Off_Proxy(1);
				LED_Off_Proxy(3);
				status_byte &=~(1<<6);
			}
			status_byte |=(1<<3); //imposto il piano corretto
			//lancio timer attesa piano (libera l'ascensore dopo un minuto di attesa
			init_timer(1,0x59682f00);	/* TIMER0 Initialization   frequenza 25MHz           */
			enable_timer(1);
			
			reset_timer(3);
			PauseTimerBlink();
			
			Blink5Hz();
		}
	}
	status_byte &=~(1<<4);	// resetto il flag del timer di movimento
	reset_timer(2);
	disable_timer(2);				//diabilito il timer di movimento
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}

//timer per la gestione del blinking
//frequenza a 5 HZ-> ogni periodo ha durata 1/10 s
// 3 s -> 30 cicli totali 
// count da dare al timer->1/10s*25 mhz=0x2625A0
// frequenza a 2Hz->ogni periodo ha durata di un quarto di secondo
// c=0,25*25Mhz=0x5EFC68
void TIMER3_IRQHandler (void)
{
	switch(i%2){
		case 1:
			LED_On_Proxy(7);
		break;
		case 0:
			LED_Off_Proxy(7);
			break;
	}
	i++;
	if(((status_byte & (1<<7))!=0) && i==30){ //fine dei 5 secondi
		i=0;
		status_byte &=~(1<<7);
		reset_timer(3);
		disable_timer(3);
		LED_Off_Proxy(7);
	}
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}

void Blink5Hz(){
	status_byte |=(1<<7);		//abilito il blinking a 5Hz
	i=0;										// abiito il timer per il blinking a 5Hz
	init_timer(3,0x2625A0/speedup);
	enable_timer(3);
}

void Blink2Hz(){
	status_byte &=~(1<<7);		//abilito il blinking a 2Hz
	i=0;										// abiito il timer per il blinking a 5Hz
	init_timer(3,0x5EFC68/speedup);
}

void ResumeTimerBlink(){
	enable_timer(3);
}

void PauseTimerBlink(){
	disable_timer(3);
}
/******************************************************************************
**                            End Of File
******************************************************************************/
