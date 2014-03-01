#include "GateController.h"
#include <Arduino.h>
#include "Pins.h"
#include "Util.h"


typedef enum {
    GATE_OPENING, GATE_CLOSING, GATE_CLOSED, GATE_OPEN
} GateControllerState;

GateController::GateController() {
    pinMode(MAGNET_CONTROLLER_PIN, OUTPUT);
    pinMode(SERVO_CONTROLLER_PIN, OUTPUT);
    this->state = GATE_CLOSED;
    this->magnetsActive = 0;
    this->magnetsActivationTime = 0;
}

void GateController::step(unsigned long now) {
    static int last_state = this->state;
    if (this->state != last_state) {
        Serial.print("changed state: ");
        Serial.print(last_state);
        Serial.print(" -> ");
        Serial.print(this->state);
        Serial.print(" (");
        Serial.print(now);
        Serial.println(")");
        last_state = this->state;
    }
    if (this->state == GATE_OPEN || this->state == GATE_CLOSED) {
        return;
    }
    if (this->magnetsActive) {
        if (time_diff(this->magnetsActivationTime, now) > MAGNET_ACTIVATION_TIME) {
            this->deactivateMagnets();
        }
    }
    if (this->busy() && time_diff(this->transitionStartTime, now) > GATE_ARRIVED_SIGNAL_MARGIN) {
        int arrivalSignal = analogRead(GATE_ARRIVED_PIN);
        // basically any reading that is not 1023 or 0 is ON.
        // Should typically be about 512, but let's keep plenty of margin
        int arrived = arrivalSignal > 200 && arrivalSignal < 800;
        if (arrived) {
            Serial.print("ARRIVED ");
            Serial.print(arrivalSignal);
            Serial.print(" (");
            Serial.print(this->transitionStartTime);
            Serial.println(")");

            this->state = (this->state == GATE_OPENING ? GATE_OPEN : GATE_CLOSED);
            this->servo.detach();

        }
    }
}

void GateController::open(unsigned long now) {
    if (this->state == GATE_OPEN || this->busy()) {
        return;
    }
    this->transitionStartTime=now;
    this->state = GATE_OPENING;
    this->activateMagnets(now);
    if (!this->servo.attached()) {
        this->servo.attach(SERVO_CONTROLLER_PIN);
    }
    this->servo.writeMicroseconds(SERVO_CONTROLLER_OPEN_PULSE);
}

void GateController::close(unsigned long now) {
    if (this->state == GATE_CLOSED || this->busy()) {
        return;
    }
    this->transitionStartTime=now;
    this->state = GATE_CLOSING;
    if (!this->servo.attached()) {
        this->servo.attach(SERVO_CONTROLLER_PIN);
    }
    this->servo.writeMicroseconds(SERVO_CONTROLLER_CLOSE_PULSE);
}

void GateController::activateMagnets(unsigned long now) {
    digitalWrite(MAGNET_CONTROLLER_PIN, HIGH);
    this->magnetsActivationTime = now;
    this->magnetsActive = 1;
}

void GateController::deactivateMagnets() {
    digitalWrite(MAGNET_CONTROLLER_PIN, LOW);
    this->magnetsActivationTime = 0;
    this->magnetsActive = 0;
}

int GateController::busy() {
    return this->state == GATE_CLOSING || this->state == GATE_OPENING;
}