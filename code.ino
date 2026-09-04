#include <Servo.h>  // library for servo motor

// -------------------- MOTOR PINS --------------------
const int FL_PWM = 3;   // Front Left wheel speed (PWM)
const int FL_IN1 = 4;
const int FL_IN2 = 7;


const int BL_PWM = 5;   // Back Left wheel speed (PWM)
const int BL_IN1 = 8;
const int BL_IN2 = 10;


const int FR_PWM = 6;   // Front Right wheel speed (PWM)
const int FR_IN1 = 11;
const int FR_IN2 = 12;


const int BR_PWM = 9;   // Back Right wheel speed (PWM)
const int BR_IN1 = A1;
const int BR_IN2 = A0;


// -------------------- ULTRASONIC --------------------
const int Trig_Pin = 2;
const int Echo_Pin = 13;


// -------------------- SERVO --------------------
Servo myServo;
const int Servo_Pin = A4;


// —----------------- Buzzer —----------------
const int Buzzer_Pin = A3;


// —--------------- LED —--------------------
const int LED_Pin = A2;


// -------------------- SETTINGS --------------------
int speedVal = 150; // motor speed (0–255)
int safeDistance = 30;  // cm
int buzzDistance = 40; //cm
int scanStep = 20;


// ----------------------------------------------------
// BASIC MOVEMENT FUNCTIONS
// ----------------------------------------------------


void stopRobot() {
  // stop all motors
  digitalWrite(FL_IN1, LOW); digitalWrite(FL_IN2, LOW);
  digitalWrite(FR_IN1, LOW); digitalWrite(FR_IN2, LOW);
  digitalWrite(BL_IN1, LOW); digitalWrite(BL_IN2, LOW);
  digitalWrite(BR_IN1, LOW); digitalWrite(BR_IN2, LOW);


  // set speed to zero
  analogWrite(FL_PWM, 0); analogWrite(FR_PWM, 0);
  analogWrite(BL_PWM, 0); analogWrite(BR_PWM, 0);
}


void driveForward(int speedVal) {
  // Left wheels forward
  digitalWrite(FL_IN1, HIGH); digitalWrite(FL_IN2, LOW);
  digitalWrite(BL_IN1, HIGH); digitalWrite(BL_IN2, LOW);


  // Right wheels forward
  digitalWrite(FR_IN1, HIGH); digitalWrite(FR_IN2, LOW);
  digitalWrite(BR_IN1, HIGH); digitalWrite(BR_IN2, LOW);


  // Set speed values
  analogWrite(FL_PWM, speedVal); analogWrite(FR_PWM, speedVal);
  analogWrite(BL_PWM, speedVal); analogWrite(BR_PWM, speedVal);
}


void moveBackward(int speedVal) {
  // Left wheels backward
  digitalWrite(FL_IN1, LOW); digitalWrite(FL_IN2, HIGH);
  digitalWrite(BL_IN1, LOW); digitalWrite(BL_IN2, HIGH);


  // Right wheels backward
  digitalWrite(FR_IN1, LOW); digitalWrite(FR_IN2, HIGH);
  digitalWrite(BR_IN1, LOW); digitalWrite(BR_IN2, HIGH);


  // Set speed values
  analogWrite(FL_PWM, speedVal); analogWrite(FR_PWM, speedVal);
  analogWrite(BL_PWM, speedVal); analogWrite(BR_PWM, speedVal);
}


void turnLeft(int speedVal) {
  // Left wheels backward
  digitalWrite(FL_IN1, LOW); digitalWrite(FL_IN2, HIGH);
  digitalWrite(BL_IN1, LOW); digitalWrite(BL_IN2, HIGH);


  // Right wheels forward
  digitalWrite(FR_IN1, HIGH); digitalWrite(FR_IN2, LOW);
  digitalWrite(BR_IN1, HIGH); digitalWrite(BR_IN2, LOW);


  // Set speed values
  analogWrite(FL_PWM, speedVal); analogWrite(FR_PWM, speedVal);
  analogWrite(BL_PWM, speedVal); analogWrite(BR_PWM, speedVal);
}


void turnRight(int speedVal) {
  // Left wheels forward
  digitalWrite(FL_IN1, HIGH); digitalWrite(FL_IN2, LOW);
  digitalWrite(BL_IN1, HIGH); digitalWrite(BL_IN2, LOW);


  // Right wheels backward
  digitalWrite(FR_IN1, LOW); digitalWrite(FR_IN2, HIGH);
  digitalWrite(BR_IN1, LOW); digitalWrite(BR_IN2, HIGH);


  // Set speed values
  analogWrite(FL_PWM, speedVal); analogWrite(FR_PWM, speedVal);
  analogWrite(BL_PWM, speedVal); analogWrite(BR_PWM, speedVal);
}


// ----------------------------------------------------
// ULTRASONIC FUNCTION
// ----------------------------------------------------
long getDistance() {
  digitalWrite(Trig_Pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_Pin, LOW);


  long duration = pulseIn(Echo_Pin, HIGH, 25000); // 25ms timeout
  if (duration == 0) {
    return 999; // no object detected
    }
  long distance = duration * 0.034 / 2;
  return distance;
}


// ----------------------------------------------------
// SCANNING FUNCTION
// ----------------------------------------------------
int scanForBestDirection() {
  int bestAngle = 90;
  long bestDist = 0;


  for (int angle = 40; angle <= 140; angle += scanStep) {
    myServo.write(angle);
    delay(200);
    long d = getDistance();
    if (d > bestDist) {
      bestDist = d;
      bestAngle = angle;
    }
  }


  myServo.write(90); // center again
  delay(200);
  return bestAngle;
}


// ----------------------------------------------------
// SETUP
// ----------------------------------------------------
void setup() {
  // motors
  pinMode(FL_IN1, OUTPUT); pinMode(FL_IN2, OUTPUT);
  pinMode(FR_IN1, OUTPUT); pinMode(FR_IN2, OUTPUT);
  pinMode(BL_IN1, OUTPUT); pinMode(BL_IN2, OUTPUT);
  pinMode(BR_IN1, OUTPUT); pinMode(BR_IN2, OUTPUT);
  pinMode(FL_PWM, OUTPUT); pinMode(FR_PWM, OUTPUT);
  pinMode(BL_PWM, OUTPUT); pinMode(BR_PWM, OUTPUT);


  // sensor
  pinMode(Trig_Pin, OUTPUT); pinMode(Echo_Pin, INPUT);


  // buzzer and led
  pinMode(Buzzer_Pin, OUTPUT); pinMode(LED_Pin, OUTPUT);


  // servo
  myServo.attach(Servo_Pin);
  myServo.write(90); // look forward


  stopRobot();
  delay(1000);
}


// ----------------------------------------------------
// MAIN LOOP
// ----------------------------------------------------


void loop() {
  int distance = getDistance();


  // movement
  if (distance > safeDistance) {
    // No object nearby
    driveForward(speedVal);
    digitalWrite(LED_Pin, LOW);
    noTone(Buzzer_Pin);
  }


  else {
    stopRobot();
    digitalWrite(LED_Pin, HIGH);
    tone(Buzzer_Pin, 1000);
    delay(100);
    int bestAngle = scanForBestDirection();
    delay(500);


    if (bestAngle < 80) {
      turnLeft(speedVal);
      delay(250);
    }


    else if (bestAngle > 100) {
      turnRight(speedVal);
      delay(250);
    }
    else {
      // No good direction
      turnRight(speedVal);
      delay(500);
    }


    stopRobot();
    delay(1000);
  }
}
