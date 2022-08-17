#include <Arduino.h>
#include <DcMotorLibrary.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

DCMotor m1("Motor 1", AFMS.getMotor(1), 2000, 2000, 255);
DCMotor m2("Motor 2", AFMS.getMotor(2), 20000, 5000, 150);

void setup() {
    Serial.begin(9600);

    if (!AFMS.begin()) {
        Serial.println("Could not find Motor Shield. Check wiring.");
        while (1);
    }

    Serial.println("Motor Shield found.");
    m1.startMotor();
    m2.startMotor();
}

void loop() {
    m1.update();
    m2.update();
}