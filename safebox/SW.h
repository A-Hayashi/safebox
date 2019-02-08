#ifndef SW
#define SW

#include "Arduino.h"

#define DOOR_SW   5   //動作確認済
#define INNER_SW  4

void InitDoorSw(void);
bool isDoorClose(void);
void InitInnerSw(void);
bool isInnerPushed(void);

#endif
