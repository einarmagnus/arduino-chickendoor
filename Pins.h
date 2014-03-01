#ifndef Pins_h
#define Pins_h

const int PHOTO_RESISTOR_PIN = 0; // A0
const int GATE_ARRIVED_PIN = 1; // A1
const int MAGNET_CONTROLLER_PIN = 2; // D2
const int SERVO_CONTROLLER_PIN = 3; // D3
const int PHOTO_RESISTOR_THRESHOLD_INDICATOR_PIN = 13; //D13, LED

const int SERVO_CONTROLLER_OPEN_PULSE = 800;
const int SERVO_CONTROLLER_CLOSE_PULSE = 1700;

const int PHOTO_RESISTOR_THRESHOLD = 700;

// how long do we ignore arrival signal (because that signal is active already
// when we start)
const int GATE_ARRIVED_SIGNAL_MARGIN = 2000;
const int MAGNET_ACTIVATION_TIME = 2000;


#endif