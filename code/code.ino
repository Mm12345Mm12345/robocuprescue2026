#include <Ultrasonic.h>

// pins
#define ena 2
#define in1 3
#define in2 4
#define in3 5
#define in4 6
#define enb 7

#define leftSensor 28
#define centerSensor 29
#define rightSensor 26


#define front_trigPin 11
#define front_echoPin 10

#define side_trigPin 9
#define side_echoPin 8

Ultrasonic ultrasonic_front(front_trigPin, front_echoPin);
Ultrasonic ultrasonic_side(side_trigPin, side_echoPin);

const int object_detection_distance = 12; // cm

int object_evation_timer = 0;
const int object_evation_time = 100;


#define LEFT_S0 46
#define LEFT_S1 47
#define LEFT_S2 48
#define LEFT_S3 49
#define LEFT_sensorOut 22

#define RIGHT_S0 50
#define RIGHT_S1 51
#define RIGHT_S2 52
#define RIGHT_S3 53
#define RIGHT_sensorOut 23

#define RIGHT false
#define LEFT true


int getGreen(bool direction){
  digitalWrite(direction ? LEFT_S2 : RIGHT_S2, HIGH);
  digitalWrite(direction ? LEFT_S3 : RIGHT_S3, HIGH);
  int greenFreq = pulseIn(direction ? LEFT_sensorOut : RIGHT_sensorOut, LOW);
  return greenFreq;
}

int getRed(bool direction){
  digitalWrite(direction ? LEFT_S2 : RIGHT_S2, LOW);
  digitalWrite(direction ? LEFT_S3 : RIGHT_S3, LOW);
  int redFreq = pulseIn(direction ? LEFT_sensorOut : RIGHT_sensorOut, LOW);
  return redFreq;
}

int getBlue(bool direction){
  digitalWrite(direction ? LEFT_S2 : RIGHT_S2, LOW);
  digitalWrite(direction ? LEFT_S3 : RIGHT_S3, HIGH);
  int blueFreq = pulseIn(direction ? LEFT_sensorOut : RIGHT_sensorOut, LOW);
  return blueFreq;
}



const int colorCheckInterval = 50;
const int colorTurnTime = 2000;
int timer = 0;


const int speed = 200;

long duration;
long distance;
long sum = 0;

int numberOfSamples = 10, counter=0;


void setup() {
  // color sensors
  pinMode(LEFT_S0, OUTPUT);
  pinMode(LEFT_S1, OUTPUT);
  pinMode(LEFT_S2, OUTPUT);
  pinMode(LEFT_S3, OUTPUT);
  pinMode(LEFT_sensorOut, INPUT);
  
  pinMode(RIGHT_S0, OUTPUT);
  pinMode(RIGHT_S1, OUTPUT);
  pinMode(RIGHT_S2, OUTPUT);
  pinMode(RIGHT_S3, OUTPUT);
  pinMode(RIGHT_sensorOut, INPUT);

  // Setting frequency-scaling to 100%
  digitalWrite(LEFT_S0, HIGH);
  digitalWrite(LEFT_S1, HIGH);
  digitalWrite(RIGHT_S0, HIGH);
  digitalWrite(RIGHT_S1, HIGH);
  
  pinMode(ena,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(enb,OUTPUT);

  pinMode(leftSensor,INPUT);
  pinMode(centerSensor,INPUT);
  pinMode(rightSensor,INPUT);

  // pinMode(13, OUTPUT);

  Serial.begin(9600);
  forward();

}

bool isGreen(bool direction){
  int greenValue = getGreen(direction);
  int redValue = getRed(direction);
  int blueValue = getBlue(direction);

  Serial.print(greenValue);
  Serial.print(" ");
  Serial.print(redValue);
  Serial.print(" ");
  Serial.print(blueValue);
  Serial.print("  ");

  if (redValue > 13 && greenValue > 13 && blueValue > 13){
    return true;
  }
  else{
    return false;
  }
}

// bool isRed(bool direction){
//   int greenValue = getGreen(direction);
//   int redValue = getRed(direction);
//   int blueValue = getBlue(direction);

//   // logic

//   return true;
// }

void intersection(){
  bool isGreenRight = isGreen(RIGHT);
  bool isGreenLeft = isGreen(LEFT);

  delay(200);
  stop();
  delay(1000);

  if (!isGreenRight && !isGreenLeft){
    forward();
    delay(500);
  }
  else if (isGreenRight && isGreenLeft){
    tank_right();
    delay(500);
  }
  else if (isGreenRight){
    left();
    delay(500);
  }
  else if (isGreenLeft){
    right();
    delay(500);
  }
}

void forward() {
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(ena, speed-50);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enb, speed-50);
}

void right() {
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  analogWrite(ena, speed);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enb, speed);
}

void left() {
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(ena, speed);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  analogWrite(enb, speed);
}
void tank_right(){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(ena,speed);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  analogWrite(enb,speed);
}
void tank_left(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(ena,speed);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enb,speed);
}
void stop() {
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(ena,0);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enb,0);
}

void obstacle(){
  stop();
  delay(1000);

  while (ultrasonic_side.read() > object_detection_distance + 10){
    tank_right();
    // digitalWrite(13, HIGH);
  }
  // digitalWrite(13, LOW);
  while (digitalRead(leftSensor)==HIGH && digitalRead(centerSensor)==HIGH && digitalRead(rightSensor)==HIGH){
    if (millis() < object_evation_timer + object_evation_time){
      forward();
    }
    else {
      object_evation_timer = millis();
      while(ultrasonic_side.read() > object_detection_distance + 10){
        tank_left();
      }
    }
  }
  left();
}

void loop() {
  // Serial.print(ultrasonic_front.read());
  // Serial.print("    ");
  // Serial.println(ultrasonic_side.read());
  Serial.print(digitalRead(leftSensor));
  Serial.print("\t");
  Serial.print(digitalRead(centerSensor));
  Serial.print("\t");
  Serial.println(digitalRead(rightSensor));


  // if (isRed(LEFT) || isRed(RIGHT)){
  //   stop();
  // }
  /*else */if (digitalRead(leftSensor)== LOW && digitalRead(centerSensor)== LOW && digitalRead(rightSensor)== LOW)
  {
    stop();
    intersection();
  }
  else if (digitalRead(leftSensor)==HIGH && digitalRead(centerSensor)==LOW && digitalRead(rightSensor)==HIGH)
  {
    forward();
  }
  else if (digitalRead(leftSensor)==LOW && digitalRead(rightSensor)==HIGH)
  {
    left();
  }
  else if (digitalRead(leftSensor)==HIGH && digitalRead(centerSensor)==HIGH && digitalRead(rightSensor)==LOW)
  {
    right();
  }
  // int distance = ultrasonic_front.read();
  // if (distance == 0){ distance = 357;}
  // if (distance < object_detection_distance){
  //   obstacle();
  // }
}