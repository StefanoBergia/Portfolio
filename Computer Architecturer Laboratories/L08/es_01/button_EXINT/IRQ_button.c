#include "button.h"
#include "lpc17xx.h"

#include "../led/led.h"


void Show_Led(char val){
	int i=0;
	char mask=1;
	char led;
	for(i=0;i<8;i++){
		led=val & mask;
		if(led!=0){
			LED_On(i);
		}else
			LED_Off(i);
		mask= mask<<1;
	}
}


void EINT0_IRQHandler (void)	  
{
	//pulsante a destra
	//reset count
	
	Set_Led_value(0);
	Show_Led(0);
	
  LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  
{
	//pulsante a sinistra
	// incremento
	
	Inc_Led_value();
	Show_Led(Get_Led_value());
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  
{
	//pusante centrale
	//decremento
	
	Dec_Led_value();
	Show_Led(Get_Led_value());
	
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


