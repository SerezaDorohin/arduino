#include <Servo.h>

/**
 * @author SergeyDorohin;
 * @version 1.0;
 */
 
int echoPin = 11; // 
int trigPin = 12; // наши глаза
int duration;     //

int stepsDelay = 3; // данная переменная задаёт перерыв между шагами двигателей

// настройка сервоприводов:
Servo check;   // control - руль, check - поворот глаз
Servo control; // диапазон севомашинок - 15 - 160

// переменные, хранящие позицию:
int controlPos = 90; // позиция руля
int checkPos = 90;   // позиция глаз

// массивы, записывающие изменения
int walls[4];
int steps;

/*
В коде встречаются маркировки стен: 1, 2, 3:
1 - левая стена
2 - правая стена
3 - стены на одинаковых расстояниях
4 - вернуть руль обратно
*/

void setup() {
    Serial.begin (9600);
    check.attach(9);
    control.attach(10);
    for (int i = 2; i < 9; i++) {
      pinMode(i, OUTPUT);
    }
    pinMode(8, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    setCheckDefault();
    setControl(4);
    // отпраляем машинку к старту:
    goHome();
    // гоняем по стенам
    setControl(1);
    steps = 0;
    steps += goNextWall(steps);
    walls[0] = steps;
    steps += goNextWall(steps);
    walls[1] = steps;
    steps += goNextWall(steps);
    walls[2] = steps;
    steps += goNextWall(steps);
    walls[3] = steps;
}

void loop() {
    
}

int goNextWall(int steps) {
    setControl(4);
    while(getDistance() < 80) {
       steps += 1;
       doStep();
    }
    Serial.print("wall: ");
    Serial.println(walls[1]);
    return steps;
}

// метод, отпраляющий машинку к ближайшему углу
void goHome() {
    while(true) {
        // проверяем, что находится за бортом
        int distance = getDistance();
        Serial.println(distance);
        // если стена близко, то прекращаем хождение и смотрим куда поедем дальше
        if(distance < 40) {
            int test = checkWalls();
            setControl(test);
            break;
        }
        // делаем 50 шагов:
        for(int barrier = 0; barrier <= 50; barrier++) { 
            doStep(); 
        }
    }
    while(true) {
        // проверяем, что находится за бортом
        int distance = getDistance();
        Serial.println(distance);
        // если стена близко, то прекращаем хождение и мы дома!
        if(distance < 40) {
            break;
        }
        // делаем 50 шагов:
        for(int barrier = 0; barrier <= 50; barrier++) { 
            doStep(); 
        }
    }
    setControl(4);
}

// метод, поварачивающий руль:
void setControl(int wall) {
    if(wall == 1 || wall == 3) {
        for(controlPos; controlPos > 40; controlPos--) {
            control.write(controlPos);
        }
    } else if(wall == 2) {
        for(controlPos; controlPos < 140; controlPos++) {
            control.write(controlPos);
        }
    } else if(wall = 4) {
        if(controlPos < 90) {
            for(controlPos; controlPos <= 90; controlPos++) {
                control.write(controlPos);
            }
        } else if(controlPos > 90) {
            for(controlPos; controlPos >= 90; controlPos--) {
                control.write(controlPos);
            }
        }
    }
}

// метод, поворачивающий ультразвуковой датчик в первоначальную позицию:
void setCheckDefault() {
    if(controlPos > 90) {
         for(controlPos; controlPos >= 90; controlPos--) {
              control.write(controlPos);
         }
    } else if(controlPos < 90) {
         for(controlPos; controlPos <= 90; controlPos++) {
              control.write(controlPos);
         }
    }
}

int checkWalls() {
    // поворачиваем ульразвуковой датчик вправо:
    for(checkPos; checkPos > 10; checkPos--) {
        check.write(checkPos);
        delay(10);
    }
    // запишем расстояние от правой стены
    int right = getDistance();
    delay(100);
    // поворачиваем ульразвуковой датчик влево:
    for(checkPos; checkPos < 180; checkPos++) {
        check.write(checkPos);
        delay(10);
    }
    // запишем расстояние от левой стены
    int left = getDistance();
    delay(50);
    // возвращаем сервомашинку на первоначальную позицию (90)
    for(checkPos; checkPos >= 90; checkPos--) {
        check.write(checkPos);
        delay(10);
    }
    // проверяем, какая сторона ближе и отправляем:
      if(left > right) {
          return 1;
      } else if (left < right) {
          return 2;
      } else if (left == right) {
          return 3;
      }
}

// метод, возвращающий расстояние с "глаз"
int getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    return (pulseIn(echoPin, HIGH) / 58);
}

// метод, производящий шаг: (написан вручную)
void doStep() {
    digitalWrite(8, 1);
    digitalWrite(13, 0);
    digitalWrite(2, 0);
    digitalWrite(3, 0);
    digitalWrite(4, 1);
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    digitalWrite(7, 0);
    delay(stepsDelay);
    digitalWrite(8, 0);
    digitalWrite(13, 1);
    digitalWrite(2, 0);
    digitalWrite(3, 0);
    digitalWrite(4, 0);
    digitalWrite(5, 1);
    digitalWrite(6, 0);
    digitalWrite(7, 0);
    delay(stepsDelay);
    digitalWrite(8, 0);
    digitalWrite(13, 0);
    digitalWrite(2, 1);
    digitalWrite(3, 0);
    digitalWrite(4, 0);
    digitalWrite(5, 0);
    digitalWrite(6, 1);
    digitalWrite(7, 0);
    delay(stepsDelay);
    digitalWrite(8, 0);
    digitalWrite(13, 0);
    digitalWrite(2, 0);
    digitalWrite(3, 1);
    digitalWrite(4, 0);
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    digitalWrite(7, 1);
    delay(stepsDelay);
}

