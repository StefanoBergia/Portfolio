/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "../timer/timer.h"

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/

unsigned short AD_current;   
unsigned short AD_last = 0xFF;     /* Last converted value               */
extern int sel;
extern int tmpNote1;
extern int tmpNote2;
extern int maintenance;
extern void FocusElement(int,int);

void ADC_IRQHandler(void) {
  	
  AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);/* Read Conversion Result             */
	AD_current=AD_current*12/0xFFF;
  if(AD_current != AD_last && maintenance==1){

		AD_last = AD_current; 		//recupero la posizione del potenziometro
		
		if(sel==1){
			tmpNote1=AD_current;
			FocusElement(1,tmpNote1);
		}
		else if(sel==2){
			tmpNote2=AD_current;
			FocusElement(2,tmpNote2);
		}	
  }
	
}
