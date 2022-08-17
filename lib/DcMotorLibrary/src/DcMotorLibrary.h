#ifndef DC_MOTOR_LIBRARY_H
#define DC_MOTOR_LIBRARY_H

#include <Arduino.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_MotorShield.h>

class DCMotor
{
private:
    const char *name;
    Adafruit_DCMotor *motor;
    unsigned long runTime;
    unsigned long pauseTime;
    unsigned long spd;
    unsigned long startTime; 
    unsigned long stopTime;
    unsigned long previousMillis; 
    bool startNow;
    bool stopNow;
    bool running;
public:
    DCMotor(
        const char *_name, 
        Adafruit_DCMotor *_motor, 
        unsigned long _runTime, 
        unsigned long _pauseTime, 
        unsigned long _spd
    );
    void init();
    void startMotor();
    void stopMotor();
    void update();
};

#endif