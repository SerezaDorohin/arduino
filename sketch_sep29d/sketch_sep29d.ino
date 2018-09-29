#include <SPI.h>
#include <MFRC522.h>

MFRC522 rfid(10,9);

unsigned long Key, KeyTemp;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(3, 0);
  digitalWrite(2, 0);
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent() ){return;}
  if ( ! rfid.PICC_ReadCardSerial() ){return;}

  Key = 0;

  for (byte i = 0; i < rfid.uid.size; i++) {
    KeyTemp = rfid.uid.uidByte[i];
    Key = Key * 256 + KeyTemp;
  }
  
  if (Key==2685696931||Key==127766627){
    Serial.println("SUCESS");
    digitalWrite(2, 1);
    digitalWrite(3, 1);
    delay(100);
    digitalWrite(3,0);
    delay(100);
    digitalWrite(3, 1);
    delay(100);
    digitalWrite(3, 0);
    digitalWrite(2, 0);
    delay(2000);
  } else {
    Serial.println("BAD");
    digitalWrite(3, 1);
    delay(200);
    digitalWrite(3, 0);
    delay(1000);
  }
}
