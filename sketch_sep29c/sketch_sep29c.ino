#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);        // Create MFRC522 instance.
MFRC522::MIFARE_Key key;

void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  Serial.begin(9600);        // Initialize serial communications with the PC
        while (!Serial);           // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
        SPI.begin();               // Init SPI bus
        mfrc522.PCD_Init();        // Init MFRC522 card
        Serial.println(F("Warning: this example overwrites the UID of your UID changeable card, use with care!"));

}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
            delay(50);
            digitalWrite(2,0);
            return;
        }
        String str[] = {"07","D9","90","63"};
                for (byte i = 0; i < mfrc522.uid.size; i++) {
                  digitalWrite(2,1);
                  digitalWrite(3,1);
                Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                Serial.print(mfrc522.uid.uidByte[i], HEX);
                if (mfrc522.uid.uidByte=="079D9063"){
                  Serial.println("OK");
                }
                delay(10);
                digitalWrite(2,0);
        } 
        digitalWrite(3,0);
        Serial.println();
        delay(500);

}
