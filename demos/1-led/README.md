## Description
This program turns on the red led

Be sure to understand the manipulation of P1OUT and P1DIR.

## Suggested Activities

* Modify so that different combinations of LEDs are illuminated.
  Made a loop that switches between LED_GREEN and LED_RED on a delay cycle of
  0.25 seconds
* Determine the impact of not setting one of the LED bits in P1DIR (and why). 
  Not setting the either both or one of the LED bits in P1DIR will not allow
  for their use regardless of P1OUT
