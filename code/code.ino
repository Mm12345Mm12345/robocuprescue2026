// pins
#define ena 2
#define in1 3
#define in2 4
#define in3 5
#define in4 6
#define enb 7

#define LEFT true
#define RIGHT false

#define leftSensor 28
#define centerSensor 27
#define rightSensor 26

const int speed = 200;

bool current_turn = LEFT;

long long current_millis = 0;
long long start_millis = 0;

const int forward_check_time = 500;

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
}

void forward_a_bit(){
  start_millis = millis();
  current_millis = millis();

  while(current_millis - start_millis < forward_check_time){
    current_millis = millis();
    forward();
  }

  current_turn ? left() : right();
}

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


  if (digitalRead(leftSensor)==HIGH && digitalRead(centerSensor)==HIGH && digitalRead(rightSensor)==HIGH){
    forward_a_bit();
  }
  
  if (digitalRead(leftSensor)==HIGH && digitalRead(centerSensor)==LOW && digitalRead(rightSensor)==HIGH)
  {
    forward();
  }
  else if (digitalRead(leftSensor)==LOW && digitalRead(centerSensor)==HIGH && digitalRead(rightSensor)==HIGH)
  {
    left();
    current_turn = LEFT;
  }
  else if (digitalRead(leftSensor)==HIGH && digitalRead(centerSensor)==HIGH && digitalRead(rightSensor)==LOW)
  {
    right();
    current_turn = RIGHT;
  }
  // if (digitalRead(leftSensor)==LOW && digitalRead(centerSensor)==LOW && digitalRead(rightSensor)==HIGH)
  // {
  //   digitalWrite(in1,LOW);
  //   digitalWrite(in2,HIGH);
  //   analogWrite(ena,200);
  //   digitalWrite(in3,HIGH);
  //   digitalWrite(in4,LOW);
  //   analogWrite(enb,200);
  // }
  // if (digitalRead(leftSensor)==HIGH && digitalRead(centerSensor)==LOW && digitalRead(rightSensor)==LOW)
  // {
  //   digitalWrite(in1,HIGH);
  //   digitalWrite(in2,LOW);
  //   analogWrite(ena,200);
  //   digitalWrite(in3,LOW);
  //   digitalWrite(in4,HIGH);
  //   analogWrite(enb,200);
  // }
}