#include <Arduino.h>
#include <DcMotorLibrary.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

DCMotor m1("Motor 1", AFMS.getMotor(1), 5000, 8000, 255);
DCMotor m2("Motor 2", AFMS.getMotor(2), 3000, 1000, 255);
DCMotor m3("Motor 3", AFMS.getMotor(3), 3000, 2000, 255);

const int pirIn = 2;

void setup() {
    Serial.begin(9600);

    if (!AFMS.begin()) {
        Serial.println("Could not find Motor Shield. Check wiring.");
        while (1);
    }

    Serial.println("Motor Shield found.");
    pinMode(pirIn, INPUT);
}

void loop() {
  m1.update();
  int value = digitalRead(pirIn);
  if (value == HIGH) {
      m2.update();
      m3.update();
  }
  if (value == LOW) {
    m2.stopMotor();
    m3.stopMotor();
  }
}