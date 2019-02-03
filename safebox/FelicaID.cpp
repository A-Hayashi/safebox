#include "FelicaID.h"

static PaSoRi pasori;

static void readId(byte* IDm);
static void EEPROM_SAVER(int address, byte *val, int size);
static void EEPROM_LOADER(int address, byte *val, int size);
static void readEdy(PaSoRi& pasori);

void FelicaInit()
{
  Serial.println("FelicaInit");
  delay(500);
  byte rcode = pasori.begin(); // initialize PaSoRi
  
  if (rcode != 0) {
    Serial.print("PaSoRi initialization failed! : rcode = ");
    Serial.println(rcode, HEX);
    while (1); // stop
  }
  
}

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

static void readId(byte* IDm)
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



static void EEPROM_SAVER(int address, byte *val, int size) {
  for (int i = 0 ; i < size ; i++) {
    EEPROM[address + i] = val[i];
  }
}

static void EEPROM_LOADER(int address, byte *val, int size) {
  for (int i = 0 ; i < size ; i++) {
    val[i] = EEPROM[address + i];
  }
}

byte detectId(byte *IDm)
{
  byte rcode;
  byte IDm_tmp[8];
  pasori.task(); // call this at every loop
  rcode = pasori.poll(POLLING_ANY);

  if (rcode) {
    delay(500);
  } else {
    // Polling successful
    Serial.print("FeliCa detected. IDm=");
    memset(IDm, 0, 8);
    for (int i = 0; i < 8; i++) {
      IDm_tmp[i] = pasori.getIDm()[i];
      Serial.print(IDm_tmp[i], HEX);
      Serial.print(":");
    }
    if (IDm != NULL) {
      memcpy(IDm, IDm_tmp, sizeof(IDm_tmp));
    }
    Serial.println("");
    readEdy(pasori);
  }
  return rcode;
}


static void readEdy(PaSoRi& pasori)
{
  byte b[16];
  for (int i = 0; i < 32; i++) {
    int rcode = pasori.read_without_encryption02(0x170F, i, b);
    if (rcode) {
      break;
    }
  }
}
