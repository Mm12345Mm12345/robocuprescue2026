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

void setup() {
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

  Serial.begin(9600);
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

  if (redValue <= 11 && redValue >= 9 && greenValue < 9 && blueValue < 9){
    return true;
  }
  else{
    return false;
  }
}

void loop() {
  // delay(5000);
  // int start_millis = millis();
  // float greenAverage = 0;
  // float redAverage = 0;
  // float blueAverage = 0;
  // float items = 0;
  // Serial.println("calculating right average...");
  // while(millis() < start_millis + 5000){
  //   int green = getGreen(RIGHT);
  //   greenAverage = ((greenAverage * items) + green)/(items+1.0);
  //   Serial.print(green);
  //   Serial.print(" ");

  //   int red = getRed(RIGHT);
  //   redAverage =   ((redAverage * items) + red)/(items+1.0);
  //   Serial.print(red);
  //   Serial.print(" ");

  //   int blue = getBlue(RIGHT);
  //   blueAverage =  ((blueAverage * items) + blue)/(items+1.0);
  //   Serial.println(blue);

  //   items++;
  // }
  // Serial.print("right green average: ");
  // Serial.print(greenAverage);
  // Serial.print("   right red average: ");
  // Serial.print(redAverage);
  // Serial.print("   right blue average: ");
  // Serial.println(blueAverage);

  // delay(5000);

  // start_millis = millis();
  // greenAverage = 0;
  // redAverage = 0;
  // blueAverage = 0;
  // items = 0;
  // Serial.println("calculating left average...");
  // while(millis() < start_millis + 5000){
  //   int green = getGreen(LEFT);
  //   greenAverage = ((greenAverage * items) + green)/(items+1.0);
  //   Serial.print(green);
  //   Serial.print(" ");

  //   int red = getRed(LEFT);
  //   redAverage =   ((redAverage * items) + red)/(items+1.0);
  //   Serial.print(red);
  //   Serial.print(" ");

  //   int blue = getBlue(LEFT);
  //   blueAverage =  ((blueAverage * items) + blue)/(items+1.0);
  //   Serial.println(blue);

  //   items++;
  // }
  // Serial.print("left green average: ");
  // Serial.print(greenAverage);
  // Serial.print("   left red average: ");
  // Serial.print(redAverage);
  // Serial.print("   left blue average: ");
  // Serial.println(blueAverage);
  Serial.print(isGreen(LEFT));
  Serial.print("    ");
  Serial.println(isGreen(RIGHT));
}
