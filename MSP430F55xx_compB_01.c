//******************************************************************************
// MSP430x552x Demo - COMPB output Toggle in LPM4; Vcompare is compared against
//                    the internal 2.0V reference
//C
// Description: Use CompB and internal reference to determine if input'Vcompare'
//    is high of low.  When Vcompare exceeds 2.0V CBOUT goes high and when
//    Vcompare is less than 2.0V then CBOUT goes low.
//    Connect P1.6/CBOUT to P1.0 externally to see the LED toggle accordingly.
//1
//                 MSP430x552x
//             ------------------
//         /|\|                  |
//          | |                  |
//          --|RST       P6.0/CB0|<--Vcompare
//            |                  |
//            |        P1.6/CBOUT|----> 'high'(Vcompare>2.0V); 'low'(Vcompare<2.0V)
//            |                  |  |
//            |            P1.0  |__| LED 'ON'(Vcompare>2.0V); 'OFF'(Vcompare<2.0V)
//            |                  |
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5529.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;     // Stop WDT
  P1DIR |= BIT6;                // P1.6 output direction
  P1SEL |= BIT6;                // Select CBOUT function on P1.6/CBOUT

// Setup ComparatorB
  CBCTL0 |= CBIPEN + CBIPSEL_0; // Enable V+, input channel CB0
  CBCTL1 |= CBPWRMD_1;          // normal power mode
  CBCTL2 |= CBRSEL;             // VREF is applied to -terminal
  CBCTL2 |= CBRS_3+CBREFL_2;    // R-ladder off; bandgap ref voltage (1.2V)
                                // supplied ref amplifier to get Vcref=2.0V (CBREFL_2)
  CBCTL3 |= BIT0;               // Input Buffer Disable @P6.0/CB0
  CBCTL1 |= CBON;               // Turn On ComparatorB

  __delay_cycles(75);           // delay for the reference to settle

  __bis_SR_register(LPM4_bits);          // Enter LPM4
  __no_operation();                      // For debug
}
