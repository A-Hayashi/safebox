#include "LED.h"
#include "SW.h"
#include "mp3.h"
#include "FelicaID.h"
#include "RY.h"

void led_check()
{
  //  動作確認済み
  InitPowerLed();
  InitInnerLed();
  while (1) {
    PowerLedOn(1);
    InnerLedOn(1);
    delay(1000);
    PowerLedOn(0);
    InnerLedOn(0);
    delay(1000);
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
    byte rcode = detectId(NULL);
    Serial.println(rcode);
    if (rcode == 0) {
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
    byte rcode = detectId(IDm);
    Serial.println(rcode);
    if (rcode == 0) {
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

void setup()
{
  Serial.begin(9600);
  Serial.println("Start");
  Felica_id_check();

}

void loop()
{
  //  byte rcode, i;
  //  pasori.task(); // call this at every loop
  //
  //  rcode = pasori.poll(POLLING_ANY);
  //
  //  if (isPowerOn()) {
  //    Lock(false);
  //  } else {
  //    Lock(true);
  //  }
  //
  //  isPowerOn();
  //  isDoorClose();
  //
  //  if (rcode) {
  //    delay(500);
  //  } else {
  //
  //    // Polling successful
  //    Serial.print("FeliCa detected. IDm=");
  //    byte IDm[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  //    for (i = 0; i < 8; i++) {
  //      IDm[i] = pasori.getIDm()[i];
  //      Serial.print(pasori.getIDm()[i], HEX);
  //      Serial.print(":");
  //    }
  //    Serial.println("");
  //    readEdy();
  //
  //    if (isIdBlank()) {
  //      writeId(IDm);
  //    } else {
  //      if (isIdMatch(IDm)) {
  //        if (isDoorClose() == true ) {
  //          Lock(false);
  //          clearId();
  //        }
  //      } else {
  //        Lock(true);
  //        PlayMp3(1);
  //      }
  //    }
  //
  //    delay(3000);
  //  }
}

