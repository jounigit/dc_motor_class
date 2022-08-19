#include <Arduino.h>
#include <DcMotorLibrary.h>
#include <TimerEvent.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

DCMotor m1("Motor 1", AFMS.getMotor(1), 5000, 8000, 255);
DCMotor m2("M 2", AFMS.getMotor(2), 3000, 1000, 255);
DCMotor m3("M 3", AFMS.getMotor(3), 3000, 2000, 255);

const int sensorPin = 2;
volatile byte state = LOW;

const long interval = 10000;
unsigned long now;
unsigned long startPeriod = 0;
unsigned long stopPeriod = 0;
boolean isMotion = false;

// const unsigned int timerTwoPeriod = 13;
// TimerEvent timerTwo;

void detectsMovement() {
  Serial.println("Motion detected");
  isMotion = true;
  startPeriod = millis();
}

// void timerTwoFunc() {
//   m2.startMotor();
// }

void myTimer(unsigned long myPeriod) {
  if(millis() - startPeriod >= myPeriod) {
    Serial.println("Motion stopped...");
    stopPeriod = millis();
    isMotion = false;
  }
}

void setup() {
  Serial.begin(9600);
  AFMS.begin();

  Serial.println("Motor Shield found.");
  pinMode(sensorPin, INPUT_PULLUP);
  // timerTwo.set(timerTwoPeriod, timerTwoFunc);
  attachInterrupt(digitalPinToInterrupt(sensorPin), detectsMovement, CHANGE);
}

void loop() {
  m1.update();
  now = millis();

  if(isMotion) myTimer(interval);

  /* if(isMotion && (now - startPeriod > interval)) {
    Serial.println("Motion stopped...");
    stopPeriod = millis();
    isMotion = false;
  } */

  (isMotion && (now - startPeriod > 5000)) ? m2.startMotor() : m2.stopMotor();
  // (isMotion) ? timerTwo.update() : timerTwo.disable();


  if (isMotion && (now - startPeriod > 3000)) m3.startMotor();

  if (!isMotion && (now - stopPeriod > 5000)) m3.stopMotor();
}