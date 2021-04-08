//*NOTE* if functions not working try adding delays (0.5-1 sec?)
// need to test time to move 10 inches
// need to test best position for IR sensors

#include <Arduino.h>
#include <AccelStepper.h>

int A = 22; // connect ir sensor to arduino pin 22
int B = 23;
int C = 24;
int D = 25;

int ASensor; //always 1 or 0
int BSensor;
int CSensor;
int DSensor;

int LED_C = 26; // connect Led to arduino pin 26
int LED_D = 27;

// define stepper motors and pins
AccelStepper LeftBackWheel(1, 44, 45, 46, 47);   // (Type:driver, STEP, DIR) - Stepper1 <- not for bipolar stepper
AccelStepper LeftFrontWheel(1, 40, 41, 42, 43);  // Stepper2
AccelStepper RightBackWheel(1, 48, 49, 50, 51);  // Stepper3
AccelStepper RightFrontWheel(1, 52, 53, 54, 55); // Stepper4

// define speed
int wheelSpeed = 1500; // what units is this??

//last variable for B sensor.
int last; //if last sensor read 1, A = 65, C = 67
bool firstC = true;
bool go = false;

void setup() 
{
  pinMode (A, INPUT); // sensor pin INPUT
  pinMode (B, INPUT); // sensor pin INPUT
  pinMode (C, INPUT); // sensor pin INPUT
  pinMode (D, INPUT); // sensor pin INPUT
  
  pinMode (LED_C, OUTPUT); // Led pin OUTPUT
  pinMode (LED_D, OUTPUT);

  LeftFrontWheel.setMaxSpeed(3000);
  LeftBackWheel.setMaxSpeed(3000);
  RightFrontWheel.setMaxSpeed(3000);
  RightBackWheel.setMaxSpeed(3000);

  Serial.begin(9600);
}

void loop()
{
  ASensor = digitalRead (A); //always 1 or 0
  BSensor = digitalRead (B);
  CSensor = digitalRead (C);
  DSensor = digitalRead (D);

  if (!go && (CSensor == 1 && DSensor == 1)) {
      go = true;
      //turn on C and D LED
      digitalWrite(LED_C, HIGH); // LED ON
      digitalWrite(LED_D, HIGH); // LED ON
      delay(5000);
      
      //ESSKEDITT
      jumpBack('C');
      firstC = false;
      delay(500);
      jumpBack('D');
      delay(500);
      moveForward();
  }

  if (go) {
    if (ASensor == 1) {
      last = 65;
      jumpBack('A'); //backwards
    } else if (BSensor == 1) {
        jumpBack('B');
    } else if (CSensor == 1) {
        last = 67;
        jumpBack('C');
    } else if (DSensor == 1) {
        jumpBack('D');
    }
  }
  
}

void moveForward() {
  //logic to actually move forward
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(wheelSpeed);
}

void moveBackward() {
  //logic to actually move back
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(-wheelSpeed);
}

void moveRight() {
  //logic to actually move right
  //either move "10" or stop when B = 1
  unsigned long timer = 0;

  while (timer < 10000) { //move to the right for 10 seconds, get the timing right later
    if (BSensor == 0) {
      LeftFrontWheel.setSpeed(wheelSpeed);
      LeftBackWheel.setSpeed(-wheelSpeed);
      RightFrontWheel.setSpeed(-wheelSpeed);
      RightBackWheel.setSpeed(wheelSpeed);
    } else {
      //if it's off the table, jumpBack
      break;
    }
    
    timer = millis();
    delay(500); //wait a second so it dont freak out
  }  

  stopMoving();
  if (last == 65) {
    //A was last
    jumpBack('B');
  } else if (last == 67) {
    jumpBack('B');
  }
  
}

void moveLeft() {
  //logic to actually move left
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(-wheelSpeed);
}

void stopMoving() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(0);
}

void BmoveBackward() {
  //same as moveBackward BUT until CSensor == 1 then STOP
  while (CSensor == 0) {
    //logic to actually move back
    LeftFrontWheel.setSpeed(wheelSpeed);
    LeftBackWheel.setSpeed(wheelSpeed);
    RightFrontWheel.setSpeed(wheelSpeed);
    RightBackWheel.setSpeed(wheelSpeed);
  }

  stopMoving();
}

void BmoveForward() {
  //same as moveForward BUT until ASensor == 1 then STOP
  while (ASensor == 0) {
    //logic to actually move forward
    LeftFrontWheel.setSpeed(wheelSpeed);
    LeftBackWheel.setSpeed(wheelSpeed);
    RightFrontWheel.setSpeed(wheelSpeed);
    RightBackWheel.setSpeed(wheelSpeed);
  }

  stopMoving();
}

void jumpBack(int sensor) {
  //parameter is sensor?
  //switch for sensor

  switch(sensor) {
    case 'A':
      while (ASensor == 1) {
        moveBackward();
      }

      stopMoving();
      delay(1000);
      moveRight(); //distance or sensor B reading, whichever is first
      break;
    case 'B':
      //special
      while (BSensor == 1) {
        moveLeft();
      }

      stopMoving();
      delay(1000);
      
      switch(last) {
        case 65:
          BmoveBackward();
          break;
        case 67:
          BmoveForward();
          break;
      }
      break;
    case 'C':
      while (CSensor == 1) {
        moveForward();
      }

      stopMoving();
      delay(1000);
      
      if (!firstC) {
        moveRight(); //distance or sensor B reading, whichever is first
      }
      break;
    
    case 'D':
      while (DSensor == 1) {
        moveRight();
      }

      stopMoving();
      delay(1000);
      break;
  }
  
  return;
}
