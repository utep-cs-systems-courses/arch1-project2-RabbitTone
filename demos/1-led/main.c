//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

//void one_min_delay();

int main(void) {
  P1DIR |= LEDS;   //set both LEDS
  P1OUT |= (LED_GREEN | LED_RED);   //turn on GREEN & RED LED
  P1OUT &= ~(LED_GREEN | LED_RED);  //turn off GREEN & RED LED
  
  or_sr(0x18);		/* CPU off, GIE on */
}
/*
Void one_min_delay(){
  __delay_cycles(2500000); //2.5 seconds
  __delay_cycles(2500000);
  __delay_cycles(2500000);
  __delay_cycles(2500000);
}
*/

void fliker(){
  while(1){
    P1OUT ^= (LED_GREEN | LED_RED);
    __delay_cycles(250000);
  }
}
