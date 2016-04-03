#ifndef SENSORS_H_
#define SENSORS_H_

#include "Arduino.h"
// Variables
int* front_input;              
int* left_input;             
int* right_input;

int calR, calF, calL;

const int FRONT_SENSOR = A0;  
const int RIGHT_SENSOR = A1;  
const int LEFT_SENSOR = A2;

// initializes sensors
// initializes calibration variables
void sensors_calibrate() {
  calF = analogRead(FRONT_SENSOR);
  calR = analogRead(RIGHT_SENSOR);
  calL = analogRead(LEFT_SENSOR);
}
void sensors_initialize(int* Right, int* Front, int* Left) {
  front_input = Front;              
  left_input = Left;             
  right_input = Right;  
  sensors_calibrate();
}

// reads & calibrates sensor inputs
void sensors_read() {
  // read the analog in value:
  *front_input = analogRead(FRONT_SENSOR);
  *right_input = analogRead(RIGHT_SENSOR);
  *left_input = analogRead(LEFT_SENSOR);

  // calibrate
  *front_input -= calF;
  *left_input -= calL;
  *right_input -= calR;

  // cailbration adjustment
  if(analogRead(FRONT_SENSOR) - calF < 0)
    *front_input = ~*front_input + 1;
  if(analogRead(LEFT_SENSOR) - calL < 0)
    *left_input = ~*left_input + 1;
  if(analogRead(RIGHT_SENSOR) - calR < 0)
    *right_input = ~*right_input + 1; 
}

#endif
