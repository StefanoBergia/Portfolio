/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: to control led through EINT and joystick buttons
 * Note(s):
 *----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include <stdio.h>
#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "led/led.h"
#include "button_EXINT/button.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
 
unsigned char status_byte;

/*
	significato bit di status_byte
	0->1 per ascensore occupato, 0 per ascensore libero
	1->1 per ascensore a metà strada tra i piani, 0 per ascensore fermo ad un piano
	2->1 se l'ascensore sta andando verso l'alto, 0 se sta andando verso il basso (ha significato solo se il bit precedente vale 1)
	3->1 ascensore al primo piano, 0 ascensore al piano terra (ha significaato solo se il secondo bit vale 0)
	4->1 timer spostamento manuale abilitato, 0 se disabilitato
	5->1 l'ascensore si sta muovendo in maniera autonoma, 0 ascensore controllato da joystick
	6->1 stato di allarme
	7->1 per blinking a 5Hz, 0 per blinking a 2Hz
*/

unsigned int position;
unsigned int interval_number=80 ; //numero di intervalli (80 intervalli = step di 10 cm)
unsigned int speedup =1;					//accelerazione velocità di movimento
void MoveToFloor(char floor);
void ResetTimerProxy(int n);
void LED_On_Proxy (unsigned int num);
void LED_Off_Proxy (unsigned int num);
void EnableTimerReposition();
void EnableTimerWait();
void EnableTimerAlarm(int min);


int main (void) {
	
  status_byte=0;									
	position=0;
	SystemInit();  												/* System Initialization (i.e., PLL)  */
  LED_init();                           /* LED Initialization                 */
  BUTTON_init();												/* BUTTON Initialization              */
	joystick_init();											/* Joystick Initialization            */
	init_RIT(0x4C4B40);									  /* RIT Initialization 50 msec       	*/
	enable_RIT();													/* RIT enabled												*/
	
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
		
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
  }

}

void MoveToFloor(char floor){
	if((status_byte&(1<<6))!=0){ //se sono in una situazione di allarme mi assicuro che i pulsanti siano ablitati
		if(floor==1)						
			status_byte &=~(1<<3);
		else if (floor==0)
			status_byte |=(1<<3);
	}
	if( ((status_byte &(1<<3))!= (floor<<3))){	
		//se l'ascensore è dalla parte opposta 
		
		status_byte |=(1<<5); 	//movimento senza joystick
		status_byte |=(1<<1); 	//ascensore in movimento
		
		if(floor==1)						// imposto la direzione del senso di marcia dell'ascensore (uguale al piano a cui sto andando)
			status_byte |=(1<<2);
		else if (floor==0)
			status_byte &=~(1<<2);
		
		init_timer(0,0x225510/speedup);							/* TIMER0 Initialization   frequenza 25MHz           */
		enable_timer(0);
	}else{
		status_byte &=~(1<<1); 	//ascenzore non in movimento, joystick attivo
		
		init_timer(1,0x59682f00);	/* TIMER0 Initialization   frequenza 25MHz           */
		enable_timer(1);
	}
	
}

void ResetTimerProxy(int n){
	reset_timer(n);
	disable_timer(n);
	//init_timer(1,0x17D7840);
	//enable_timer(n);
}

void LED_On_Proxy (unsigned int num){
	LED_On(num);
}
void LED_Off_Proxy (unsigned int num){
	LED_Off(num);
}

void EnableTimerReposition(){
	init_timer(2,0x225510/speedup);
	enable_timer(2);
}

void EnableTimerWait(){
	reset_timer(1); ///////////////
	init_timer(1,0x59682f00); //speddup 0x17D7840
	enable_timer(1);
}

void EnableTimerAlarm(int min){
	ResetTimerProxy(1);
	init_timer(1,0x59682f00*min);
	enable_timer(1);
}