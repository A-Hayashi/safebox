#include "debug.h"

void led_check()
{
  //  動作確認済み
  InitPowerLed();
  InitInnerLed();
  while (1) {
    PowerLedOn(1);
    InnerLedOn(1);
    delay(500);
    InnerLedOn(0);
    delay(500);
    PowerLedOn(0);
    InnerLedOn(1);
    delay(500);
    InnerLedOn(0);
    delay(500);
  }
}

void mp3_check()
{
  //  動作確認済み
  InitMp3();
  while (1) {
    PlayMp3(ID_REGISTER);   //ID登録
    delay(3000);
    PlayMp3(ID_UNMATCH);   //ID不一致
    delay(3000);
    PlayMp3(ID_MATCH);   //ID一致
    delay(3000);
  }
}

void power_latch_check()
{
  //動作確認済
  InitPowerRy();
  InitPowerLed();
  while (1) {
    PowerLedOn(1);
    PowerRy(1);
    delay(3000);
    PowerRy(0);
    while (1);
  }
}

void Felica_check()
{
  //動作確認済
  InitPowerRy();
  InitPowerLed();
  PowerRy(1);
  PowerLedOn(1);

  FelicaInit();
  InitMp3();

  while (1) {
    byte IDm[8];
    byte ret = detectId(IDm);
    Serial.println(ret);
    if (ret == 1) {
      PlayMp3(ID_REGISTER);
      delay(3000);
    }
  }
}


void sw_check()
{
  //動作確認済
  InitPowerLed();
  PowerLedOn(1);

  InitPowerRy();
  PowerRy(1);

  InitDoorSw();
  InitInnerSw();
  InitLock();
  while (1) {
    Lock(0);
    isInnerPushed();
    bool door_close = isDoorClose();
    if (door_close == true) {
      Lock(1);
      delay(5000);
      Lock(0);
      delay(5000);
    }
    delay(100);
  }
}


void lock_check()
{
  //動作確認済
  InitPowerRy();
  InitLock();
  InitPowerLed();
  PowerLedOn(1);
  PowerRy(1);
  Lock(0);
  while (1) {
    PowerRy(1);
    Lock(1);
    delay(3000);
    PowerRy(1);
    Lock(0);
    delay(3000);
  }
}

void Felica_id_check()
{
  //動作確認済
  InitPowerRy();
  InitPowerLed();
  PowerRy(1);
  PowerLedOn(1);

  FelicaInit();
  InitMp3();
  while (1) {
    byte IDm[8];
    byte ret = detectId(IDm);
    Serial.println(ret);
    if (ret == 1) {
      if (isIdBlank()) {
        PlayMp3(ID_REGISTER);
        writeId(IDm);
      } else {
        if (isIdMatch(IDm)) {
          PlayMp3(ID_MATCH);
          clearId();
        } else {
          PlayMp3(ID_UNMATCH);
        }
      }
      delay(3000);
    }
  }
}


void eink_check()
{
  pinMode(A2, OUTPUT);
  while (1) {
    delay(10000);
    Serial.println("USED");
    digitalWrite(A2, LOW);
    delay(10000);
    Serial.println("NOT USED");
    digitalWrite(A2, HIGH);
  }
}

