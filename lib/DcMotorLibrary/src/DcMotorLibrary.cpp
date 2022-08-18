#include "DcMotorLibrary.h"
#include <Arduino.h>

DCMotor::DCMotor(
    const char *_name,
    Adafruit_DCMotor *_motor,
    unsigned long _runtime,
    unsigned long _pauseTime, 
    unsigned long _spd
) {
    this->name = _name;
    this->motor = _motor;
    this->runTime = _runtime;
    this->pauseTime = _pauseTime;
    this->spd = _spd;
}

void DCMotor::startMotor() {
        // Serial.print("Run ");
        // Serial.print(name);
        // Serial.println('!');
        motor->setSpeed(spd);
        motor->run(FORWARD);
        startTime = millis();
        running = true;
}

void DCMotor::stopMotor() {
        // Serial.print(name);
        // Serial.println(" Time Elapsed!");
        // motor->setSpeed(0);
        motor->run(RELEASE);
        stopTime = millis();
        running = false;
}

void DCMotor::update() {

    if (running && (millis() - startTime > runTime)) stopMotor();

    if (!running && (millis()-stopTime > pauseTime)) startMotor();
}