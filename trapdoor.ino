#include "DayOrNight.h"
#include "GateController.h"
#include <Servo.h>
#include "Consts.h"

DayOrNight dayOrNight;
GateController gate;

void setup() {
    Serial.begin(9600);
}

unsigned long now = 0;

void loop() {
    static int wasDay = true;
    now = millis();
    dayOrNight.step(now);
    gate.step(now);

    if (!gate.busy()) {
        int isDay = dayOrNight.isDay();

        if (isDay && !wasDay) {
            Serial.print(" Open!");
            gate.open(now);
        } else if (!isDay && wasDay) {
            Serial.print(" Close!");
            gate.close(now);
        }
        wasDay = isDay;
    }
}
