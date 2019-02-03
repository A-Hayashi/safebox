#include "LED.h"
#include "SW.h"
#include "mp3.h"
#include "FelicaID.h"
#include "RY.h"
#include "debug.h"

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

