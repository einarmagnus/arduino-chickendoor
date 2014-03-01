#include "DayOrNight.h"
#include <Arduino.h>
#include "Pins.h"
#include "Util.h"

DayOrNight::DayOrNight() {
  pinMode(PHOTO_RESISTOR_THRESHOLD_INDICATOR_PIN, OUTPUT);

  // get a sample that is somewhat stable.
  int val = 0;
  for(int i = 0; i < 5; i++) {
    val += analogRead(PHOTO_RESISTOR_PIN);
  }
  val /= 5;

  this->secondMean = new MeanTracker(10, val);
  this->minuteMean = new MeanTracker(10, val);
  this->tenMinuteMean = 0;
  this->samples = 0;
};

void DayOrNight::step(unsigned long now) {
  static unsigned long lastTime = 0;

  // we only run every 100ms
  if (time_diff(lastTime, now) < 100 ) {
    return;
  }
  lastTime=now;

  int brightness = analogRead(PHOTO_RESISTOR_PIN);
  Serial.println(brightness);
  // indicate what brightness we are currently seeing
  digitalWrite(PHOTO_RESISTOR_THRESHOLD_INDICATOR_PIN,
                    brightness > PHOTO_RESISTOR_THRESHOLD ? LOW : HIGH);

  this->secondMean->addValue(brightness);
  // are we ready to update second values?
  if (this->samples % 10 == 0) {
    this->minuteMean->addValue(this->secondMean->getMean());
  }
  // are we ready to update minute values
  if (this->samples % 600 == 0) {
    if (0 == this->tenMinuteMean) {
      this->tenMinuteMean = new MeanTracker(10, this->minuteMean->getMean());
    }
    this->tenMinuteMean->addValue(this->minuteMean->getMean());
  }

  this->samples = (this->samples + 1) % 600; // avoid overflow
};

int DayOrNight::isDay() {
  // if (0 == this->tenMinuteMean) {
  //   return 1;
  // }
  return this->minuteMean->getMean() > PHOTO_RESISTOR_THRESHOLD;
};

int DayOrNight::aboveThreshold() {
  return this->secondMean->getMean() > PHOTO_RESISTOR_THRESHOLD;
};
