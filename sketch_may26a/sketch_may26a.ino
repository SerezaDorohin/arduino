void setup() {
  pinMode(4,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i=digitalRead(A0);
  Serial.println(i);
  if (i==1){
    for (byte b;b<=10;b++){
      delay(1000);
      Serial.println(b);
      digitalWrite(4,1);
    }
  }
   else {
      digitalWrite(4,0);
    }
  }

