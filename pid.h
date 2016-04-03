#ifndef PID_H
#define PID_H
#include "Arduino.h"
#include "sensors.h"

/*
 * PID Control (Mostly P)
 * Code internally controls output variables to make the mouse go straight
 * Only covers "handeling"; no decision making
 * Output is bounded from 0 - 255
 */

// Conservative controller parameters
int Kp=1, Ki=0.05, Kd=0.25;

// pointers to point to user defined variables
int* F_setpoint; // setpoints, front not yet determined. further testing
int* L_setpoint;
int* R_setpoint;
int* front_output; // never used
int* right_output; // output to right motor
int* left_output; // output to left motor

// used for bools bool
bool updateR = true, updateL = true;

// thershold values to determine which wall case we are in
int noleft = 400; // used to determine no walls for left side
int noright = 200;

// error variables for caclulations
int* error;
double errorL, errorR; // used for calculations
int err_L, err_R; // used to convert back to int

// map user variables to internal variables via pointers
void pid_initialize(int* L_O, int* L_S,int* F_O, int* F_S, int* R_O, int* R_S, int* er ) {
  F_setpoint = F_S;
  L_setpoint = L_S;
  R_setpoint = R_S;
  front_output = F_O;
  right_output = R_O;
  left_output = L_O; 
  error = er;
}

// determines whether to increase left, decrease right motor or vice versa
// true = decrease left & increase right ie. too close to left
// used in case with two walls
bool pid_direction() {
  if((sensors_getleft() - sensors_getright()) > 0)
    return true;
  else
    return false;
}

// determines if mouse is stable ie. going straight ie. no error
// true if stable
bool pid_stable() {
  if((sensors_getleft() - sensors_getright()) == 0) 
    return true;
  else
    return false;
}

// works for two walls case
// => relies on errors from both sensors
void pid_compute() {
  Serial.print("\nWalls\n");
  if(!pid_stable()) {
    errorL = Kp*(*L_setpoint - sensors_getleft()); // get error & decrease right side
    errorR = Kp*(*R_setpoint - sensors_getright()); // in theory a negative value
    err_L = int(errorL);
    err_R = int(errorR);
   
    updateR = true;
    updateL = true;
    if(*left_output + err_L - err_R < 0) {
      *left_output = 0;
      updateL = false;
    }
    if(*left_output + err_L - err_R > 255) {
      *left_output = 255;
      updateL = false;
    }

    if(*right_output + err_R - err_L < 0) {
      *right_output = 0;
      updateR = false;
    }
    if(*right_output + err_R - err_L > 255) {
      *right_output = 255;
      updateR = false;
    }
    if(updateL)
      *left_output = *left_output + err_L - err_R;
    if(updateR)
      *right_output = *right_output + err_R - err_L;
       
    
  }
}

// case only left wall, no right wall
// => relies on error from left sensor only
void pid_compute_left() {
  Serial.print("\nNo right wall\n");
    errorL = Kp*(*L_setpoint - sensors_getleft()); // get error & decrease right side
    //errorR = Kp*(*R_setpoint - sensors_getright()); // in theory a negative value
    err_L = int(errorL);
    //err_R = int(errorR);
        *right_output = *right_output - err_L;
        *left_output = *left_output + err_L;

    updateR = true; // bools bool
    updateL = true;
    if(*left_output + err_L < 0) {
      *left_output = 0;
      updateL = false;
    }
    if(*left_output + err_L > 255) {
      *left_output = 255;
      updateL = false;
    }

    if(*right_output - err_L < 0) {
      *right_output = 0;
      updateR = false;
    }
    if(*right_output - err_L > 255) {
      *right_output = 255;
      updateR = false;
    }
    if(updateL)
      *left_output = *left_output + err_L;
    if(updateR)
      *right_output = *right_output - err_L;
}

// case only right wall
// => relies on error from right sensor only   
void pid_compute_right() {
    Serial.print("\nNo left wall\n");
    //errorL = Kp*(*L_setpoint - sensors_getleft()); // get error & decrease right side
    errorR = Kp*(*R_setpoint - sensors_getright()); // in theory a negative value
    //err_L = int(errorL);
    err_R = int(errorR);
    updateR = true;
    updateL = true;
    if(*left_output - err_R < 0) {
      *left_output = 0;
      updateL = false;
    }
    if(*left_output - err_R > 255) {
      *left_output = 255;
      updateL = false;
    }

    if(*right_output + err_R < 0) {
      *right_output = 0;
      updateR = false;
    }
    if(*right_output + err_R > 255) {
      *right_output = 255;
      updateR = false;
    }
    if(updateL)
      *left_output = *left_output - err_R;
    if(updateR)
      *right_output = *right_output + err_R;
}

// determines which case we are in to properly control mouse to go straight
// both walls, only left wall, only right wall
// only controls how mouse drives, does not decide whether to turn or not
void pid_think() {
  if(sensors_getright() <= noright) // case no right wall 
    pid_compute_left();
  else if(sensors_getleft() <= noleft)
    pid_compute_right();
  else
    pid_compute();
}

#endif
