// #include <NewPing.h>

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


// #define front_trigPin 11
// #define front_echoPin 10

// #define side_trigPin 9
// #define side_echoPin 8

// NewPing front_sonar(front_trigPin, front_echoPin, MAX_DISTANCE);
// NewPing side_sonar(front_echoPin, FRONT_ECHO_PIN, MAX_DISTANCE);

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

// Variables to store frequency
int redFrequency = 0;
int greenFrequency = 0;

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

  // Setting frequency-scaling to 20%
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

  Serial.begin(9600);

}

bool isGreen(bool direction){
  int greenValue = getGreen(direction);
  int redValue = getRed(direction);
  int blueValue = getBlue(direction);

  // logic

  return true;
}

// this is forward
void forward() {
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(ena, speed);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enb, speed);
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
  analogWrite(ena,200);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  analogWrite(enb,200);
}
void tank_left(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(ena,200);
  digitalWrite(in3,HIGH);
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
  // Serial.print(digitalRead(leftSensor));
  // Serial.print("\t");
  // Serial.print(digitalRead(centerSensor));
  // Serial.print("\t");
  // Serial.println(digitalRead(rightSensor));

  if (millis() - timer > colorCheckInterval){
    Serial.print("Green Left: ");
    Serial.print(getGreen(LEFT));
    Serial.print("  Green Right: ");
    Serial.print(getGreen(RIGHT));
    Serial.print("   ");
    Serial.print("Red Left: ");
    Serial.print(getRed(LEFT));
    Serial.print("  Red Right: ");
    Serial.print(getRed(RIGHT));
    Serial.print("   ");
    Serial.print("Blue Left: ");
    Serial.print(getBlue(LEFT));
    Serial.print("  Blue Right: ");
    Serial.println(getBlue(RIGHT));

    timer = millis();
  }

  bool isGreenRight = isGreen(RIGHT);
  bool isGreenLeft = isGreen(LEFT);


  if (isGreenRight && isGreenLeft){
    tank_right();
    delay(colorTurnTime);
  }
  else if (isGreenRight){
    right();
    delay(colorTurnTime);
  }
  else if (isGreenLeft){
    left();
    delay(colorTurnTime);
  }  
  
  // if (digitalRead(leftSensor)==HIGH && digitalRead(centerSensor)==LOW && digitalRead(rightSensor)==HIGH)
  // {
  // // forward();
  // }
  if (digitalRead(leftSensor)==LOW && digitalRead(centerSensor)==HIGH && digitalRead(rightSensor)==HIGH)
  {
    left();
  }
  else if (digitalRead(leftSensor)==HIGH && digitalRead(centerSensor)==HIGH && digitalRead(rightSensor)==LOW)
  {
    right();
  }
  if (digitalRead(leftSensor)==LOW && digitalRead(centerSensor)==LOW && digitalRead(rightSensor)==HIGH)
  {
    tank_left();
  }
  if (digitalRead(leftSensor)==HIGH && digitalRead(centerSensor)==LOW && digitalRead(rightSensor)==LOW)
  {
    tank_left();
  }
  // else{
  //   // stop();
  // }

  // while(counter < numberOfSamples){
    
  // getDistance();
    
  //   if(distance > 3 && distance < 300){
  //     sum += distance;
  //     counter++;
  //   }
  // }
    
  // Serial.print("average distance[cm] = ");
  // Serial.println(sum/counter);
  // delay(10);
  // counter = 0;
  // sum=0;
}

// int getDistance(){
//   digitalWrite(front_trigPin, LOW);
//   delayMicroseconds(2); 
//   digitalWrite(front_trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(front_trigPin, LOW);
  
//   duration = pulseIn(front_echoPin,HIGH);
//   distance = duration/58.1;
// }