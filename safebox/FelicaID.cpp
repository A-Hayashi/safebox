#include "FelicaID.h"

static PN532_I2C pn532i2c(Wire);
static PN532 nfc(pn532i2c);

static void readId(byte* IDm);
static void EEPROM_SAVER(int address, byte *val, int size);
static void EEPROM_LOADER(int address, byte *val, int size);

void FelicaInit()
{
  Serial.println("FelicaInit");

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata)
  {
    Serial.print("Didn't find PN53x board");
    while (1) {delay(10);};      // halt
  }

  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Firmware ver. "); Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print('.'); Serial.println((versiondata >> 8) & 0xFF, DEC);

  // Set the max number of retry attempts to read from a card
  // This prevents us from waiting forever for a card, which is
  // the default behaviour of the PN532.
  nfc.setPassiveActivationRetries(0xFF);
  nfc.SAMConfig();
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
  uint8_t ret;
  uint16_t systemCode = 0xFFFF;
  uint8_t requestCode = 0x01;       // System Code request
  uint8_t pmm[8];
  uint16_t systemCodeResponse;

  // Wait for an FeliCa type cards.
  // When one is found, some basic information such as IDm, PMm, and System Code are retrieved.
  Serial.print("Waiting for an FeliCa card...  ");
  ret = nfc.felica_Polling(systemCode, requestCode, IDm, pmm, &systemCodeResponse, 500);
	
  return ret;
}

