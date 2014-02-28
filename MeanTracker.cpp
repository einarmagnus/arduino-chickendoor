#include "MeanTracker.h"
#include <stdlib.h>
MeanTracker::MeanTracker(int size, int initialValue) {
    this->values = (int*) malloc(sizeof(int) * size);
    this->size = size;
    this->last = 0;
    this->total = 1l * size * initialValue;
    for (int i = 0; i < size; i++) {
        this->values[i] = initialValue;
    }
}

void MeanTracker::addValue(int value) {
    this->total = this->total + value - this->values[this->last]; // modify total
    this->values[this->last] = value; // save current value as last
    this->last = (this->last + 1) % this->size; // increase position with wrap
};

int MeanTracker::getMean() {
    return this->total / this->size;
}
