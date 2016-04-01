
#ifndef MOTOR_FUNC
#define MOTOR_FUNC

int MotorPowerEN = 11;
int MotorLogic1_left = 23;
int MotorLogic2_left = 22;
int MotorLogic1_right = 3;
int MotorLogic2_right = 4;

//remember to try and account for the right motor being a piece of shit

void SetMotorForward(int x){
  analogWrite(MotorLogic1_left, x);
  analogWrite(MotorLogic2_left, 0);
  analogWrite(MotorLogic1_right, x+48);
  analogWrite(MotorLogic2_right, 0);  
}

void SetMotorBackward(int x){
   analogWrite(MotorLogic1_left, 0);
   analogWrite(MotorLogic2_left, x);
   analogWrite(MotorLogic1_right, 0);
   analogWrite(MotorLogic2_right, x); 
}

void SetMotorRight(int x){
   analogWrite(MotorLogic1_left, x);
   analogWrite(MotorLogic2_left, 0);
   analogWrite(MotorLogic1_right, 0);
   analogWrite(MotorLogic2_right, x); 
}

void SetMotorLeft(int x){
   analogWrite(MotorLogic1_left, 0);
   analogWrite(MotorLogic2_left, x);
   analogWrite(MotorLogic1_right, x);
   analogWrite(MotorLogic2_right, 0); 
}

void SetMotorStop(){
//   analogWrite(MotorLogic1_left, 255);
//   analogWrite(MotorLogic2_left, 255);
//   analogWrite(MotorLogic1_right, 255);
//   analogWrite(MotorLogic2_right, 255); 
   
   analogWrite(MotorLogic1_left, 0);
   analogWrite(MotorLogic2_left, 0);
   analogWrite(MotorLogic1_right, 0);
   analogWrite(MotorLogic2_right, 0); 
}

//int grid[16][16];
//
//void grid_mapping(){
//  //move forward 1 cell
//  //if wall 
//    //turn until no wall
//  //mark the cell the corresponding distance
//  //if middle
//    //party
//  
//}

//void grid_forward(int &xPos, int &yPos, int &distance, &int grid[][]){
//  grid[xPos][yPos] = distance;
//}

#endif
