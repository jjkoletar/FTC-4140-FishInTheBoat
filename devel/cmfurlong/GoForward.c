#pragma config(Hubs,  S3, HTMotor,  HTServo,  none,     none)
#pragma config(Motor,  mtr_S3_C1_1,     leftMotor,     tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S3_C1_2,     rightMotor,    tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


/*   ---FTC--Fish in the Boat Team 4140--Written for CaptureBot v1--

This is a basic drive control, written from scratch after previous code (Joystick2-modified.c) was too trashed to work on the robot, along with the re-design of the motors.

///Log\\\
*Wrote basic drive controlm, and dead zone function. - 10/21/10 JJK




///Notes\\\
*Having the rightMotor be postitive power, and the leftMotor be negative power makes the robot go forward. - 10/21/10 JJK








*/


/*
You're entering the variable declaration zone!
*/
int whatJoystick, deadZone;


/*
Goodbye from the variable declaration zone!
*/
void defineVariables()
{
  /*
  Config Zone!
  */
  deadZone = 10; //The amount the joystick must be greater than for the values to be used, and not be zero.

  /*
  End Config Zone!
  */
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  defineVariables(); //Fix for defining config bugs
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
int makeJoystickValuesWithDeadZone (int joyNum)
{
  if (joyNum==1)
  {
    whatJoystick = joystick.joy1_y2;
  }
  else if (joyNum==2)
  {
    whatJoystick = joystick.joy1_y1;
  }
  if (whatJoystick<deadZone)
  {
    if (whatJoystick>-deadZone)
    {
      whatJoystick = 0;
    }
  }
  return whatJoystick;
}



task main()
{
  initializeRobot();



  waitForStart();   // wait for start of tele-op phase

  while (true)
  {
    getJoystickSettings(joystick);
    motor[rightMotor] = makeJoystickValuesWithDeadZone(1);
    motor[leftMotor] = -makeJoystickValuesWithDeadZone(2);
  }
}
