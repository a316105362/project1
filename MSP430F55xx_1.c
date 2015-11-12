//******************************************************************************
//   MSP430F552x Demo - Software Toggle P1.0
//   this is a test of  B2
//   Description: Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO~1MHz
//
//                MSP430F552x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P1.0|-->LED
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5529.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  P1DIR |= BIT0;                            // P1.0 set as output
  P8DIR |= BIT1;
  P8DIR |= BIT2;
  P1DIR = BIT0;
  P8DIR = BIT1;
  P8DIR = BIT2;
  
  while(1)                                  // continuous loop
  {
    P1OUT ^= BIT0;                          // XOR P1.0
    for(i=50000;i>0;i--);  
    P1OUT ^= BIT0;
    
    P8OUT ^= BIT1;
    
    for(i=50000;i>0;i--);
    P8OUT ^= BIT1;
   
    P8OUT ^= BIT2;
    for(i=50000;i>0;i--);
    P8OUT ^= BIT2;
  
  }
}
