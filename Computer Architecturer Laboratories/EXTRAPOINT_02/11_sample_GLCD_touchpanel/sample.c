/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "button_EXINT/button.h"
#include "RIT/RIT.h"
#include "adc/adc.h"
#include "dac/dac.h"

void DrawPanel(int);
void FocusElement(int,int);
void DrawPanelMaintenance();

volatile int Note1;
volatile int Note2;
extern int sel;
extern int tmpNote1;
extern int tmpNote2;
volatile int maintenance;

volatile char * labels[] ={"523Hz - C    ","494Hz - B   ","466 Hz - Bb  ","440Hz - A    ","415Hz - Ab   ","392Hz - G    ",
														"370 Hz - Gb  ","349 Hz - F   ","330Hz - E    ","311Hz - Eb   ","294Hz - D    ","277Hz - Db   ","262Hz - C    "};

int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	BUTTON_init();												/* BUTTON Initialization              */
	init_RIT(0x004C4B40);									/* RIT Initialization 50 msec       	*/
	enable_RIT();													/* RIT enabled												*/
	ADC_init();														/* ADC Initialization									*/
	DAC_init();														/* DAC Initialization	  							*/
  LCD_Initialization();

	maintenance=0;
  Note1=3;
	Note2=3;
	tmpNote1=3;
	tmpNote2=3;
	sel=-1;
	
	TP_Init();
	TouchPanel_Calibrate();
	DrawPanelMaintenance();
	//DrawPanel(0);
	
	init_timer(0, 0x1312D0 ); 						/* 50ms * 25MHz = 1.25*10^6 = 0x1312D0 */
	//init_timer(0, 0x6108 ); 						  /* 1ms * 25MHz = 25*10^3 = 0x6108 */
	//init_timer(0, 0x4E2 ); 						    /* 500us * 25MHz = 1.25*10^3 = 0x4E2 */

	enable_timer(0);
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	
  {
		__ASM("wfi");
  }
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
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
