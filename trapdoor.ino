#include "DayOrNight.h"
#include <Servo.h>
#include "Pins.h"

Servo myservo;  // create servo object to control a servo
DayOrNight *dayOrNight;

void setup() {
    pinMode(ELECTRO_MAGNET_CONTROLLER_PIN, OUTPUT);
    pinMode(SERVO_CONTROLLER_PIN, OUTPUT);
    Serial.begin(9600);
    dayOrNight = new DayOrNight();
}

void electroMagnetsOn() {
    digitalWrite(ELECTRO_MAGNET_CONTROLLER_PIN, HIGH);
}
void electroMagnetsOff() {
    digitalWrite(ELECTRO_MAGNET_CONTROLLER_PIN, LOW);
}

void gateStartOpen() {
    if (!myservo.attached()) {
        myservo.attach(SERVO_CONTROLLER_PIN);
    }
    myservo.writeMicroseconds(SERVO_CONTROLLER_OPEN_PULSE);
}

void gateStartClose() {
    if (!myservo.attached()) {
        myservo.attach(SERVO_CONTROLLER_PIN);
    }
    myservo.writeMicroseconds(SERVO_CONTROLLER_CLOSE_PULSE);
}

void gateStop() {
    myservo.detach();
}


void loop() {
    static int wasDay = true;
    static unsigned long gateTime = 0;

    dayOrNight->step();

    int isDay = dayOrNight->isDay();

    if (gateTime == 0) {
        if (isDay && !wasDay) {
            Serial.print(" Open!");
            gateStartOpen();
            electroMagnetsOn();
            gateTime = millis();
        } else if (!isDay && wasDay) {
            Serial.print(" Close!");
            gateStartClose();
            electroMagnetsOn();
            gateTime = millis();
        }
    } else {

        if (millis() > gateTime + 5000 ) {
            Serial.print(" Transitioned!");
            gateTime = 0;
            gateStop();
        }
        if (millis() > gateTime + 500 ) {
            electroMagnetsOff();
        }

    }
    wasDay = isDay;
}
