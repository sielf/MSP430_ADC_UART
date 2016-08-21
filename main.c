#include "msp430g2553.h"
 //#include "msp430g2452.h"
#define TXLED BIT0
#define RXLED BIT6
#define TXD BIT2
#define RXD BIT1
volatile unsigned char flag; //flag
volatile unsigned char counter; //flag
volatile unsigned char unused; //flag
// MC_1 -first state in datasheet MC1- second but in MC block
void TimConf(void)
{
TA1CTL|=TASSEL_2 | MC_1   |TACLR| ID_3;// |TAIE;
  TA1CCR0 = 30000;
 TA1CCTL0 = CCIE;
}
void ConfigureAdc(void)
{
 ADC10CTL0 |=  ADC10ON|ADC10SHT1 |ADC10SHT0|ADC10IE;//|(1<<3);//|ADC10SHT1 |ADC10SHT0 
  ADC10CTL1 |= INCH0 | INCH1;//|CONSEQ1;
  ADC10AE0 |= BIT3;
  ADC10CTL0 |= ENC;
}
void clk(void)
{
DCOCTL = 0; // Select lowest DCOx and MODx settings
   BCSCTL1 = CALBC1_1MHZ; // Set DCO
   DCOCTL = CALDCO_1MHZ;
   P2DIR |= 0xFF; // All P2.x outputs
   P2OUT &= 0x00; // All P2.x reset
   P1SEL |= RXD + TXD ; // P1.1 = RXD, P1.2=TXD
   P1SEL2 |= RXD + TXD ; // P1.1 = RXD, P1.2=TXD
   P1OUT &= 0x00;
   P1DIR |= RXLED + TXLED;
   //P1REN|= BIT3;
   UCA0CTL1 |= UCSSEL_2; // SMCLK
}

void uart_conf(void)
{
  UCA0CTL1 |= UCSWRST;
    //UCA0BR0 = 0x04; // 1MHz 250000
 // UCA0BR0 = 0x08; // 1MHz 115200
  UCA0BR0=0x68;
   UCA0BR1 = 0x00; // 1MHz 115200
   UCA0MCTL = UCBRS2 + UCBRS0; // Modulation UCBRSx = 5
   // UCA0MCTL = UCBRS1+ UCBRS0; // Modulation UCBRSx = 3 
  UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
   UC0IE |= UCA0RXIE; // Enable USCI_A0 RX interrupt}
    
}

int main(void)
{
   WDTCTL = WDTPW + WDTHOLD; // Stop WDT
   clk();
   uart_conf();
   ConfigureAdc();
   TimConf();
   flag=0;
   counter=0;
   __bis_SR_register( GIE);// G I enable
   while (1)
   { 
   }
}
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{
  UC0IE &= ~UCA0TXIE;
  counter=0;
 
} 
#pragma vector=USCIAB0RX_VECTOR 
__interrupt void USCI0RX_ISR(void) 
{
        P1OUT ^= RXLED;
    if (UCA0RXBUF == 'a') // 'a' received?
    { 
      flag=2;
      ADC10CTL0 |= ADC10SC;
    } 
   if (UCA0RXBUF == 'o') // 'o' received?
    { 
      flag=1;
      ADC10CTL0 |= ADC10SC;

      P1OUT ^= TXLED;
    } 
     if (UCA0RXBUF == 'e') // 'e' received?
    { 
    flag=0;
    } 
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  P1OUT ^= RXLED;
   if (flag==2)
  {
    if (counter==1)
    {
       ADC10CTL0 |= ADC10SC;
    }
    if (counter==0)
    {
      UCA0TXBUF =  (ADC10MEM);
      UC0IE |= UCA0TXIE;
      ADC10CTL0 |= ADC10SC;
      counter=1;
    }
  }
  if (flag==1)
  {
    P1OUT ^= RXLED;
   if (counter==0)
    {
      UCA0TXBUF =  (ADC10MEM);
      UC0IE |= UCA0TXIE;
      counter=1;
      ADC10CTL0 &= ~ADC10SC;
   }
    flag=0;
  }
  if (flag==0)
  {
    ADC10CTL0 &= ~ADC10SC;
  }
   //ADC10CTL0 &=~ADC10IFG;
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void CCRO_ISR(void)
{
 
 TA1CCTL0 &=~CCIFG;
}
//#pragma vector=TIMER0_A0_VECTOR
//__interrupt void T0CCR0_ISR(void)
//{
//  TA0CCTL0 &=~CCIFG;
//   //P1OUT ^= TXLED;
//}
//#pragma vector=TIMER0_A1_VECTOR
//__interrupt void T0CCR1_ISR(void)
//{
//   TA0CCTL1 &=~CCIFG;
//}

