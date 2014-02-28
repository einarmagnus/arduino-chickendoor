#include "DayOrNight.h"

DayOrNight::DayOrNight(int (*sensorRead)(), int threshold) {
  this->sensorRead = sensorRead;
  this->threshold = threshold;

  // get a sample that is somewhat stable.
  int val = 0;
  for(int i = 0; i < 5; i++) {
    val += this->sensorRead();
  }
  val /= 5;

  this->secondMean = new MeanTracker(10, val);
  this->minuteMean = new MeanTracker(60, val);
  this->tenMinuteMean = 0;
  this->samples = 0;
};

void DayOrNight::step() {
  this->secondMean->addValue(this->sensorRead());
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
  if (0 == this->tenMinuteMean) {
    return 1;
  }
  return this->tenMinuteMean->getMean() > this->threshold;
};

int DayOrNight::aboveThreshold() {
  return this->secondMean->getMean() > this->threshold;
};
