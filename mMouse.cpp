#include <cmath>
#include "mMouse.h"

#define MAX_AVERAGE 500
#define USED_AVERAGE 25
#define KP = 0.3

#define LEFT_SPEED 100
#define RIGHT_SPEED 100

mMouse::mMouse() :
    origLeftSensor(0),
    origRightSensor(0),
    origFrontSensor(0),
    lastLeftSensor(0),
    lastRightSensor(0),
    lastFrontSensor(0),
    cellX(0),
    cellY(0),
    direction(North)
{}

void initCalibrate() {
    int left = 0; int right = 0; int front = 0;
    for (unsigned i = 0; i < m_AVERAGE; ++i) {
        left += analogRead(sensorL);
        right += analogRead(sensorR);
        front += analogRead(sensorF);
    }
    origLeftSensor = left / MAX_AVERAGE;
    origRightSensor = right / MAX_AVERAGE;
    origFrontSensor = front / MAX_AVERAGE;
}

void repositionMouse() {
    // if mouse is stuck, 'unstuck' it by going back to a 
    // position such that sensors are similar to initial values
}

int getLeftSensor() {
    int reading = analogRead(sensorL);
    reading = abs(reading - origLeftSensor);
    return reading;
}

int getRightSensor() {
    int reading = analogRead(sensorR);
    reading = abs(reading - origRightSensor);
    return reading;
}

int getFrontSensor() {
    int reading = analogRead(sensorF);
    reading = abs(reading - origFrontSensor);
    return reading;
}

int avgLeftSensor(unsigned count) {
    if (count > MAX_AVERAGE) {
        count = MAX_AVERAGE;
    }
    int avgReading = 0;
    for (unsigned i = 0; i < count; ++i) {
        avgReading += getLeftSensor();
    }
    avgReading /= MAX_AVERAGE;
    return avgReading;
}

int avgRightSensor(unsigned count) {
    if (count > MAX_AVERAGE) {
        count = MAX_AVERAGE;
    }
    int avgReading = 0;
    for (unsigned i = 0; i < count; ++i) {
        avgReading += getRightSensor();
    }
    avgReading /= MAX_AVERAGE;
    return avgReading;
}

int avgFrontSensor(unsigned count) {
    if (count > MAX_AVERAGE) {
        count = MAX_AVERAGE;
    }
    int avgReading = 0;
    for (unsigned i = 0; i < count; ++i) {
        avgReading += getFrontSensor();
    }
    avgReading /= MAX_AVERAGE;
    return avgReading;
}

void calcAverageSensors(unsigned count) {
    lastLeftSensor = avgLeftSensor(count);
    lastRightSensor = avgRightSensor(count);
    lastFrontSensor = avgFrontSensor(count);
}

int getLeftEncoder() {
    return -1;
}

int getRightEncoder() {
    return -1;
}

void setMouseLocation(unsigned x, unsigned y) {
    cellX = x;
    cellY = y;
}

unsigned getCellX() {
    return cellX;
}

unsigned getCellY() {
    return cellY;
}

void stopMouse(unsigned ms) {
    digitalWrite(ENL, LOW);
    digitalWrite(mLR, LOW);
    digitalWrite(mLF, LOW);
  
    digitalWrite(ENR, LOW);
    digitalWrite(mRF, LOW);
    digitalWrite(mRR, LOW);
    
    delay(ms);
}

void moveForward(double leftMotor, double rightMotor) {
    analogWrite(ENL, leftMotor);
    digitalWrite(mLR, LOW);
    digitalWrite(mLF, HIGH);
  
    analogWrite(ENR, rightMotor);
    digitalWrite(mRF, HIGH);
    digitalWrite(mRR, LOW);
}

void centerMouse() {
    calcAverageSensors(USED_AVERAGE);
    if (lastLeftSensor < lastRightSensor) {
        moveForward(LEFT_SPEED , RIGHT_SPEED - ((lastLeftSensor - lastRightSensor) * KP));
    }
    if (lastLeftSensor > lastRightSensor) {
        moveForward(LEFT_SPEED - ((lastLeftSensor - lastRightSensor) * KP), RIGHT_SPEED);
    }
}

void turnRight() {
    // need to figure out new encoders...
}

void turnLeft() {
    // need to figure out new encoders...
}

void turnAround() {
    // need to figure out new encoders...
}

bool checkLeftWall(unsigned offset) {
    if (avgLeftSensor(USED_AVERAGE) > origLeftSensor + offset) {
        return true;
    }
    return false;
}

bool checkRightWall(unsigned offset) {
    if (avgRightSensor(USED_AVERAGE) > origRightSensor + offset) {
        return true;
    }
    return false;
}

bool checkFrontWall(unsigned offset) {
    if (avgFrontSensor(USED_AVERAGE) > origFrontSensor + offset) {
        return true;
    }
    return false;
}
