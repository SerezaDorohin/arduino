#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN    9   // 
#define SS_PIN    10    //

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

void setup() {
  Serial.begin(9600);  
  while (!Serial)
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println(F("Scan PICC to see UID, type, and data blocks..."));
}

void loop() {
if (mfrc522.PICC_DumpToSerial(&(mfrc522.uid))=="A1 A2 A3 A4"){
  Serial.println("OK");
}
else
{
  Serial.println("BAD");
}
}


