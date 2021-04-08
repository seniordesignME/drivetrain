#include <Arduino.h>
#include <Stepper.h>

//initialize the number of steps per revolution
const int stepsPerRevolution = 200;

//initialize motor driver with corresponding Arduino pins
Stepper myStepper1(stepsPerRevolution, 8, 9, 10, 11);
Stepper myStepper2(stepsPerRevolution, 2, 3, 4, 5);

void setup() {
  // set RPM
  myStepper1.setSpeed(180);
  myStepper2.setSpeed(180);

  //initialize the serial port
  Serial.begin(9600);
}

// run infinite loop of code for linear motion demonstration
void loop() {
  for(int s=0; s<stepsPerRevolution; s++)
  {
   myStepper1.step(1);
   myStepper2.step(-1);
  }
}
