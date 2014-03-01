#ifndef DayOrNight_h
#define DayOrNight_h
#include "MeanTracker.h"
/**
  * This class tracks whtehr it is day or night. It transitions when the ten
  * minute mean sensor value is above or below the threshold.
  * It will assume it is day until it has run for a minute, then it will assume
  * that it can extrapolate the sampled values backwards in time.
  */
class DayOrNight {
public:

    DayOrNight();

    /** Read value and do calculations
      */
    void step();

    /** Return 1 if day, 0 otherwise
      */
    int isDay();

    /** Return 1 if the current second considers it to be day, otherwise 0
      */
    int aboveThreshold();

private:
    int samples;
    MeanTracker *secondMean, // keep track of sub second values, 10 of them
                *minuteMean, // keep track of second values
                *tenMinuteMean; // keep track of minute values.

};

#endif