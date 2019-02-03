#ifndef LED
#define LED

#include <Arduino.h>

#define POWER_LED   2
#define INNER_LED   3

void InitPowerLed(void);
void PowerLedOn(bool on);
void InitInnerLed(void);
void InnerLedOn(bool on);

#endif
