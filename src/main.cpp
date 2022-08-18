#include <Arduino.h>
#include <DcMotorLibrary.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

DCMotor m1("Motor 1", AFMS.getMotor(1), 5000, 8000, 255);
DCMotor m2("M 2", AFMS.getMotor(2), 3000, 1000, 255);
DCMotor m3("M 3", AFMS.getMotor(3), 3000, 2000, 255);

const int sensorPin = 2;
volatile byte state = LOW;

const long interval = 10000;
unsigned long currentTime;
unsigned long startTrigger = 0;
unsigned long stopTrigger = 0;
boolean startTimer = false;

void detectsMovement() {
  Serial.println("Motion detected");
  startTimer = true;
  startTrigger = millis();
}

void setup() {
  Serial.begin(9600);
  AFMS.begin();

  Serial.println("Motor Shield found.");
  pinMode(sensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensorPin), detectsMovement, CHANGE);
}

void loop() {
  m1.update();
  currentTime = millis();

  if(startTimer && (millis() - startTrigger > interval)) {
    Serial.println("Motion stopped...");
    stopTrigger = millis();
    startTimer = false;
  }

  (startTimer) ? m2.startMotor() : m2.stopMotor();


  if (startTimer && (millis() - startTrigger > 3000)) m3.startMotor();

  if (!startTimer && (millis() - stopTrigger > 5000)) m3.stopMotor();
}