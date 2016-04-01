#include "TaskScheduler.h"
#include "motorFunctions.h"

/*----------------------------------------------------------------------------------------------------------
Variables
----------------------------------------------------------------------------------------------------------*/
int MotorOut1_left = 19;
int MotorOut2_left = 18;
int MotorOut1_right = 7;
int MotorOut2_right = 8;

double leftIn1 = 0;
double leftIn2 = 0;
double rightIn1 = 0;
double rightIn2 = 0;

int val; 
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;

int Move_state = 0;

/*----------------------------------------------------------------------------------------------------------
Scheduler Stuff
----------------------------------------------------------------------------------------------------------*/

// void FunctionName_Callback()
void Move_Callback();
void Read_Motor_Left_Callback();

//Task FunctionName(period(ms), TASK_FOREVER, &FunctionName_Callback);
Task Move(1600, TASK_FOREVER, &Move_Callback);
Task Read_Motor_Left(15, TASK_FOREVER, &Read_Motor_Left_Callback);

Scheduler runner;

//void FunctionName_Callback(){
//    code
//}

void Move_Callback(){
  if(Move_state == 0){
      Serial.println("FORWARDS"); //about 1600ms for a cell
      SetMotorForward(150);
      Move_state = 1;
  }
  else if(Move_state == 1){
      Serial.println("STOP");   //about 700ms for a cell right turn
      SetMotorStop();
      Move_state = 0; 
  }
    else if(Move_state == 2){
      Serial.println("BACKWARDS");
      SetMotorRight(150);
      Move_state = 3;
  }
    else if(Move_state == 3){    
      Serial.println("STOP");
      SetMotorStop();
      Move_state = 0;
  }

}
void Read_Motor_Left_Callback(){

  n = digitalRead(MotorOut1_left);
   if ((encoder0PinALast == LOW) && (n == HIGH)) {
     if (digitalRead(MotorOut2_left) == LOW) {
       encoder0Pos--;
     } 
     else {
       encoder0Pos++;
     }
     Serial.print (encoder0Pos);
     Serial.print ("\n");
   } 
   encoder0PinALast = n;
}

/*----------------------------------------------------------------------------------------------------------
Setup and Loop
----------------------------------------------------------------------------------------------------------*/
void setup() {
  pinMode(MotorPowerEN, OUTPUT);
  pinMode(MotorLogic1_right,OUTPUT);
  pinMode(MotorLogic2_right, OUTPUT);
  pinMode(MotorLogic1_left,OUTPUT);
  pinMode(MotorLogic2_left, OUTPUT);

  pinMode(MotorOut1_left, INPUT);
  pinMode(MotorOut2_left, INPUT);
  pinMode(MotorOut1_right, INPUT);
  pinMode(MotorOut2_right, INPUT);
  //digitalWrite(MotorPowerEN, LOW);

  Serial.begin(9600);

  //start scheduler code
  Serial.println("Scheduler TEST");
  runner.init();
  Serial.println("Initialized scheduler");

  //runner.addTask(FunctionName);
  //Serial.println("added t#");
  runner.addTask(Move);
  Serial.println("added t1");
  runner.addTask(Read_Motor_Left);
  Serial.println("added t2");

  delay(1500);

  //FunctionName.enable();
  //Serial.println("Enabled t#");
  Move.enable();
  Serial.println("Enabled t1");
  Read_Motor_Left.enable();
  Serial.println("Enabled t2");

//  for(int i = 0; i < 16; i++){
//    for(int j = 0; j < 16; j++){
//      Serial.print(grid[i][j]);
//    }
//    Serial.print("\n");
//  }
//  delay(5000);
}

void loop() {
  runner.execute();


}
