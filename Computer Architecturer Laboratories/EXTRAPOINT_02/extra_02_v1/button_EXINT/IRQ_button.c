#include "button.h"
#include "lpc17xx.h"

extern int down1;
extern int down2;
extern int down0;
extern unsigned char status_byte;

volatile int block_alarm;

void EINT0_IRQHandler (void)	  	/* INT0														 */
{		
	//pulsante a destra
	//allarme manuale
	//
	
	if(!block_alarm){
		NVIC_DisableIRQ(EINT0_IRQn);		/* disable Button interrupts			 */
		LPC_PINCON->PINSEL4    &= ~(1 << 20);     /* GPIO pin selection */
		down0=1;
		LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
	}
}

void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	//pulsante a sinistra
	//request floor 1
	//bit piano a 0
	
	NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
	down1=1;
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	//pusante in centro
	//request floor 2
	// bit piano a 1
	
	NVIC_DisableIRQ(EINT2_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 24);     /* GPIO pin selection */
	down2=1;
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


