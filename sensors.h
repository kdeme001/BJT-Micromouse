#ifndef SENSORS_H_
#define SENSORS_H_

#include "Arduino.h"
// point to user defined variables
int* front_input;              
int* left_input;             
int* right_input;

// calibration variables
int calR, calF, calL;

const int FRONT_SENSOR = A0;  
const int RIGHT_SENSOR = A1;  
const int LEFT_SENSOR = A2;

// initializes sensor calibration variables
// initializes calibration variables
void sensors_calibrate() {
  calF = analogRead(FRONT_SENSOR);
  calR = analogRead(RIGHT_SENSOR);
  calL = analogRead(LEFT_SENSOR);
}

// links user variables to internal variables via pointers
// also sets up setpoints
void sensors_initialize(int* Right, int* Front, int* Left, int &Rsetpoint, int &Fsetpoint, int &Lsetpoint) {
  front_input = Front;              
  left_input = Left;             
  right_input = Right;  
  sensors_calibrate();
  Fsetpoint = analogRead(FRONT_SENSOR);
  Rsetpoint = analogRead(RIGHT_SENSOR);
  Lsetpoint = analogRead(LEFT_SENSOR);
 
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

// returns actual sensor values, no calibration
void sensors_actual() {
  *front_input = analogRead(FRONT_SENSOR);
  *right_input = analogRead(RIGHT_SENSOR);
  *left_input = analogRead(LEFT_SENSOR);
}

// returns front sensor value
int sensors_getfront() {
  return *front_input;
}

// returns left sensor value
int sensors_getleft() {
  return *left_input;
}

// returns right sensor value
int sensors_getright() {
  return *right_input;
}

#endif
