#ifndef Pins_h
#define Pins_h

const int PHOTO_RESISTOR_PIN = 0; // A0
const int ELECTRO_MAGNET_CONTROLLER_PIN = 2; // D2
const int SERVO_CONTROLLER_PIN = 3; // D3
const int PHOTO_RESISTOR_THRESHOLD_INDICATOR_PIN = 13; //D13, LED
const int SERVO_CONTROLLER_OPEN_PULSE = 800;
const int SERVO_CONTROLLER_CLOSE_PULSE = 1700;
const int PHOTO_RESISTOR_THRESHOLD = 800;


// returns millis from t1 to t2, handles the ~50 day wrap.
unsigned long time_difff(unsigned long t1, unsigned long t2);

#endif