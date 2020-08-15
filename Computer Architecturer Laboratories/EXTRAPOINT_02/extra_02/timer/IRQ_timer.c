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
#include "../dac/dac.h"


extern unsigned int interval_number;
extern unsigned int position;
extern unsigned int status_byte;
extern unsigned int speedup;
extern int block_alarm;
extern int Note1;
extern int Note2;
extern void LED_On_Proxy (unsigned int num);
extern void LED_Off_Proxy (unsigned int num);
extern void EnableTimerAlarm(int min);
void Blink5Hz();
void Blink2Hz();
void Blink4Hz();
void ResumeTimerBlink();
void PauseTimerBlink();
void StartBell(int);
unsigned int i=0;

volatile int frequency[13]={1062,1125,1192,1263,1339,1417,1502,1592,1684,1786,1890,2006,2120};
	/* k=1/f'*f/n  k=f/(f'*n) k=25MHz/(f'*45) */
				/*C: *523 Hz --> k=25M/(523*45)= 1062
				B: 494Hz --> k=25M/(494*45)= 1125
				Bb: 466 Hz --> k=25M/(466*45)= 1192
				A: 440 Hz --> k=25M/(440*45)= 1263
				Ab: 415 Hz --> k=25M/(415*45)= 1339
				G: 392 Hz --> k=25M/(392*45)= 1417
				Gb: 370 Hz --> k=25M/(370*45)= 1502
				F: 349 Hz --> k=25M/(349*45)= 1592
				E: 330 Hz --> k=25M/(330*45)= 1684
				Eb: 311 Hz --> k=25M/(311*45)= 1786
				D: 294 Hz --> k=25M/(294*45)= 1890
				Db: 277 Hz --> k=25M/(277*45)= 2006
				C: 262 Hz --> k=25M/(262*45)= 2120*/


int SinTable[]={
	154,175,196,216,235,
252,248,281,291,299,
305,307,306,302,296,
286,275,260,244,226,
206,185,164,143,122,
101,81,63,47,32,
21,11,5,1,0,2,8,16,
26,39,55,72,91,111,132
};

//timer usato per il movimento dell'ascensore
//4 Km/H=1,11 m/s
//tempo totale percorrenza = 8m / 1,11 m/s=7,2 s
//ipotizzo incremento minimo di 10 cm
// totale cicli->800cm/10cm=80
//tempo singolo periodo= 7,2s/80=0.09s
// count =0,09s * 25 Mhz=0x225510

void TIMER0_IRQHandler (void)
{
	static int ticks=0;
	if((status_byte & (1<<6))!=0){
		// se sono in stato di allarme sto utilizzando il timer 0 come sirena!!!
		static int ticks=0;
		/* DAC management */	
		DAC_convert (SinTable[ticks]<<6);
		ticks++;
		if(ticks==45) 
			ticks=0;
		
	}else{
		ResumeTimerBlink();
		if((status_byte &(1<<2))==0)
			position--;
		else
			position++;
		
		
		if(position==interval_number || position==0){
			
			reset_timer(0);
			disable_timer(0);
			
			if((status_byte &(1<<2))==0)
				status_byte &=~(1<<3);
			else
				status_byte |=(1<<3);
			
			status_byte &=~(1<<5); 	//disabilito movimento senza joystick
			status_byte &=~(1<<1); 	//ascensore fermo
		
			
			init_timer(1,0x59682f00);	/* TIMER0 Initialization   frequenza 25MHz           */
			enable_timer(1);
			//block_alarm=1;
			
			reset_timer(3);					//blocco il blinking a 2Hz nel momento in cui arrivo al piano
			PauseTimerBlink();
			
			Blink5Hz();							//avvio il blink per l'arrivo al piano
			
		}
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
		//ATTESA AL PIANO PER PERMETTERE LA DISCESA
		status_byte &=~(1<<1); 	//ascensore fermo
		status_byte &=~(1); 	 //ascensore non occupato
		status_byte &=~(1<<4);	// resetto il flag del timer di movimento
		LED_Off_Proxy(0);
		LED_Off_Proxy(2);
		LED_Off_Proxy(0);
		reset_timer(1);
		disable_timer(1);
		block_alarm=0;
	}else{
		//STATO DI ALLARME
		//block_alarm=1;
		status_byte |=(1<<6);
		LED_Off_Proxy(0);
		LED_Off_Proxy(2);
		LED_On_Proxy(1);
		LED_On_Proxy(3);
		status_byte &=~(1);
		reset_timer(3);
		Blink4Hz();
	}
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}


//timer per il movimento manuale, dopo il reset non riparte
void TIMER2_IRQHandler (void)
{
	if((status_byte & (1<<2))==0){
		//vado in basso
		if(position>0){
			position --;
			block_alarm=0;
			status_byte &=~(1<<7);		//abilito il blinking a 2Hz
			ResumeTimerBlink();
			if((status_byte & (1<<6))==0)
				EnableTimerAlarm(2);		//ogni volta che la posizione viene aggiornata resetto e faccio ripartire il timer di allarme
		}else{
			reset_timer(1);					//quando arrivo al piano disabilito il timer di allarme
			disable_timer(1);
		
			status_byte &=~(1<<3); //imposto il piano corretto
			//lancio timer attesa piano (libera l'ascensore dopo un minuto di attesa
			init_timer(1,0x59682f00);	/* TIMER0 Initialization   frequenza 25MHz           */
			enable_timer(1);
			block_alarm=1;
			reset_timer(3);
			PauseTimerBlink();
			Blink5Hz();
			LED_Off_Proxy(7);
		}
	}else{
		//vado in alto
		if(position<80){
			position ++;
			block_alarm=0;
			status_byte &=~(1<<7);		//abilito il blinking a 2Hz
			ResumeTimerBlink();
			if((status_byte & (1<<6))==0)
				EnableTimerAlarm(2);		//ogni volta che la posizione viene aggiornata resetto e faccio ripartire il timer di allarme
		}else{
			reset_timer(1);					//quando arrivo al piano disabilito il timer di allarme
			disable_timer(1);

			status_byte |=(1<<3); //imposto il piano corretto
			//lancio timer attesa piano (libera l'ascensore dopo un minuto di attesa
			init_timer(1,0x59682f00);	/* TIMER0 Initialization   frequenza 25MHz           */
			enable_timer(1);
			block_alarm=1;
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
// frequenza a 4Hz-> ogni periodo ha durata 1/8 di secondo
// c=1/8*25MHz=0x2FAF08
void TIMER3_IRQHandler (void)
{
	static int * curNote=&Note2;
	switch(i%2){
		case 1:
			LED_On_Proxy(7);
		break;
		case 0:
			LED_Off_Proxy(7);
			break;
	}
	if((status_byte & (1<<6))!=0){
		//CODICE PER LA CAMPANELLA
		reset_timer(0);
		if(*curNote==Note1)
				curNote=&Note2;
		else
				curNote=&Note1;
		StartBell(frequency[*curNote]);
	}
	i++;
	if(((status_byte & (1<<7))!=0) && i==30){ //fine dei 5 secondi
		i=0;
		status_byte &=~(1<<7);
		reset_timer(3);
		disable_timer(3);
		init_timer(3,0x5EFC68/speedup);		//per riprendere il blinkin a 2Hz se necessario
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
	enable_timer(3);
}

void Blink4Hz(){
	status_byte &=~(1<<7);		//abilito il blinking a 4Hz
	i=0;										// abiito il timer per il blinking a 5Hz
	init_timer(3,0x2FAF08/speedup);
	enable_timer(3);
}



void ResumeTimerBlink(){
	enable_timer(3);
}

void PauseTimerBlink(){
	disable_timer(3);
}

void StartBell(int freq){
	init_timer(0,freq);	/* middle A 440Hz -> k = 1263 */
	reset_timer(0);
	enable_timer(0);
}
/******************************************************************************
**                            End Of File
******************************************************************************/
