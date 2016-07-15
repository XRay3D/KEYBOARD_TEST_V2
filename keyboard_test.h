#ifndef KEYBOARD_TEST
#define	KEYBOARD_TEST

#include <xc.h> 

typedef struct {
    unsigned char *Tris;
    unsigned char *Port;
    unsigned char Val;
    unsigned char An;
} PIN_T;

extern uint8_t AdcCh;

extern uint16_t AdcMeasData[];
extern uint8_t AdcChData[];
extern const uint8_t AdcChArr[];

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    void UpdatePins();

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* KEYBOARD_TEST */