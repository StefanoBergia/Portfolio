/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include <stdio.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../dac/dac.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern void DrawPanel(int);
extern void FocusElement(int, int);
extern void DrawPanelMaintenance();
extern int Note1;
extern int Note2;
extern int maintenance;

int sel;
int tmpNote1;
int tmpNote2;

int SinTable[]={
	170, 204, 236, 265, 291,
312, 328, 337, 341, 337,
328, 312, 291, 265, 236,
204, 170, 137, 105, 76,
50, 29, 13, 3, 0,
3, 13, 29, 50, 76,
105, 137
};

void TIMER0_IRQHandler (void)
{
	char sup[30];
	static int pressed=0;
	static int hold=0;
	static int delay=0;
	
	getDisplayPoint(&display, Read_Ads7846(), &matrix ) ;
	
	if (maintenance==0){
		if(display.x >= 180 && display.x <=230 && display.y>=20 && display.y<=70 ){
			maintenance=1;
			DrawPanel(0);
		}
	}
	else if(maintenance==1){

		if(delay==1){
			hold++;
		}
		
		if(hold==5){
			FocusElement(-3,-1);
			FocusElement(-4,-1);
			hold=0;
			delay=0;
			pressed=0;
		}
		
			if(display.x <= 240 && display.x > 0 ){
				
				
				//sprintf(sup,"%d,%d",display.x,display.y);
				//GUI_Text(180, 0, (uint8_t *) "       ", White, Blue);
				//GUI_Text(180, 0, (uint8_t *) sup, Red, Black);
				
				if(display.x >= 30 && display.x<=150 && display.y>=50 && display.y<=150 ){
					//nota 1
					if(pressed!=1)
						FocusElement(-2,tmpNote2);
					pressed=1;
					FocusElement(1,tmpNote1);
					sel=1;
					
				}else if (display.x >= 30 && display.x<=150 && display.y>=150 && display.y<=200 ){
					//nota 2
					if(pressed!=2)
						FocusElement(-1,tmpNote1);
					pressed=2;
					FocusElement(2,tmpNote2);
					sel=2;
				} else if (display.x >= 20 && display.x<=70 && display.y>=270 && display.y<=300 ){
					//save
					pressed=3;
					delay=1;
					FocusElement(3,-1);
					Note1=tmpNote1;
					Note2=tmpNote2;
				}else if (display.x >= 180 && display.x<=230 && display.y>=270 && display.y<=300 ){
					// quit
					maintenance=0;
					pressed=4;
					FocusElement(4,-1);
					DrawPanelMaintenance();
					delay=1;
					sel=-1;
				}
			}
		else{
		}
	}
	//
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	
	static int ticks=0;
	/* DAC management */	
	DAC_convert (SinTable[ticks]<<6);
	ticks++;
	if(ticks==32) 
		ticks=0;
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
