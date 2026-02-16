#include <NewPing.h>
  int Speed = 65;
  int SlowSpeed = 0;
  int turnSpeed = 55;

// pins
#define ena 2
#define in1 3
#define in2 4
#define in3 5
#define in4 6
#define enb 7

#define leftSensor 28
#define centerSensor 27
#define rightSensor 26

#define front_trigPin 22
#define front_echoPin 23
  long duration;
  long distance;
int numberOfSamples = 10, counter=0;
long sum=0; 

/*#define SIDE_TRIGGER_PIN 22 // Arduino pin tied to trigger pin on the ultrasonic sensor.
  #define SIDE_ECHO_PIN 23 // Arduino pin tied to echo pin on the ultrasonic sensor.

  #define FRONT_TRIGGER_PIN 33 // Arduino pin tied to trigger pin on the ultrasonic sensor.
  #define FRONT_ECHO_PIN 32 // Arduino pin tied to echo pin on the ultrasonic sensor.
  #define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.*/*
void setup() {
  // put your setup code here, to run once:
pinMode(ena,OUTPUT);
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
pinMode(enb,OUTPUT);

pinMode(leftSensor,INPUT);
pinMode(centerSensor,INPUT);
pinMode(rightSensor,INPUT);

Serial.begin(9600);

pinMode(front_trigPin, OUTPUT);
pinMode(front_echoPin, INPUT);
Serial.begin(9600);
}

void forward  () 
{
  digitalWrite(in1,HIGH);
digitalWrite(in2,LOW);
analogWrite(ena,200);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);
analogWrite(enb,200);
}

void right() {
 digitalWrite(in1,LOW);
digitalWrite(in2,LOW);
analogWrite(ena,200);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);
analogWrite(enb,200);
}

void left() {
 digitalWrite(in1,HIGH);
digitalWrite(in2,LOW);
analogWrite(ena,200);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);
analogWrite(enb,200);
}
void stop() {
   digitalWrite(in1,HIGH);
digitalWrite(in2,LOW);
analogWrite(ena,0);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);
analogWrite(enb,0);
}

void loop() {
  Serial.print(digitalRead(leftSensor));
  Serial.print("\t");
  Serial.print(digitalRead(centerSensor));
  Serial.print("\t");
  Serial.println(digitalRead(rightSensor));

  
  if (digitalRead(leftSensor)==HIGH && digitalRead(centerSensor)==LOW && digitalRead(rightSensor)==HIGH)
   {
  // forward();
  }
  else if (digitalRead(leftSensor)==LOW && digitalRead(centerSensor)==HIGH && digitalRead(rightSensor)==HIGH)
   {
   left();
  }
  else if (digitalRead(leftSensor)==HIGH && digitalRead(centerSensor)==HIGH && digitalRead(rightSensor)==LOW)
   {
   right();
  }
  if (digitalRead(leftSensor)==LOW && digitalRead(centerSensor)==LOW && digitalRead(rightSensor)==HIGH)
    {
       digitalWrite(in1,LOW);
       digitalWrite(in2,HIGH);
       analogWrite(ena,200);
       digitalWrite(in3,HIGH);
       digitalWrite(in4,LOW);
       analogWrite(enb,200);
    }
  if (digitalRead(leftSensor)==HIGH && digitalRead(centerSensor)==LOW && digitalRead(rightSensor)==LOW)
    {
       digitalWrite(in1,HIGH);
       digitalWrite(in2,LOW);
       analogWrite(ena,200);
       digitalWrite(in3,LOW);
       digitalWrite(in4,HIGH);
       analogWrite(enb,200);


  if (distance <5)
  {
    
  }
    }
  else{
   // stop();

 while(counter <numberOfSamples){
    
  getDistance();
    
    if(distance>3 && distance <300){
    sum+=distance;
      counter++;
    }
  }
    
  Serial.print("average distance[cm] = ");
  Serial.println(sum*1.0/counter);
  delay(10);
  counter = 0;
  sum=0;
  }

void getDistance(){
  digitalWrite(front_trigPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(front_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(front_trigPin, LOW);
  
  duration = pulseIn(front_echoPin,HIGH);
  distance = duration/58.1;
  
}

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
/*


  if (digitalRead(leftSensor)==LOW && digitalRead(centerSensor)==HIGH && digitalRead(rightSensor)==LOW)
   {
  forward();
  }
  if (digitalRead(leftSensor)==HIGH && digitalRead(centerSensor)==LOW && digitalRead(rightSensor)==LOW)
  {
   left();
  }
  if (digitalRead(leftSensor)==LOW && digitalRead(centerSensor)==LOW && digitalRead(rightSensor)==HIGH) 
  {
    right();
}
*/
}