#include "common_header.h"

void interrupt high_priority HISR(){
    if(TMR4IF && TMR4IE){
        TMR4IF = 0;
        if(UpdateLedDisplay(PR4)){
            PR4 <<= 1;
            if(!PR4){
                ++PR4;
            }
        }
        TMR4 = 0;
    }
}

void interrupt low_priority LISR(){
    static float Rez = 0.0;
    float Rez2;
    uint8_t ErrCounterX = 0;
    uint8_t ErrCounterY = 0;
    uint8_t i;
    uint8_t Buf[10];
    uint16_t U1, U2;
    uint32_t U = 1000; // В качестве опоры 1кОм 0,5% резисторы.

    if(TMR1IF && TMR1IE){
        TMR1IF = 0;
        if(Rez > 300){
            UpdateLedColor(255);
        } else if(Rez > 45){
            UpdateLedColor(Rez - 45);
        } else{
            UpdateLedColor(0);
        }
        if(Rez < 10){
            sprintf(Buf, "  %.1f", Rez);
        } else if(Rez < 100){
            sprintf(Buf, " %.1f", Rez);
        } else if(Rez < 1000){
            sprintf(Buf, "%.1f", Rez);
        } else{
            sprintf(Buf, "%u", (uint32_t) Rez);
        }
        UpdateLedData(Buf);
    }
    if(TMR2IF && TMR2IE){
        TMR2IF = 0;
        if(ADCON0bits.CHS != AdcChArr[AdcCh]){
            ADCON0bits.CHS = AdcChArr[AdcCh];
        } else{
            GO_DONE = 1;
            TMR2ON = 0;
            TMR2 = 0;
        }
    }
    if(ADIF && ADIE){
        ADIF = 0;
        AdcMeasData[AdcCh] = ADRES;
        if(++AdcCh == 14){
            AdcCh = 0;
            // Сканирование Шины Х на наличие утечек и КЗ
            for(ErrCounterX = 0, i = 0; i < 8; ++i){
                if(AdcMeasData[i] > 15){
                    AdcChData[ErrCounterX++] = i;
                }
                if(ErrCounterX == 2){
                    ++ErrCounterX;
                    i = 8;
                }
            }
            // Сканирование Шины У на наличие утечек и КЗ
            for(ErrCounterY = 0, i = 8; i < 14; ++i){
                if(AdcMeasData[i] > 15){
                    AdcChData[ErrCounterX + ErrCounterY++] = i;
                }
                if(ErrCounterY == 2){
                    ++ErrCounterY;
                    i = 14;
                }
            }
            switch(ErrCounterX + ErrCounterY){
                case 0:
                case 1:
                    //                    Rez = 0.0;
                    TMR1ON = 0; // Обновление индикации выключено
                    break;
                case 2:
                    // Сопротивление = ((u1 - u2) / u2) * 1000 Rоп
                    // В стенде реализованна импровизированная четырёхпроводная схема измерения
                    U1 = AdcMeasData[AdcChData[0]];
                    U2 = AdcMeasData[AdcChData[1]];
                    if(U1 > U2){
                        U *= (U1 - U2);
                    } else{
                        U *= (U2 - U1);
                    }
                    Rez2 = U / (float) U2;

                    // Ускорение вычисленя усреднения
                    //                    if(Rez == 0.0){
                    //                        Rez = Rez2;
                    //                    }
                    // Усреднение
#define Filter 0.1
                    Rez = ((Rez * (1.0 - Filter)) + (Rez2 * Filter));
                    TMR1ON = 1; // Обновление индикации включено
                    break;
                default:
                    UpdateLedColor(255);
                    if(ErrCounterX > 2 && ErrCounterY < 2){
                        UpdateLedData("E1");
                    }
                    if(ErrCounterX < 2 && ErrCounterY > 2){
                        UpdateLedData("E2");
                    }
                    if(ErrCounterX > 2 && ErrCounterY > 2){
                        UpdateLedData("E3");
                    }
                    Rez = 0.0;
                    TMR1ON = 0; // Обновление индикации выключено
                    break;
            }
            UpdatePins();
        }
        TMR2ON = 1;
    }
}
// Функции необходимые для #include <stdio.h>

char getch(void){
    while(!RC1IF){
    }
    if(OERR1){
        CREN1 = 0; // EUSART error - restart
        CREN1 = 1;
    }
    return RCREG1;
}

char getche(){
    return getch();
}

void putch(char txData){
    while(!TX1IF){
    }
    TXREG1 = txData; // Write the data byte to the USART.
}