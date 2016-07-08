#include "common_header.h"

void main(void){
    TRISB = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;

    TXSTA1 = 0x24; //TRANSMIT STATUS AND CONTROL REGISTER
    RCSTA1 = 0x90; //RECEIVE STATUS AND CONTROL REGISTER
    SPBRG1 = 0xA2; //Baud Rate Generator Register //9600 //25MHz
    //TX1IE = 1;
    //RC1IE = 1;

    ADCON0 = 0x01;
    ADCON1 = 0x10;
    ADCON2 = 0x86; //adfm = r
    ADCON0bits.GO_DONE = 1;
    PIE1bits.ADIE = 1;
    IPR1bits.ADIP = 0;

    TMR1ON = 1;
    T1CON = 0x11;
    PIE1bits.TMR1IE = 1;
    IPR1bits.TMR1IP = 0;

    T2CON = 0x00;
    T2CONbits.TMR2ON = 1;
    PIE1bits.TMR2IE = 1;
    IPR1bits.TMR2IP = 0;

    T4CONbits.T4CKPS = 3;
    T4CONbits.T4OUTPS = 2;
    T4CONbits.TMR4ON = 1;
    PR4 = 0x01;
    PIE3bits.TMR4IE = 1;
    IPR3bits.TMR4IP = 1;

    UpdateLedData("  0.0 ");

    RCONbits.IPEN = 1;
    GIE = 1;
    PEIE = 1;

    while(1){
    }
}

/**
  End of File
 */
