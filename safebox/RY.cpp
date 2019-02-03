#include "RY.h"

void InitLock(void)
{
  pinMode(LOCK_RY, OUTPUT);
  Serial.println("InitLock");
}

void Lock(bool lock)
{
  static byte lock_old = 0xff;
  if (lock_old != lock) {
    if (lock == true) {
      Serial.println("DoorLock");
    } else {
      Serial.println("DoorUnlock");
    }
  }

  if (lock == true) {
    digitalWrite(LOCK_RY, HIGH);
  } else {
    digitalWrite(LOCK_RY, LOW);
  }

  lock_old = lock;
}

void InitPowerRy(void)
{
  pinMode(POWER_RY, OUTPUT);
  Serial.println("InitPowerRy");
}

void PowerRy(bool on)
{
  static byte on_old = 0xff;
  if (on_old != on) {
    if (on == true) {
      Serial.println("PowerRyOn");
    } else {
      Serial.println("PowerRyOff");
    }
  }

  if (on == true) {
    digitalWrite(POWER_RY, LOW);
  } else {
    digitalWrite(POWER_RY, HIGH);
  }

  on_old = on;
}


