#include "DayOrNight.h"
#include <Servo.h>

const int PhotoResistorPin = 0; // A0
const int ElectroMagnetControllerPin = 2; // D2
const int ServoControllerPin = 3; // D3
const int ServoControllerOpenPulse = 800;
const int ServoControllerClosePulse = 1700;
const int PhotoResistorThreshold = 800;
const int PhotoResistorThresholdIndicatorPin = 13;

Servo myservo;  // create servo object to control a servo
DayOrNight *dayOrNight;

void setup() {
    pinMode(ElectroMagnetControllerPin, OUTPUT);
    pinMode(ServoControllerPin, OUTPUT);
    pinMode(PhotoResistorThresholdIndicatorPin, OUTPUT);
    myservo.attach(ServoControllerPin);
    Serial.begin(9600);
    dayOrNight = new DayOrNight(readPhotoResistor, PhotoResistorThreshold);
}

int readPhotoResistor() {
    return analogRead(PhotoResistorPin);
}

void electroMagnetsOn() {
    digitalWrite(ElectroMagnetControllerPin, HIGH);
}
void electroMagnetsOff() {
    digitalWrite(ElectroMagnetControllerPin, LOW);
}

void gateStartOpen() {
    if (!myservo.attached()) {
        myservo.attach(ServoControllerPin);
    }
    myservo.writeMicroseconds(ServoControllerOpenPulse);
}

void gateStartClose() {
    if (!myservo.attached()) {
        myservo.attach(ServoControllerPin);
    }
    myservo.writeMicroseconds(ServoControllerClosePulse);
}

void gateStop() {
    myservo.detach();
}

// This is to try to get something close to proper intervals
int delayInterval(int interval) {
    static int delayIntervalLastTime = millis();
    unsigned long thisTime = millis();
    int delay_ms;
    if (thisTime < delayIntervalLastTime) {
      //millis has overflowed, happens every 50 days
      delay_ms = interval - (thisTime + (((unsigned long)-1l) - delayIntervalLastTime));
    } else {
      delay_ms = interval - (thisTime - delayIntervalLastTime);
    }

    delay(delay_ms);

    delayIntervalLastTime = millis();
}
void loop() {

    delayInterval(100);
    dayOrNight->step();

    digitalWrite(PhotoResistorThresholdIndicatorPin,
                    dayOrNight->aboveThreshold() ? LOW : HIGH);

    Serial.println(dayOrNight->secondMean->getMean());
}
