#include <LiquidCrystal.h>

LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

void setup(){
    lcd.begin(16, 2);
    lcd.print( "Hello, world!" );
}

void loop(){
}
