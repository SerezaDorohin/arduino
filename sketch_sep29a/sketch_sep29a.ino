int data;
void setup()
{
  pinMode(3,OUTPUT);
  Serial.begin(9600);
  
}

void loop(){
if (Serial.available()>0) {
  data=Serial.parseInt();
  if (data==1){
    digitalWrite(3,1);
    delay(50);
    digitalWrite(3,0);
    delay(50);
  }
}
delay(100);
}
