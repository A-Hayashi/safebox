#include <EEPROM.h>

#include "Spi.h"
#include "Usb.h"
#include "PaSoRi.h"

PaSoRi pasori;


#define DOOR_SW   A3
#define POWER_SW  A2
#define OTHER_RY  A4
#define LOCK_RY   A5

bool isIdBlank(void)
{
  byte ExpectedIDm[8];
  readId(ExpectedIDm);

  int i;
  for (i = 0; i < sizeof(ExpectedIDm); i++) {
    if (ExpectedIDm[i] != 0xFF) {
      break;
    }
  }

  if (i == 8) {
    Serial.println("ID is Blank");
    return true;
  } else {
    Serial.println("ID is not Blank");
    return false;
  }
}

bool isIdMatch(byte* IDm)
{
  byte ExpectedIDm[8];
  readId(ExpectedIDm);

  int i;
  for (i = 0; i < sizeof(ExpectedIDm); i++) {
    if (ExpectedIDm[i] != IDm[i]) {
      break;
    }
  }

  if (i == 8) {
    Serial.println("ID match");
    return true;
  } else {
    Serial.println("ID not match");
    return false;
  }
}

void readId(byte* IDm)
{
  EEPROM_LOADER(0, IDm, 8);

  Serial.print("read ");
  for (int i = 0; i < 8; i++) {
    Serial.print(IDm[i], HEX);
    Serial.print(":");
  }
  Serial.println("");
}


void writeId(byte* IDm)
{
  EEPROM_SAVER(0, IDm, 8);

  Serial.print("write ");
  for (int i = 0; i < 8; i++) {
    Serial.print(IDm[i], HEX);
    Serial.print(":");
  }
  Serial.println("");
}

void clearId(void)
{
  byte IDm[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

  Serial.println("clear ID");
  writeId(IDm);
}

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
  //  clearId();
  //  while (true);

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

  rcode = pasori.poll(POLLING_ANY);

  if (ReadPowerSw()) {
    Lock(false);
  } else {
    Lock(true);
  }

  ReadDoorSw();

  if (rcode) {
    delay(500);
  } else {

    // Polling successful
    Serial.print("FeliCa detected. IDm=");
    byte IDm[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    for (i = 0; i < 8; i++) {
      IDm[i] = pasori.getIDm()[i];
      Serial.print(pasori.getIDm()[i], HEX);
      Serial.print(":");
    }
    Serial.println("");
    readEdy();

    if (isIdBlank()) {
      writeId(IDm);
    } else {
      if (isIdMatch(IDm)) {
        Lock(false);
        clearId();
      } else {
        Lock(true);
      }
    }


    delay(3000);
  }
}

void readEdy()
{
  byte b[16];
  for (int i = 0; i < 32; i++) {
    int rcode = pasori.read_without_encryption02(0x170F, i, b);
    if (rcode) {
      break;
    }
  }
}



void EEPROM_SAVER(int address, byte *val, int size) {
  for (int i = 0 ; i < size ; i++) {
    EEPROM[address + i] = val[i];
  }
}

void EEPROM_LOADER(int address, byte *val, int size) {
  for (int i = 0 ; i < size ; i++) {
    val[i] = EEPROM[address + i];
  }
}

