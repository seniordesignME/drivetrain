#include <Arduino.h>

// initialize variable for pins
int led1 = 26;
int trig1 = 23;
int echo1 = 22;
//int unit = 100; // initialize variable for time delay in ms
//int dot = unit;
//int dash = unit*3; 
//int spacepartletter = unit;
//int spaceletter = unit*3;
//int spaceword = unit*7;

// initialize variables for calculating distance
int duration = 0;
int distance = 0;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  Serial.begin(9600);
}

void getDistance() {
  //send ultrasonic wave using trig pin
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);

  // read wave using echo pin
  duration = pulseIn(echo1, HIGH);

  // calculate distance in cm
  distance = duration * 0.034/2; 
  
}
void loop() {
  getDistance();
  while (distance < 30) {
    if (distance < 5) {
        digitalWrite(led1, HIGH); // LED off
    }
    getDistance();
    Serial.print("Distance: ");
    Serial.println(distance);
  }
  digitalWrite(led1, LOW); // LED off
//  Serial.print("Distance: ");
//  Serial.println(distance);

}

//void letterS() {
//  digitalWrite(led1, HIGH); // turn LED on
//  delay(dot);     
//  digitalWrite(led1, LOW);  // turn LED off
//  delay(spacepartletter);   
//  digitalWrite(led1, HIGH); // turn LED on
//  delay(dot); 
//  digitalWrite(led1, LOW);  // turn LED off
//  delay(spacepartletter); 
//  digitalWrite(led1, HIGH); // turn LED on
//  delay(dot);    
//  digitalWrite(led1, LOW);  // turn LED off
//}
//
//void letterO() {
//  digitalWrite(led1, HIGH); // turn LED on
//  delay(dash);       
//  digitalWrite(led1, LOW);  // turn LED off
//  delay(spacepartletter);     
//  digitalWrite(led1, HIGH); // turn LED on
//  delay(dash);  
//  digitalWrite(led1, LOW);  // turn LED off
//  delay(spacepartletter);    
//  digitalWrite(led1, HIGH); // turn LED on
//  delay(dash);    
//  digitalWrite(led1, LOW);  // turn LED off
//}
//
// 
