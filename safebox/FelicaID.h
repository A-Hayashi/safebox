#include <Arduino.h>
#include <EEPROM.h>
#include "Spi.h"
#include "Usb.h"
#include "PaSoRi.h"


void FelicaInit();
bool isIdBlank(void);
bool isIdMatch(byte* IDm);
void writeId(byte* IDm);
void clearId(void);
byte detectId(byte *IDm);
