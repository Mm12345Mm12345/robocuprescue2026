#include <NewPing.h>
  int Speed = 65;
  int SlowSpeed = 0;
  int turnSpeed = 55;
//fake setup
  unsigned long currentMillis = 0;
  unsigned long previousMillis = 0;
  unsigned long interval = 0;


  int leftSpeed = 0;
  int rightSpeed = 0;
  int LeftGreenFrequency = 0;
  int LeftGreenColor = 0;
  int RightGreenFrequency = 0;
  int RightGreenColor = 0;



  bool isLeft = true;

  //colorsens Right
  #define LeftS0 35
  #define LeftS1 34
  #define LeftS2 37
  #define LeftS3 38
  #define LeftSensorOut 36

  //colorsens left
  #define RightS0 49
  #define RightS1 50
  #define RightS2 47
  #define RightS3 46
  #define RightSensorOut 48

  #define SIDE_TRIGGER_PIN 44 // Arduino pin tied to trigger pin on the ultrasonic sensor.
  #define SIDE_ECHO_PIN 43 // Arduino pin tied to echo pin on the ultrasonic sensor.

  #define FRONT_TRIGGER_PIN 33 // Arduino pin tied to trigger pin on the ultrasonic sensor.
  #define FRONT_ECHO_PIN 32 // Arduino pin tied to echo pin on the ultrasonic sensor.
  #define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

  NewPing front_sonar(FRONT_TRIGGER_PIN, FRONT_ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

  NewPing side_sonar(SIDE_TRIGGER_PIN, SIDE_ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

  #define enb 3
  #define in1 4
  #define in2 5
  #define in3 6
  #define in4 7
  #define ena 8
  #define led 13
  #define sens1 23 // 27 |
  #define sens2 24 // 28 |
  #define sens3 25 // 29 |
  #define sens4 29 //.25 |
  #define sens5 28 // 24 |
  #define sens6 27 // 23 |

void setup() {
  Serial.begin(9600);
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb, OUTPUT);

  pinMode(led, OUTPUT);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  pinMode(sens1, INPUT);
  pinMode(sens2, INPUT);
  pinMode(sens3, INPUT);
  pinMode(sens4, INPUT);
  pinMode(sens5, INPUT);
  pinMode(sens6, INPUT);
  // Setting the outputs
  pinMode(LeftS0, OUTPUT);
  pinMode(LeftS1, OUTPUT);
  pinMode(LeftS2, OUTPUT);
  pinMode(LeftS3, OUTPUT);

  pinMode(RightS0, OUTPUT);
  pinMode(RightS1, OUTPUT);
  pinMode(RightS2, OUTPUT);
  pinMode(RightS3, OUTPUT);

  // Setting the sensorOut as an input
  pinMode(RightSensorOut, INPUT);
  pinMode(LeftSensorOut, INPUT);

  // Setting frequency scaling to 20%
  digitalWrite(LeftS0, HIGH);
  digitalWrite(LeftS1, LOW);
  digitalWrite(RightS0, HIGH);
  digitalWrite(RightS1, LOW);

}

void loop() {

  int front_distance = front_sonar.ping_cm();
  digitalWrite(13, LOW);
  if (front_distance < 15 && front_distance > 0) { //  עצור לשניה אם יש מכשול מקדימה
    leftSpeed = 0;
    rightSpeed = 0;
    analogWrite(ena, leftSpeed);
    analogWrite(enb, rightSpeed);
    delay(1000);
    int side_distance = side_sonar.ping_cm();
    while (!(side_distance < 30 && side_distance > 0)) { //תתחיל להסתובב במקום עד שהחיישן מרלחק בצד קולט את המכשול
      side_distance = side_sonar.ping_cm();

      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      leftSpeed = Speed;
      rightSpeed = Speed;
      analogWrite(ena, leftSpeed);
      analogWrite(enb, rightSpeed);
    }
    leftSpeed = 0;
    rightSpeed = 0;
    analogWrite(ena, leftSpeed);
    analogWrite(enb, rightSpeed);
    delay(1000); // עצור לשניה

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    digitalWrite(13, HIGH);

    while (digitalRead(sens4) != LOW && digitalRead(sens3) != LOW) { // כל עוד החיישן קו לא מזהה קו תיסע 
      //בקשת לםי החיישן מרחק צד במקביל לבקבוק
      side_distance = side_sonar.ping_cm();

      while ((side_distance < 30 && side_distance > 0) && digitalRead(sens4) != LOW &&  digitalRead(sens3) != LOW) { // רואה
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        delay(50);
        side_distance = side_sonar.ping_cm();
        digitalWrite(13, HIGH);
        leftSpeed = Speed;
        rightSpeed = Speed;
        analogWrite(ena, leftSpeed);
        analogWrite(enb, rightSpeed);
      }
      analogWrite(ena, 0);
      analogWrite(enb, 0);
      delay(100);
      while (!(side_distance < 30 && side_distance > 0) && digitalRead(sens4) != LOW &&  digitalRead(sens3) != LOW) { // לא רואה
        side_distance = side_sonar.ping_cm();

        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        leftSpeed = Speed;
        rightSpeed = Speed;
        analogWrite(ena, leftSpeed);
        analogWrite(enb, rightSpeed);
      }
      analogWrite(ena, 0);
      analogWrite(enb, 0);
      delay(100);
    }
  }

  if (digitalRead(sens2) == LOW && digitalRead(sens5) == LOW) { // אם שתי החיישנים חיצונים רואים שחור                                                               // לבדוק חיישן צבע
    leftSpeed = 0;
    rightSpeed = 0;
    analogWrite(ena, leftSpeed);
    analogWrite(enb, rightSpeed);
    digitalWrite(13, HIGH);
    LeftGreenFrequency = pulseIn(LeftSensorOut, LOW); // בודק חיישן צבע שמאל 
    Serial.print(" LG = ");
    Serial.print(LeftGreenFrequency);
    Serial.print("  ");
    RightGreenFrequency = pulseIn(RightSensorOut, LOW);
    // Printing the GREEN (G) value  
    Serial.print(" RG = ");
    Serial.print(RightGreenFrequency);
    Serial.print("  ");

    if (RightGreenFrequency > 50 && LeftGreenFrequency > 50){
      Serial.println("U turn");
      digitalWrite(led,HIGH);
      delay(100);
      digitalWrite(led,LOW);
      delay(100);
      digitalWrite(led,HIGH);
      delay(100);
      digitalWrite(led,LOW);
      delay(100);
      digitalWrite(led,HIGH);
      delay(100);
      digitalWrite(led,LOW);
      delay(100);
      analogWrite(ena, 0);
      analogWrite(enb, 0);
      delay(1000);
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      int counter = 0;
      while(counter<4){
        leftSpeed= Speed;
        rightSpeed= Speed;
        analogWrite(ena, leftSpeed);
        analogWrite(enb, rightSpeed);
        delay(150);
        if(digitalRead(sens4) != LOW){
          counter++;
        }
      }
    }// u turn

    else if (RightGreenFrequency > 50 && LeftGreenFrequency < 50) {
      Serial.println("right");
      analogWrite(ena, 0);
      analogWrite(enb, 0);
      delay(1000);
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(ena, Speed);
      analogWrite(enb, Speed);
      delay(200);
      analogWrite(ena, 0);
      analogWrite(enb, 0);
      delay(500);
      while (digitalRead(sens4) != LOW) {
        Serial.println("while");
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        leftSpeed = Speed;
        rightSpeed = 0;
        analogWrite(ena, leftSpeed);
        analogWrite(enb, rightSpeed);
      }
    } // right

    else if (LeftGreenFrequency > 50 && RightGreenFrequency < 50) {
      Serial.println("left");
      analogWrite(ena, 0);
      analogWrite(enb, 0);
      delay(1000);
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(ena, Speed);
      analogWrite(enb, Speed);
      delay(200);
      analogWrite(ena, 0);
      analogWrite(enb, 0);
      delay(1000);
      while (digitalRead(sens4) != LOW) {
        Serial.println("while");
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        leftSpeed = 0;
        rightSpeed = Speed;
        analogWrite(ena, leftSpeed);
        analogWrite(enb, rightSpeed);
      }
    } // left
    else if (RightGreenFrequency < 50 && LeftGreenFrequency < 50) {
      Serial.println("skip turn");
      analogWrite(ena, 0);
      analogWrite(enb, 0);
      delay(1000);
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(ena, Speed);
      analogWrite(enb, Speed);
      delay(100);
      analogWrite(ena, 0);
      analogWrite(enb, 0);
    }//continue
  }
  // line follower
        else if (digitalRead(sens2) == LOW) {

        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        leftSpeed = Speed;
        rightSpeed = 0;
      } 
      else if (digitalRead(sens3) == LOW) {
        isLeft = true;
        currentMillis = millis();

        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        leftSpeed = Speed;
        rightSpeed = SlowSpeed;

      } 
      else if (digitalRead(sens4) == LOW) {
        isLeft = false;
        currentMillis = millis();

        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        leftSpeed = SlowSpeed;
        rightSpeed = Speed;
      } 
      else if (digitalRead(sens5) == LOW) {

        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        leftSpeed = 0;
        rightSpeed = Speed;
      } 
         else if (digitalRead(sens1) == LOW) {
 while (digitalRead(sens3) != LOW) { //כל עוד החיישן האמצעי לא מוצא קו תסתובב 90 מעלות
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      leftSpeed = turnSpeed;
      rightSpeed = turnSpeed;
      analogWrite(ena, leftSpeed);
      analogWrite(enb, rightSpeed);
    }
      } 

  else if ((digitalRead(sens6)  == LOW ||digitalRead(sens5) == LOW )&& (digitalRead(sens2) == HIGH ||digitalRead(sens1) == HIGH )) {// חיישן שמאלי מזהה קו ימני
    while ( digitalRead(sens4) != LOW) {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      leftSpeed = turnSpeed;
      rightSpeed = turnSpeed;
      analogWrite(ena, leftSpeed);
      analogWrite(enb, rightSpeed);

    }
  } else if ((digitalRead(sens2)  == LOW ||digitalRead(sens1) == LOW )&& (digitalRead(sens5) == HIGH ||digitalRead(sens6) == HIGH )) { // חיישן ימני מזהה קו והשמאלי
  
    // לא מזהה קו לפנות 90 מעלות
    while (digitalRead(sens3) != LOW) { //כל עוד החיישן האמצעי לא מוצא קו תסתובב 90 מעלות
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      leftSpeed = turnSpeed;
      rightSpeed = turnSpeed;
      analogWrite(ena, leftSpeed);
      analogWrite(enb, rightSpeed);
    }
  } else if (digitalRead(sens6) != LOW &&
    digitalRead(sens5) != LOW &&
    digitalRead(sens4) != LOW &&
    digitalRead(sens3) != LOW &&
    digitalRead(sens2) != LOW &&
    digitalRead(sens1) != LOW) {
            if(!isLeft){
              leftSpeed = Speed;
              rightSpeed = SlowSpeed;
              isLeft = true;
            }
            else{
              leftSpeed = SlowSpeed + 30;
              rightSpeed = Speed;
              isLeft = false;
            }
              digitalWrite(in1, LOW);
              digitalWrite(in2, HIGH);
              digitalWrite(in3, LOW);
              digitalWrite(in4, HIGH);

  
  }//קו קטוע
  // prints+delay
    analogWrite(ena, leftSpeed);
    analogWrite(enb, rightSpeed);
    Serial.print(leftSpeed);
    Serial.print(' ');
    Serial.println(rightSpeed);
    Serial.print(' ');
    Serial.print("sens1 = ");
    Serial.print(digitalRead(sens1));
    Serial.print(' ');
    Serial.print("sens2 = ");
    Serial.print(digitalRead(sens2));
    Serial.print(' ');
    Serial.print("sens3 = ");
    Serial.print(digitalRead(sens3));
    Serial.print(' ');
    Serial.print("sens4 = ");
    Serial.print(digitalRead(sens4));
    Serial.print(' ');
    Serial.print("sens5 = ");
    Serial.print(digitalRead(sens5));
    Serial.print(' ');
    Serial.print("sens6 = ");
    Serial.print(digitalRead(sens6));
    Serial.print(' ');
    delay(50);
}