#include "LED.h"
#include "SW.h"
#include "mp3.h"
#include "FelicaID.h"
#include "RY.h"
#include "debug.h"

#include <MsTimer2.h>

void setup()
{
  Serial.begin(9600);
  Serial.println("Start");
  //led_check();
  //mp3_check();
  //power_latch_check();
  //Felica_check();
  //Felica_id_check();
  //lock_check();
  //sw_check();
  //eink_check();
  //Felica_id_clear();
  InitPowerRy();
  InitPowerLed();
  PowerRy(1);
  PowerLedOn(1);

  FelicaInit();
  InitMp3();
  InitLock();
  eink_init();

  //  MsTimer2::set(30000, powerOff); // 500msの期間
  //  MsTimer2::start();
}

void powerOff()
{
  PowerRy(0);
  MsTimer2::stop();
}


void loop()
{
  byte IDm[8];

  //  if (isDoorClose()) {
  //    delay(1000);
  //    Lock(1);
  //  }

  if (isIdBlank()) {
    eink_disp(CAN_USE);
    Lock(0);
  } else {
    eink_disp(USING);
  }

  byte ret = detectId(IDm);
  Serial.println(ret);

  if (ret == 1) {
    if (isIdBlank()) {
      PlayMp3(ID_REGISTER);
      writeId(IDm);
      delay(1000);
      Lock(1);
    } else {
      if (isIdMatch(IDm)) {
        PlayMp3(ID_MATCH);
        clearId();
        delay(1000);
        Lock(0);
      } else {
        PlayMp3(ID_UNMATCH);
        delay(1000);
      }
    }
  }
}

