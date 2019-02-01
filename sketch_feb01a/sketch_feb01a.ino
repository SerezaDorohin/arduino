int echoPin = 11; // 
int trigPin = 12; // наши глаза
int duration;     //

int report = 0;

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(9600); // info
}

void loop() {
    
        int dist = getDistance();
        if(dist >= 0 && dist < 1200) {
            Serial.println(getDistance());
        } else {
            Serial.print("[error] -> distance is wrong (");
            Serial.print(dist);
            Serial.println("). ");
            report++;
            delay(5000);
        }
        delay(100);
    }
}

int getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    return (pulseIn(echoPin, HIGH) / 58);
}
