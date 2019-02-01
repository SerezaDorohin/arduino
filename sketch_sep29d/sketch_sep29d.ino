#include <SPI.h>
#include <MFRC522.h>

MFRC522 rfid(10,9);

unsigned long Key, KeyTemp;

void setup() {
  pinMode(3, OUTPUT);
  digitalWrite(3, 1);
  pinMode(2, OUTPUT);
  digitalWrite(2, 1);
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  delay(500);
}

void loop() {
  digitalWrite(2,0);
  digitalWrite(3,0);
  if ( ! rfid.PICC_IsNewCardPresent() ){return;}
  if ( ! rfid.PICC_ReadCardSerial() ){return;}

  Key = 0;

  for (byte i = 0; i < rfid.uid.size; i++) {
    KeyTemp = rfid.uid.uidByte[i];
    Key = Key * 256 + KeyTemp;
  }
  if (Key==2685696931) {
    digitalWrite(3,1);
    digitalWrite(2,1);
    delay(200);
    digitalWrite(3,0);
    delay(3000);  
    digitalWrite(2,0);
    digitalWrite(3,1);
    delay(50);
    digitalWrite(2,1);
    digitalWrite(3,0);
    delay(50);
    digitalWrite(2,0);
    digitalWrite(3,1);
    delay(50);
    digitalWrite(2,1);
    digitalWrite(3,0);
    delay(50);
    digitalWrite(2,0);
  }
  delay(1000);
}
