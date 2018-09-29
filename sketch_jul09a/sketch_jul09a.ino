
#include <Keypad.h> // подключаем нашу библиотеку

const byte ROWS = 4; //число строк у нашей клавиатуры

const byte COLS = 4; //число столбцов у нашей клавиатуры

char hexaKeys[ROWS][COLS] = {

{'1','4','7','*'}, // здесь мы располагаем названия наших клавиш, как на клавиатуре,для удобства пользования

{'2','5','8','0'},

{'3','6','9','#'},

{'A','B','C','D'}

};

byte rowPins[ROWS] = {5, 4, 3, 2}; //к каким выводам подключаем управление строками

byte colPins[COLS] = {9, 8, 7, 6}; //к каким выводам подключаем управление столбцами

//initialize an instance of class NewKeypad

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup(){

Serial.begin(9600);

pinMode(11,OUTPUT);
pinMode(13,OUTPUT);

}

void loop(){
  char key = customKeypad.getKey();
  if (key){
    Serial.println(key); // Передаем название нажатой клавиши в сериал порт
    analogWrite(11,(int)key*50); // Издаем звуковой сигнал длиной 300 миллисекунд 
    digitalWrite(13,1);
  }
}




