void setup() {
Serial.begin(9600);
}
void loop() {
  boolean vib=digitalRead(A1);
  int i=analogRead(A0);
  byte v=map(i,0,1023,0,4);
  Serial.print("|");  
  Serial.print(vib);
  delay(100);
  
  }
