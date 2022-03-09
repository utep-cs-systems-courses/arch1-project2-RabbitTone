//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

#define NORMAL 250 //clock speed
#define FAST NORMAL / 2
#define SLOW NORMAL * 2
int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT &= ~LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);			/* CPU off, GIE on */
}

// global state vars that control blinking
int blinkLimit = 0;  // duty cycle = 1/blinkLimit
int blinkCount = 0;  // cycles 0...blinkLimit-1
int secondCount = 0; // state var representing repeating time 0…1s
int colors = 0;

void blink_RLED(){
  blinkCount ++;
  if (blinkCount >= blinkLimit) { // on for 1 interrupt period
    blinkCount = 0;
    P1OUT |= LED_RED;
  } else{	          // off for blinkLimit - 1 interrupt periods
    P1OUT &= ~LED_RED;
  }
}

void blink_GLED(){
  blinkCount ++;
  if (blinkCount >= blinkLimit) { // on for 1 interrupt period
    blinkCount = 0;
    P1OUT |= LED_GREEN;
  } else{	          // off for blinkLimit - 1 interrupt periods
    P1OUT &= ~LED_GREEN;
  }
}

void clock(){
  secondCount ++;
  if (secondCount >= FAST) {  // once each second
    secondCount = 0;
    blinkLimit ++;	     // reduce duty cycle
    if (blinkLimit >= 15){     // but don't let duty cycle go below 1/7.
      blinkLimit = 0;
      if(colors >= 1){
	colors = 0;
      }else{
	colors ++;
      }
    }
  }
}

void statemachine(){
  switch(colors){
  case 0:
    blink_GLED();
    break;
  default:
    blink_RLED();
    break;
  }
}
 
void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  // handle blinking
  statemachine();
  // measure a second
  clock();
} 

