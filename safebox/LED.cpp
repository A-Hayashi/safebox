#include "LED.h"

void InitPowerLed(void)
{
  pinMode(POWER_LED, OUTPUT);
  Serial.println("InitPowerLed");
}

void PowerLedOn(bool on)
{
  static byte on_old = 0xFF;

  if (on != on_old) {
    if (on == true) {
      Serial.println("POWER LED ON");
    } else {
      Serial.println("POWER LED OFF");
    }
  }
  on_old = on;

  if (on == true) {
    digitalWrite(POWER_LED, LOW);
  } else {
    digitalWrite(POWER_LED, HIGH);
  }
}




void InitInnerLed(void)
{
  pinMode(INNER_LED, OUTPUT);
  Serial.println("InitInnerLed");
}

void InnerLedOn(bool on)
{
  static byte on_old = 0xFF;

  if (on != on_old) {
    if (on == true) {
      Serial.println("INNER LED ON");
    } else {
      Serial.println("INNER LED OFF");
    }
  }
  on_old = on;

  if (on == true) {
    digitalWrite(INNER_LED, LOW);
  } else {
    digitalWrite(INNER_LED, HIGH);
  }
}