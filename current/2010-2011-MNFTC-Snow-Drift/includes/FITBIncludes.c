/*    ---FTC--Fish in the Boat Team 4140--ROBOTC Generic Function Includes--
This file contains many user-defined functions that would be independent of the setup in the program they are used on, and are very multipurpose.

//Log\\
*Created with the Joystick Button Feedback function, which adds helpful features like waiting for a joystick bump. 10-26 JJK

//Notes\\

*/
#include "LEGOUS-driver.h"
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

void light(string color="none")
{
  motor[green] = 0;
  motor[yellow] = 0;
  motor[red] = 0;

  if (color=="red") motor[red] = 100;
  else if (color=="none");
  else if (color=="yellow") motor[yellow] = 100;
  else if (color=="green") motor[green] = 100;
  else if (color=="all")
  {
    motor[green] = 100;
    motor[yellow] = 100;
    motor[red] = 100;
  }

}
void moveDist(int power, float length,  int oPower = power, bool coast=false)
{
  int lengthI = ceil((length/31.9185813)*1440);
  motor[leftMotor]  = power+leftAdjust;
  motor[rightMotor] = oPower+rightAdjust;
  while (abs(nMotorEncoder[leftMotor]) <= lengthI) {
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
{

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
