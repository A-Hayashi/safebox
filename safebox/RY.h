#include "Arduino.h"

#define POWER_RY  A1  //動作確認済
#define LOCK_RY   A0  //動作確認済

void InitLock(void);
void Lock(bool lock);
void InitPowerRy(void);
void PowerRy(bool on);
