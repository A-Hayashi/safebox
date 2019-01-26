#include "Spi.h"
#include "Usb.h"
#include "PaSoRi.h"

PaSoRi pasori;

#define DOOR_SW   A3
#define POWER_SW  A2
#define OTHER_RY  A4
#define LOCK_RY   A5

void InitDoorSw(void)
{
  pinMode(DOOR_SW, INPUT);
  Serial.println("InitDoorSw");
}

void InitPowerSw(void)
{
  pinMode(POWER_SW, INPUT);
  Serial.println("InitPowerSw");
}

void InitLock(void)
{
  pinMode(LOCK_RY, OUTPUT);
  Serial.println("InitLock");
}

bool ReadPowerSw(void)
{
  bool sw = digitalRead(POWER_SW);
  static byte sw_old = 0xff;

  if (sw_old != sw) {
    if (sw == HIGH) {
      Serial.println("PowerOff");
    } else {
      Serial.println("PowerOn");
    }
  }
  sw_old = sw;

  if (sw == HIGH) {
    return false;
  } else {
    return true;
  }
}


bool ReadDoorSw(void)
{
  bool sw = digitalRead(DOOR_SW);
  static byte sw_old = 0xff;

  if (sw_old != sw) {
    if (sw == HIGH) {
      Serial.println("DoorOpen");
    } else {
      Serial.println("DoorClose");
    }
  }
  sw_old = sw;

  if (sw == HIGH) {
    return false;
  } else {
    return true;
  }
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

void setup()
{
  Serial.begin(9600);
  Serial.println("Start");
  InitLock();
  Lock(true);
  InitDoorSw();
  InitPowerSw();

  byte rcode = pasori.begin(); // initialize PaSoRi
  if (rcode != 0) {
    Serial.print("PaSoRi initialization failed! : rcode = ");
    Serial.println(rcode, HEX);
    while (1); // stop
  }
}

void loop()
{
  byte rcode, i;
  pasori.task(); // call this at every loop
  static short syscode = POLLING_EDY;

  // Polling for SFC or Edy each time
  syscode = syscode == POLLING_SUICA ? POLLING_EDY : POLLING_SUICA;
  rcode = pasori.poll(syscode);

  if (ReadPowerSw()) {
    Lock(false);
  } else {
    Lock(true);
  }

  ReadDoorSw();

  if (rcode) {
    delay(500);
  } else {
    Lock(false);
    // Polling successful
    Serial.print("FeliCa detected. IDm=");
    for (i = 0; i < 8; i++) {
      Serial.print(pasori.getIDm()[i], HEX);
      Serial.print(" ");
    }
    Serial.print("  PMm=");
    for (i = 0; i < 8; i++) {
      Serial.print(pasori.getPMm()[i], HEX);
      Serial.print(" ");
    }
    Serial.println("");

    if (syscode == POLLING_SUICA) {
      // Read SFC (Suica etc.)
      Serial.println("<< SFC >>");
      readSFC();
    } else {
      // Read Edy
      Serial.println("<< Edy >>");
      readEdy();
    }
    delay(3000);
  }
}

int readSFC()
{
  byte b[16];
  int ret = -1;
  for (int i = 0; i < 32; i++) {
    int rcode = pasori.read_without_encryption02(0x090f, i, b);
    if (rcode) {
      Serial.print("rcode = ");
      Serial.println(rcode, HEX);
      break;
    }
    Serial.print(i, DEC);
    Serial.print(": ");
    Serial.print(b[11] * 256 + b[10]);
    Serial.print(" YEN  ");
    if (i == 0) ret = (unsigned int)b[11] * 256 + b[10];

    // date
    Serial.print(2000 + ((b[4] >> 1) & 0x7f), DEC);
    Serial.print(".");
    Serial.print(((b[4] & 0x01) << 3) | ((b[5] >> 5) & 0x07), DEC);
    Serial.print(".");
    Serial.print(b[5] & 0x1F, DEC);

    // from/to
    Serial.print(" from:");
    Serial.print(b[6], HEX);
    Serial.print("-");
    Serial.print(b[7], HEX);
    Serial.print(" to:");
    Serial.print(b[8], HEX);
    Serial.print("-");
    Serial.print(b[9], HEX);

    Serial.println("");
  }
  return ret;
}

int readEdy()
{
  byte b[16];
  int ret = -1;
  for (int i = 0; i < 32; i++) {
    int rcode = pasori.read_without_encryption02(0x170F, i, b);
    if (rcode) {
      Serial.print("rcode = ");
      Serial.println(rcode, HEX);
      break;
    }
    Serial.print(i, DEC);
    Serial.print(": ");
    Serial.print(b[14] * 256 + b[15], DEC);
    Serial.println(" YEN");
    if (i == 0) ret = (unsigned int)b[14] * 256 + b[15];
  }
  return ret;
}


