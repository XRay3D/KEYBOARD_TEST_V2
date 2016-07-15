#include <stdint.h>
#include <math.h>

#include "keyboard_test.h"

enum AdcData_CH{
    An00,
    An01,
    An02, //vref-
    An03, //vref+
    An04,
    An05,
    An06,
    An07,
    An08,
    An09,
    An10,
    An11,
    An12,
    An13,
    An14,
    An15,
    An16
};

const PIN_T Pin[] = {
    {&TRISA, &PORTA, 1/*  0*/, An00}, //	an0	ra0	
    {&TRISA, &PORTA, 2/*  1*/, An01}, //	an1	ra1	
    //    {&TRISA, &PORTA, 4/*  2*/, An02}, //	an2	ra2	ref-
    //    {&TRISA, &PORTA, 8/*  3*/, An03}, //	an3	ra3	ref+
    {&TRISA, &PORTA, 32/* 5*/, An04}, //	an4	ra5	
    {&TRISF, &PORTF, 1/*  0*/, An05}, //	an5	rf0	
    {&TRISF, &PORTF, 2/*  1*/, An06}, //	an6	rf1	
    {&TRISF, &PORTF, 4/*  2*/, An07}, //	an7	rf2	
    {&TRISF, &PORTF, 8/*  3*/, An08}, //	an8	rf3	
    {&TRISF, &PORTF, 16/* 4*/, An09}, //	an9	rf4	
    {&TRISF, &PORTF, 32/* 5*/, An10}, //	an10	rf5	
    {&TRISF, &PORTF, 64/* 6*/, An11}, //	an11	rf6	
    {&TRISH, &PORTH, 16/* 4*/, An12}, //	an12	rh4	
    {&TRISH, &PORTH, 32/* 5*/, An13}, //	an13	rh5	
    {&TRISH, &PORTH, 64/* 6*/, An14}, //	an14	rh6	
    {&TRISH, &PORTH, 128/*7*/, An15} // 	an15	rh7	
};

const uint8_t AdcChArr[] = {
    An00,
    An01,
    An04,
    An05,
    An06,
    An07,
    An08,
    An09,
    An10,
    An11,
    An12,
    An13,
    An14,
    An15,
    An16
};

uint8_t AdcCh = 0;
uint8_t AdcChData[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint16_t AdcMeasData[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Установка вывода в 1 (+5В) и сброс остальных на вход
// Сброс AdcChData для следующей итерации измерений

void UpdatePins(){
    static PIN_T *LastPin = Pin;
    static uint8_t pin = 0;

    for(uint8_t i = 0; i < 14; ++i){
        AdcChData[i] = 0;
    }

    if(++pin == 14){
        pin = 0;
    }

    *LastPin->Tris |= LastPin->Val;

    *Pin[pin].Port |= Pin[pin].Val;
    *Pin[pin].Tris &= ~Pin[pin].Val;

    LastPin = &Pin[pin];
}