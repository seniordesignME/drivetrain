#include <Arduino.h>
#include <Stepper.h>

const int stepPin = 3; //define pin for step
const int dirPin = 4; //define pin for direction

void setup() {
  // put your setup code here, to run once:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(dirPin, HIGH); // set direction, HIGH for clockwise, LOW for ccw

  for(int x=0; x<200; x++) { // loop for 200 steps
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  delay(1000); // delay for 1 second

}
