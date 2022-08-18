#include <Arduino.h>
#include <DcMotorLibrary.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

DCMotor m1("Motor 1", AFMS.getMotor(1), 5000, 8000, 255);
DCMotor m2("M 2", AFMS.getMotor(2), 3000, 1000, 255);
DCMotor m3("M 3", AFMS.getMotor(3), 3000, 2000, 255);

const int sensorPin = 2;
volatile byte state = LOW;

const long interval = 8000;
unsigned long current_time;
unsigned long last_trigger = 0;
boolean startTimer = false;

//interrupt to handle the motion detection at PIR

void detectsMovement() {
  Serial.println("Motion detected");
  startTimer = true;
  last_trigger = millis();
}

void setup() {
    Serial.begin(9600);
    AFMS.begin();

    Serial.println("Motor Shield found.");
    pinMode(sensorPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(sensorPin), detectsMovement, RISING);
}

void loop() {
  m1.update();
  current_time = millis();
  if(startTimer && (millis() - last_trigger > interval)) {
    Serial.println("Motion stopped...");
    m2.stopMotor();
    startTimer = false;
  }
  if (startTimer == true) {
    m2.startMotor();
  }
  // int value = digitalRead(sensorPin);
  /* if (state == HIGH) {
    Serial.println("Motion high!!");
    m2.startMotor();
    m3.startMotor();
  }
  if (state == HIGH) {
    m2.stopMotor();
    m3.stopMotor();
  } */
}