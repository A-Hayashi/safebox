#include "mp3.h"

void InitMp3(void)
{
  Serial.println("InitMp3");
  static AltSoftSerial mySerial;
  mySerial.begin (9600);
  mp3_set_serial (mySerial);  //set softwareSerial for DFPlayer-mini mp3 module
  delay(100);  //wait 1ms for mp3 module to set volume
  mp3_set_volume (100);
}

void PlayMp3(mp3_t num)
{
  Serial.print("PlayMP3: ");
  Serial.println(num);
  mp3_play (num);
}

