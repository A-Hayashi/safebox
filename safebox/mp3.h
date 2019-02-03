#ifndef MP3
#define MP3

#include "Arduino.h"
#include "AltSoftSerial.h"
#include "DFPlayer_Mini_Mp3.h"

typedef enum {
  ID_REGISTER = 0,
  ID_UNMATCH,
  ID_MATCH,
} mp3_t;

void InitMp3(void);
void PlayMp3(mp3_t num);

#endif
