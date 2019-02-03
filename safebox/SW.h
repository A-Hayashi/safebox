#include "Arduino.h"

#define DOOR_SW   6   //動作確認済
#define INNER_SW  5

void InitDoorSw(void);
bool isDoorClose(void);
void InitInnerSw(void);
bool isInnerPushed(void);
