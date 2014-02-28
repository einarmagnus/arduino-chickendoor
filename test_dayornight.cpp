#include <stdio.h>
#include "DayOrNight.h"
int readSensor() {
  static int i = 0;
  ++i;
  if (i < 10) {
    return 400;
  }
  if (i < 600) {
    return 500;
  }
  if (i < 12000) {
    return 900;
  }
  return 500;
}

int main(int argc, char **argv) {
  DayOrNight don(readSensor, 800);
  int last = -1;
  for (int i = 0 ; i < 100000; i++) {
    don.step();
    if (last != don.isDay()) {
      printf("Change! %d : %d\n", don.isDay(), i);
      last = don.isDay();
    }
  }
}
