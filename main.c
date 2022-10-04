#include <msp430.h>
#include <stdio.h>
#include <stdbool.h>
volatile unsigned int ADC_Result;



void initADC() {
    //LEDs
    P1DIR |=BIT0;
    P6DIR |=BIT6;
    //ADC Config
    ADCCTL0 |=ADCSHT_1 | ADCON;
    ADCCTL1 |= ADCSHP | ADCSSEL_3;
    ADCCTL2 &=~ADCRES;
    ADCCTL2 |=ADCRES_2;
    ADCMCTL0 |=ADCINCH_9 | ADCSREF_0;
}

void setGreen(bool en){
    if(en){
        P6OUT|=BIT6;
    }else{
        P6OUT &= ~BIT6;
    }
}
void setRed(bool en){
    if(en==true){
        P1OUT |= BIT0;
    }else{
        P1OUT &= ~BIT0;
    }
}

void darkOrNot(int num) {
    if(num <=1000) {
        setGreen(true);
        setRed(true);
    }

    else {
        setGreen(false);
        setRed(false);
    }
}


int main(void) {
    WDTCTL=WDTPW | WDTHOLD;
    PM5CTL0=0xFFFE;
    P1SEL0 |=BIT1;
    P2SEL1 |=BIT1;
    initADC();

    while(true) {
        ADCCTL0 |=ADCENC | ADCSC;

        while(ADCCTL1 & ADCBUSY) {
            ADC_Result=ADCMEM0;
        }

        darkOrNot(ADC_Result);
        __delay_cycles(5000);
    }

    return 0;
}


