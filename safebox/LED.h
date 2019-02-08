#ifndef LED
#define LED

#include <Arduino.h>

#define POWER_LED   3
#define INNER_LED   2

void InitPowerLed(void);
void PowerLedOn(bool on);
void InitInnerLed(void);
void InnerLedOn(bool on);

#endif
