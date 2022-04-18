#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "notes.h"

int oct3[] = {C3, CsDf3, D3, DsEf3, E3, F3, FsGf3, G3, GsAf3, A3, AsBf3, B3};

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES SW1 | SW2 | SW3 | SW4

int main() {
    configureClocks();
    buzzer_init();

    P2REN |= SWITCHES;
    P2IE |= SWITCHES;
    P2OUT |= SWITCHES;
    P2DIR &= ~SWITCHES;

   
    // enableWDTInterrupts();
    /*
    for(int n = 1; n < 12; n++)
      buzzer_set_period(notes[n]);	/* start buzzing!!! 2MHz/1000 = 2kHz*/
    
    or_sr(0x18); // CPU off, GIE on
}

int secondCount = 0;
int n = 0;
static int curr_note = 0;

void
buzz_rising(){
  /*  secondCount++;
  if(secondCount >= 125){
    secondCount = 0;
    buzzer_set_period(oct3[p]);
  }*/
  //  static curr_note = 0;
  if(curr_note < 12){
    buzzer_set_period(oct3[curr_note]);
    curr_note++;
  }else{
    curr_note = 0;
  }
  //buzzer_set_period(oct3[p]);
}

void
buzz_descend(){
  if(curr_note >= 0){
    buzzer_set_period(oct3[curr_note]);
    curr_note--;
  }else{
    curr_note = 11;
  }
}

void
switch_handler(){
  char p2val = P2IN;

  P2IES |= (p2val & SWITCHES); /* senses switch is pressed */
  P2IES &= (p2val | ~SWITCHES); /* senses switch is not pressed */
  
  if(p2val & SW1){
    buzz_rising();
  }
  if(p2val & SW2){
    buzz_descend();
  }
}

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES){
    P2IFG &= ~SWITCHES;
    switch_handler();
  }
}
