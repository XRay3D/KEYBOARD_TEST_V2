#include <stdint.h>

#include "led_display.h"

const uint8_t RedSeg [] = {
    RedA | RedB | RedC | RedD | RedE | RedF, // 	0
    RedB | RedC, // 	1
    RedA | RedB | RedD | RedE | RedG, // 	2
    RedA | RedB | RedC | RedD | RedG, // 	3
    RedB | RedC | RedF | RedG, // 	4
    RedA | RedC | RedD | RedF | RedG, // 	5
    RedA | RedC | RedD | RedE | RedF | RedG, // 	6
    RedA | RedB | RedC, // 	7
    RedA | RedB | RedC | RedD | RedE | RedF | RedG, // 	8
    RedA | RedB | RedC | RedD | RedF | RedG, // 	9
    RedG, // 	-10
    0, // 	пробел11
    RedA | RedD | RedE | RedF | RedG, // 	E12
    RedE | RedG, // 	r13
};

const uint8_t GreenSeg [] = {
    GreenA | GreenB | GreenC | GreenD | GreenE | GreenF, // 	0
    GreenB | GreenC, // 	1
    GreenA | GreenB | GreenD | GreenE | GreenG, // 	2
    GreenA | GreenB | GreenC | GreenD | GreenG, // 	3
    GreenB | GreenC | GreenF | GreenG, // 	4
    GreenA | GreenC | GreenD | GreenF | GreenG, // 	5
    GreenA | GreenC | GreenD | GreenE | GreenF | GreenG, // 	6
    GreenA | GreenB | GreenC, // 	7
    GreenA | GreenB | GreenC | GreenD | GreenE | GreenF | GreenG, // 	8
    GreenA | GreenB | GreenC | GreenD | GreenF | GreenG, // 	9
    GreenG, // 	-10
    0, // 	пробел11
    GreenA | GreenD | GreenE | GreenF | GreenG, // 	E12
    GreenE | GreenG, // 	r13
};

uint8_t Data [8] = {8, '.', 8, '.', 8, '.', 8, '.'};
uint8_t Color = 0;

void UpdateLedColor(uint8_t color){
    Color = color;
}

void UpdateLedData(uint8_t *data){
    for(uint8_t i = 0; data[i]; i++){
        switch(data[i]){
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                Data[i] = data[i] - '0';
                break;
            case '-':
                Data[i] = 10;
                break;
            case '.':
                Data[i] = data[i];
                break;
            case ' ':
                Data[i] = 11;
                break;
            case 'E':
                Data[0] = 12;
                Data[1] = 13;
                Data[2] = 13;
                Data[3] = data[++i] - '0';
                return;
                break;
            default:
                Data[i] = 11;
                break;
        }
    }
}

uint8_t UpdateLedDisplay(uint8_t flag){

    static uint8_t CounterCatode = 0;
    static uint8_t CounterDataPos = 0;

    const uint8_t Pos[] = {
        Cathode1,
        Cathode2,
        Cathode3,
        Cathode4,
        0
    };

    flag &= Color;

    Red = 0x00;
    Green = 0xFF;

    Cathode &= ~(Cathode1 | Cathode2 | Cathode3 | Cathode4);
    Cathode = Pos[CounterCatode];

    if(Data[CounterDataPos + 1] == '.'){
        if(flag){
            Red = RedSeg[Data[CounterDataPos]] | RedDot;
        } else{
            Green = ~(GreenSeg[Data[CounterDataPos]] | GreenDot);
        }
        ++CounterDataPos;
    } else{
        if(flag){
            Red = RedSeg[Data[CounterDataPos]];
        } else{
            Green = ~(GreenSeg[Data[CounterDataPos]]);
        }
    }
    ++CounterDataPos;

    if(CounterCatode == 4){
        CounterCatode = 0;
        CounterDataPos = 0;
        return 1;
    } else{
        ++CounterCatode;
    }

    return 0;
}