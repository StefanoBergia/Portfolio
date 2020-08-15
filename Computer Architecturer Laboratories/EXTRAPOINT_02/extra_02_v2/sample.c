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
#include "adc/adc.h"
#include "dac/dac.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"

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
	7->1 per blinking a 5Hz, 0 per blinking a 2Hz 0 4Hz
*/

unsigned int position;
unsigned int interval_number=80 ; //numero di intervalli (80 intervalli = step di 10 cm)
unsigned int speedup =1;					//accelerazione velocità di movimento
unsigned int maintenance=0;				//per accedere al pannello di manutenzione
int Note1;
int Note2;
extern int tmpNote1;
extern int tmpNote2;
extern int sel;
void MoveToFloor(char floor);
void ResetTimerProxy(int n);
void LED_On_Proxy (unsigned int num);
void LED_Off_Proxy (unsigned int num);
void EnableTimerReposition();
void EnableTimerWait();
void EnableTimerAlarm(int min);
void DrawPanel(int);
void FocusElement(int,int);
void DrawPanelMaintenance();

volatile char * labels[] ={"523Hz - C    ","494Hz - B   ","466 Hz - Bb  ","440Hz - A    ","415Hz - Ab   ","392Hz - G    ",
														"370 Hz - Gb  ","349 Hz - F   ","330Hz - E    ","311Hz - Eb   ","294Hz - D    ","277Hz - Db   ","262Hz - C    "};

extern int block_alarm;

int main (void) {
	
  status_byte=0;									
	position=0;
	block_alarm=1;
	SystemInit();  												/* System Initialization (i.e., PLL)  */
  LED_init();                           /* LED Initialization                 */
  BUTTON_init();												/* BUTTON Initialization              */
	joystick_init();											/* Joystick Initialization            */
	init_RIT(0x4C4B40);									  /* RIT Initialization 200 msec a25 Mhz, 50 ms a 100Mhz      	*/
	//init_RIT(0x1312D0);
	enable_RIT();													/* RIT enabled												*/
	ADC_init();	
	DAC_init();														/* DAC Initialization	  							*/
	LCD_Initialization();
	
	Note1=3;
	Note2=3;
	tmpNote1=3;
	tmpNote2=3;
	sel=-1;
	
	TP_Init();
	TouchPanel_Calibrate();
	DrawPanelMaintenance();
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
		
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
  }

}

void MoveToFloor(char floor){
	/*if((status_byte&(1<<6))!=0){ //se sono in una situazione di allarme mi assicuro che i pulsanti siano ablitati
		if(floor==1)						
			status_byte &=~(1<<3);
		else if (floor==0)
			status_byte |=(1<<3);
	}*/
	block_alarm=1;
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

void DrawPanelMaintenance(){
	int x0,y0;
	LCD_Clear(Black);
	x0=180;
	y0=20;
	LCD_DrawLine( x0, y0, x0, y0+50 , White);
	LCD_DrawLine(x0,y0+50,x0+50,y0+50,White);
	LCD_DrawLine( x0+50, y0+50, x0+50, y0 , White );
	LCD_DrawLine( x0+50,y0, x0,y0 , White );
	
	LCD_DrawLine( x0+10, y0+10, x0+10, y0+10+30 , White);
	LCD_DrawLine(x0+10,y0+10+30,x0+10+30,y0+10+30,White);
	LCD_DrawLine( x0+10+30, y0+10+30, x0+10+30, y0+10 , White );
	
	LCD_DrawLine( x0+25, y0+10, x0+25, y0+30 , White );
	
	LCD_DrawLine( x0+10, y0+10, x0+10+5, y0+10 , White);
	LCD_DrawLine( x0+10+30, y0+10, x0+10+25, y0+10 , White);
	LED_Out(0);
}

void DrawPanel(int pressed){
	LCD_Clear(Blue);
	GUI_Text(80, 20, (uint8_t *) "Maintenance", Yellow, Blue);
	
	if(pressed==1){
		GUI_Text(70, 80, (uint8_t *) "Select note 1", Blue, White);
		GUI_Text(70, 120, (uint8_t *) labels[Note1], Blue, White);
	}else{
		GUI_Text(70, 80, (uint8_t *) "Select note 1", White, Blue);
		GUI_Text(70, 120, (uint8_t *) labels[Note1], White, Blue);
	}
	
	
	LCD_DrawLine( 30, 150, 210, 150 , White );
	
	if(pressed==2){
		GUI_Text(70, 170, (uint8_t *) "Select note 2", Blue, White);
		GUI_Text(70, 210, (uint8_t *) labels[Note2], Blue, White);
	}else{
		GUI_Text(70, 170, (uint8_t *) "Select note 2", White, Blue);
		GUI_Text(70, 210, (uint8_t *) labels[Note2], White, Blue);
	}
	
	if(pressed==3){
		GUI_Text(20, 270, (uint8_t *) "      ", Green, White);
		GUI_Text(20, 290, (uint8_t *) "      ", Green, White);
		GUI_Text(20, 280, (uint8_t *) " SAVE ", Green, White);

	}else{
		GUI_Text(20, 270, (uint8_t *) "      ", White, Green);
		GUI_Text(20, 290, (uint8_t *) "      ", White, Green);
		GUI_Text(20, 280, (uint8_t *) " SAVE ", White, Green);
	}
	
	if (pressed==4){
		GUI_Text(180, 270, (uint8_t *) "      ", Red, White);
		GUI_Text(180, 290, (uint8_t *) "      ", Red, White);
		GUI_Text(180, 280, (uint8_t *)" QUIT ", Red, White );
	}else{
		GUI_Text(180, 270, (uint8_t *) "      ", White, Red);
		GUI_Text(180, 290, (uint8_t *) "      ", White, Red);
		GUI_Text(180, 280, (uint8_t *)" QUIT ", White, Red );
	}
	LED_Out(0);
}

void FocusElement(int pressed,int note){
	if(pressed==1){
		GUI_Text(70, 80, (uint8_t *) "Select note 1", Blue, White);
		GUI_Text(70, 120, (uint8_t *) labels[note], Blue, White);
	}else if (pressed==-1){
		GUI_Text(70, 80, (uint8_t *) "Select note 1", White, Blue);
		GUI_Text(70, 120, (uint8_t *) labels[note], White, Blue);
	}else if(pressed==2){
		GUI_Text(70, 170, (uint8_t *) "Select note 2", Blue, White);
		GUI_Text(70, 210, (uint8_t *) labels[note], Blue, White);
	}else  if(pressed==-2) {
		GUI_Text(70, 170, (uint8_t *) "Select note 2", White, Blue);
		GUI_Text(70, 210, (uint8_t *) labels[note], White, Blue);
	}else if(pressed==3){
		GUI_Text(20, 270, (uint8_t *) "      ", Green, White);
		GUI_Text(20, 290, (uint8_t *) "      ", Green, White);
		GUI_Text(20, 280, (uint8_t *) " SAVE ", Green, White);
	}else if  (pressed==-3){
		GUI_Text(20, 270, (uint8_t *) "      ", White, Green);
		GUI_Text(20, 290, (uint8_t *) "      ", White, Green);
		GUI_Text(20, 280, (uint8_t *) " SAVE ", White, Green);
	}else if (pressed==4){
		GUI_Text(180, 270, (uint8_t *) "      ", Red, White);
		GUI_Text(180, 290, (uint8_t *) "      ", Red, White);
		GUI_Text(180, 280, (uint8_t *)" QUIT ", Red, White );
	}else  if(pressed==-4){
		GUI_Text(180, 270, (uint8_t *) "      ", White, Red);
		GUI_Text(180, 290, (uint8_t *) "      ", White, Red);
		GUI_Text(180, 280, (uint8_t *)" QUIT ", White, Red );
	}
	LED_Out(0);
}