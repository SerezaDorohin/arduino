void setup() {
  pinMode(2,OUTPUT);

}

void loop() {
  digitalWrite(2,1);
  delay(50);
  digitalWrite(2,0);
  delay(50);
  digitalWrite(5,1);
  delay(50);
  digitalWrite(5,0);
  delay(50);
}
