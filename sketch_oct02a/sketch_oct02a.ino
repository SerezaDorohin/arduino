#include <SPI.h> // Подключение
#include <MFRC522.h> // Библиотек

MFRC522 rfid(10,9); // Объявляем пины RFID считывателя

unsigned long Key, KeyTemp; // Объявление переменных для ключей

int openDoor = 5000; // Время на открытие двери: 1с - 1000

void setup() {
  pinMode(6, OUTPUT); // Пин пищалки
  digitalWrite(6, 1);
  Serial.begin(9600); // Объявлям порт для общения с компьютером
  Serial.println("Setup: ");
  attachInterrupt(0, button, RISING); // Объявляем порт кнопки (Пин 2)
  attachInterrupt(1, button, RISING); // Объявляем порт датчика движения (Пин 3)
  pinMode(4, OUTPUT); // Пин светодиода на клавиатуре - красный цвет
  pinMode(5, OUTPUT); // Пин светодиода на клавиатуре - зелёный цвет
  pinMode(7, OUTPUT); // Пин контрольного светодиода на панели управления
  SPI.begin(); // Инициализация SPI
  rfid.PCD_Init(); // Инициализация RFID
  Serial.println("[SUCESS]");
  digitalWrite(6, 0);
}

void loop() {
if ( ! rfid.PICC_IsNewCardPresent()){return;} // Проверка на наличие карточки у readerа
if ( ! rfid.PICC_ReadCardSerial() ){return;} 

Key = 0; // Обнуление ключа карты
  for (byte i = 0; i < rfid.uid.size; i++) { // Запись ключа
    KeyTemp = rfid.uid.uidByte[i];
    Key = Key * 256 + KeyTemp;
  }
if ((Key==2685696931||Key==127766627)) { // Проверяем ключи
  digitalWrite(6,1);
  digitalWrite(7,1);
  delay(500);
  digitalWrite(6,0);
  delay(openDoor);
  digitalWrite(7,0);
} else {
  digitalWrite(7,1);
  digitalWrite(6,1);
  delay(250/2);
  digitalWrite(7,0);
  delay(250/2);
  digitalWrite(6,0);
  delay(250);
  digitalWrite(6,1);
  delay(250);
  digitalWrite(6,0);
  delay(openDoor/3);
  }
  delay(500);
}

// Метод кнопки
void button() {
  //КНОПКИ ПОКА НЕТУ
}

