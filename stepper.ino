// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
 
 
void setup() 
{ 
  myservo.attach(3);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 
  myservo.writeMicroseconds(800);
  delay(5000);
  myservo.writeMicroseconds(1700); 
  delay(5000);
} 
