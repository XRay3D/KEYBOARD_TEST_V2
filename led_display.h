#ifndef LED_DISPLAY
#define	LED_DISPLAY

#include <xc.h> // include processor files - each processor file is guarded.  

#define RedA 0x01
#define RedB 0x02
#define RedC 0x04
#define RedD 0x08
#define RedE 0x10
#define RedF 0x20
#define RedG 0x40
#define RedDot 0x80

#define GreenA 0x01
#define GreenB 0x02
#define GreenC 0x04
#define GreenD 0x08
#define GreenE 0x10
#define GreenF 0x20
#define GreenG 0x40
#define GreenDot 0x80

#define Cathode1 0x10
#define Cathode2 0x20
#define Cathode3 0x40
#define Cathode4 0x80
#define Cathode5 0x00

#define Red PORTE
#define Green PORTD
#define Cathode PORTB

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    void UpdateLedData(uint8_t *data);
    void UpdateLedColor(uint8_t data);
    uint8_t UpdateLedDisplay(uint8_t flag);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* LED_DISPLAY */