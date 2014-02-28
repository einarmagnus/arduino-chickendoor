#ifndef MeanTracker_h
#define MeanTracker_h

/**
  * This class tracks a set number of values and keeps track of the mean.
  */
class MeanTracker {

public:
    MeanTracker(int size, int initialValue);

    void addValue(int value);
    int getMean();

private:
    int *values;
    int last; // position where we inserted the last value
    long total; // sum of all values
    int size; // total number of values

};

#endif