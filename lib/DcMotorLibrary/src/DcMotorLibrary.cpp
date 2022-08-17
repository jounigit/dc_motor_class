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
    init();
}

void DCMotor::init() {
    this->startNow = false;
    this->stopNow = false;
}

void DCMotor::startMotor() {
    startNow = true;
}

void DCMotor::stopMotor() {
    stopNow = true;
}

void DCMotor::update() {
    if (startNow) {
        Serial.print("Run ");
        Serial.print(name);
        Serial.println('!');
        startNow = false;
        motor->setSpeed(spd);
        motor->run(FORWARD);
        startTime = millis();
        running = true;
    }

    if (stopNow) {
        Serial.print(name);
        Serial.println(" Time Elapsed!");
        stopNow = false;
        motor->setSpeed(0);
        motor->run(RELEASE);
        stopTime = millis();
        running = false;
    }

    if (running && (millis() - startTime > runTime)) stopNow = true;

    if (!running && (millis()-stopTime > pauseTime)) startNow = true;
}