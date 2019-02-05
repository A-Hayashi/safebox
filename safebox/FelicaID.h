#ifndef FALICA_ID
#define FALICA_ID

#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include "PN532_I2C.h"
#include "PN532.h"
#include "PN532_debug.h"



void FelicaInit();
bool isIdBlank(void);
bool isIdMatch(byte* IDm);
void writeId(byte* IDm);
void clearId(void);
byte detectId(byte *IDm);

#endif
