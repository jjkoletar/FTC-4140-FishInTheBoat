/*    ---FTC--Fish in the Boat Team 4140--ROBOTC Generic Function Includes--
This file contains many user-defined functions that would be independent of the setup in the program they are used on, and are very multipurpose.

THIS CODE IS LICENSED UNDER THE GNU GPL v3, INCLUDED IN THE SVN, AND AT THE LINK: http://www.gnu.org/licenses/gpl-3.0.txt
NO WARRANTY PROVIDED.
© FTC 4140 Fish in the Boat and Jeremy Koletar

This file will not compile on its own.

//Log\\
*Created with the Joystick Button Feedback function, which adds helpful features like waiting for a joystick bump. 10-26 JJK


//Notes\\
*If using indent, opetions to use are: -bl -npsl -nss -ncs -npcs -bap -ss
*/
#include "LEGOUS-driver.h"
#include "LEGOTS-driver.h"
bool joySwap = false;
const int leftAdjust  = 5;
const int rightAdjust = 0;
int toInt(string num)
{
  if (num=="1") return 1;
  else if (num=="2") return 2;
  else if (num=="3") return 3;
  else if (num=="4") return 4;
  else if (num=="5") return 5;
  else if (num=="6") return 6;
  else if (num=="7") return 7;
  else if (num=="8") return 8;
  else if (num=="9") return 9;
  else if (num=="10") return 10;
  else if (num=="11") return 11;
  else if (num=="12") return 12;
  else if (num=="13") return 13;
  else if (num=="14") return 14;
  else if (num=="15") return 15;
  else if (num=="16") return 16;
  else if (num=="17") return 17;
  else if (num=="18") return 18;
  else if (num=="19") return 19;
  else if (num=="20") return 20;
  else return 0;
}

void encoderDebugStream()
{
  if (nMotorEncoder[leftMotor] != 0) writeDebugStreamLine("[WARN] left motor encoder is not 0!");
  if (nMotorEncoder[rightMotor] != 0) writeDebugStreamLine("[WARN] rt motor encoder is not 0!");
}

void swapJoys()
{
  motor[leftMotor] = 0;
  motor[rightMotor] = 0;
  joySwap = !joySwap;
  PlayTone(784, 50);
}

bool swappedJoys()
{
  return joySwap;
}

int joystickVal(int joyNum, string value)
{
  //Check for joyswap activation
  if (joySwap && joyNum==1) joyNum = 2;
  else if (joySwap && joyNum==2) joyNum = 1;
  if (joyNum==1)
  {
    //All of joy1's button handlers and joystick handlers
    if (value=="x1") return joystick.joy1_x1;
    else if (value=="x2") return joystick.joy1_x2;
    else if (value=="y1") return joystick.joy1_y1;
    else if (value=="y2") return joystick.joy1_y2;
    else if (value=="hat") return joystick.joy1_TopHat;
    else return joy1Btn(toInt(value));
  }
  else if (joyNum==2)
  {
    //all of joy2's button and joystick handlers
    if (value=="x1") return joystick.joy2_x1;
    else if (value=="x2") return joystick.joy2_x2;
    else if (value=="y1") return joystick.joy2_y1;
    else if (value=="y2") return joystick.joy2_y2;
    else if (value=="hat") return joystick.joy2_TopHat;
    else return joy2Btn(toInt(value));
  }
  else return 0; //Fallback for no compiler crying
}




void straightForTime(int power, int mseconds, bool coast="false")
{
  motor[leftMotor] = power;
  motor[rightMotor] = power;
  wait1Msec(mseconds);
  motor[leftMotor] = 0;
  motor[rightMotor] = 0;
}

void waitForRelease(int joyNum, string button, int val=1)
{
  //Function to waste time until a button is released
  while (joystickVal(joyNum, button)==val)
  {
    wait1Msec(1);
  }
}

void turnDegrees(int power, string wheel, float degrees)
{
  nMotorEncoder[leftMotor]  = 0;
  nMotorEncoder[rightMotor] = 0;
  encoderDebugStream();
  motor[rightMotor] = 0;
  motor[leftMotor] = 0;
  int turnLength = ceil((degrees/60)*1440);
  if (wheel=="left")
  {
    motor[leftMotor] = power;
    motor[rightMotor] = 0;
    while (abs(nMotorEncoder[leftMotor]) <= abs(turnLength))
    {
      //motor already set, just wait for loop to finish
      //debug info !
      writeDebugStreamLine("[INFO] Turn Enc (lt): %d", nMotorEncoder[leftMotor]);
    }
    motor[leftMotor] = 0;
  }
  else if (wheel=="right")
  {
    motor[rightMotor] = power;
    motor[leftMotor] = 0;
    while (abs(nMotorEncoder[rightMotor]) <= abs(turnLength))
    {
      //motor already set... wait for loop to finish...
      //debug info too!
      writeDebugStreamLine("[INFO] Turn Enc (rt): %d", nMotorEncoder[rightMotor]);
    }
    motor[rightMotor] = 0;

  }
    nMotorEncoder[leftMotor] = 0;
  nMotorEncoder[rightMotor]= 0;
}

void periTurn(int power, string wheel, float degrees)
{
  encoderDebugStream();
  motor[rightMotor] = 0;
  motor[leftMotor] = 0;
  nMotorEncoder[rightMotor] = 0;
  nMotorEncoder[leftMotor] = 0;
  int turnLength = ceil((degrees/60)*1440);
  turnLength = turnLength/2;
  if (wheel=="left")
  {
    motor[leftMotor] = power;
    motor[rightMotor] = -power;
    while (abs(nMotorEncoder[rightMotor]) <= abs(turnLength))
    {
      //wait for loop
    }
    motor[leftMotor] = 0;
    motor[rightMotor] = 0;
  }
  else if (wheel=="right")
  {
    motor[leftMotor] = -power;
    motor[rightMotor] = power;
    while (abs(nMotorEncoder[leftMotor]) <= abs(turnLength))
    {
      //loop
    }
    motor[leftMotor] = 0;
    motor[rightMotor] = 0;
  }
  nMotorEncoder[rightMotor] = 0;
  nMotorEncoder[leftMotor] = 0;
}


void moveDist(int power, float length, int leftFix=0,  int oPower = power, bool coast=false)
{
  encoderDebugStream();
  int lastValue = 0;
  nMotorEncoder[leftMotor] = 0;
  nMotorEncoder[rightMotor]= 0;
  int lengthI = ceil(((length-5)/31.9185813)*1440);
  if (power < 0) lengthI = -lengthI;
  motor[leftMotor]  = power/*+leftAdjust*/;
  motor[rightMotor] = oPower+leftFix/*+rightAdjust*/;
  while (abs(nMotorEncoder[rightMotor]) <= abs(lengthI)) {
    if (lastValue != nMotorEncoder[rightMotor]) writeDebugStreamLine("[INFO] right encoder (inmove): %d", nMotorEncoder[rightMotor]);\
    lastValue = nMotorEncoder[rightMotor];
  }
  if (coast) {
    motor[leftMotor]  = 1;
    motor[rightMotor] = 1;
    wait1Msec(200);
  }
  else {
    motor[leftMotor]  = 0;
    motor[rightMotor] = 0;
  }
  nMotorEncoder[leftMotor] = 0;
}

void turnTime(int power, string wheel, int time)
{
  if (wheel=="left")
  {
    motor[leftMotor] = power;
    wait1Msec(time);
    motor[leftMotor] = 0;
  }
  else if (wheel=="right")
  {
    motor[rightMotor] = power;
    wait1Msec(time);
    motor[rightMotor] = 0;
  }
}
void turnDeg(int power, string wheel, int degrees)
{/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Function is deprecated. Use turnDegrees() instead.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/
  writeDebugStreamLine("[BAD] Call to deprecated function turnDeg()!");
  nMotorEncoder[leftMotor] =  1;
  nMotorEncoder[rightMotor] = 0;
  //while (nMotorEncoder[leftMotor] <= degrees*1440);
  if (wheel=="left")
  {
    motor[leftMotor] = power;
    while (nMotorEncoder[leftMotor] > degrees) nxtDisplayBigTextLine(3, "LK: %d", nMotorEncoder[leftMotor]);
    motor[leftMotor] = 0;
  }
  else if (wheel=="right")
  {
    motor[rightMotor] = power;
    while (abs(nMotorEncoder[rightMotor]) <= degrees*1440);
    motor[rightMotor] = 0;
  }
}
bool closeEnough(int val1, int val2)
{
  if (val1==val2 || val1-1== val2 || val1-2==val2 /*||val1-3==val2 */|| val1+1==val2 || val1+2==val2 /*|| val1+3==val2*/) return true;
  else return false;
}
void paralellWall()
{
  int rearSensor = SensorValue[S4] -2;
  bool aligned = false;
  while (!aligned)
  {
    rearSensor = SensorValue[S4] -2;
  nxtDisplayTextLine(3, "s4: %d s3:%d", rearSensor, SensorValue[S3]);
  if (closeEnough(rearSensor, SensorValue[S3]))
  {
    //Already close enough, we're done.
    aligned = true;
  }
  else if (SensorValue[S3] > rearSensor)
  {
    //Front of robot is futher from the wall then back, small turn.
    turnTime(25, "left", 150);
    wait1Msec(100);
  }
  else if (SensorValue[S3] < rearSensor)
  {
    //Back of robot is further, small turn.
    turnTime(25, "right", 150);
    wait1Msec(100);
  }
  else
  {
    //Odd situation, no matches of the case list. Exit.;
    aligned = true;
  }
  //next part, moving walk.
  }

}
void jogAlign()
  {
  int rearSensor = SensorValue[S4] -2;
  bool para = false;
  ClearTimer(T1);
  const int power = 25;
  motor[leftMotor] = power;
  motor[rightMotor] = power;
  while (!para)
  {
    rearSensor = SensorValue[S4] -2;

    if (time1[T1]>=2500)
    {
      //clock expire
      para = true;
    }
    else if (SensorValue[S3]==rearSensor)
    {
      motor[leftMotor]  = power;
      motor[rightMotor] = power;
    }
    else
    {
      motor[rightMotor] = 0;
      motor[leftMotor] = 0;
      paralellWall();
    }
  }
  motor[leftMotor] = 0;
  motor[rightMotor] = 0;
}

bool innerTS(string side="both")
{
  if (side == "both")
  {
    if (TSreadState(msensor_S2_3)) return true;
    else if (TSreadState(msensor_S2_4)) return true;
    else return false;
  }
  else if (side == "left") return TSreadState(msensor_S2_4);
  else if (side == "right")return TSreadState(msensor_S2_3);
  else return false;
}

void robotAdventureTimeDanceTime()
{
  writeDebugStreamLine("[INFO] Dance Time!");
  servo[leftArm] = 0;
  servo[rightArm] = 0;
  const int amount = 5;
  bool dir = false;
  wait1Msec(750);
  while (true)
  {
    if (!dir)
    {
      //increase left, subtract right
      servo[leftArm] = servo[leftArm] + amount;
      servo[rightArm] = servo[rightArm] + amount;
      wait1Msec(30);
    }
    else if (dir)
    {
      //decrease left, increase right
      servo[leftArm] = servo[leftArm] - amount;
      servo[rightArm] = servo[rightArm] - amount;
      wait1Msec(30);
    }
    if (servo[leftArm] == 0 && servo[rightArm] == 0) dir = false;
    else if (servo[leftArm] == 255 && servo[rightArm] == 255) dir = true;
  }
}
void conveyorOut()
{
   motor[conveyorMotor] = 0;
   motor[conveyorArmMotor] = 50;
   int lastVal = 0;
   while (nMotorEncoder[conveyorArmMotor] < 2500) {
     lastVal = nMotorEncoder[conveyorArmMotor];
     wait1Msec(200);
     if (lastVal == nMotorEncoder[conveyorArmMotor])
     {
       motor[conveyorArmMotor] = motor[conveyorArmMotor] + 5;
       wait1Msec(50);
     }

   }
   motor[conveyorArmMotor] = 1;
   while (nMotorEncoder[conveyorArmMotor] < 2600) {
   }
   motor[conveyorArmMotor] = 0;
 }
void conveyorIn()
{
   motor[conveyorMotor] = 0;
   motor[conveyorArmMotor] = -50;
   while (nMotorEncoder[conveyorArmMotor] > 1000) {
   }
   motor[conveyorArmMotor] = -10;
   while (nMotorEncoder[conveyorArmMotor] > 200) {
   }
   motor[conveyorArmMotor] = 0;
}
