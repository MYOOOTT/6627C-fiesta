#pragma config(Motor,  port1,           frontLeftMotor, tmotorNone, openLoop)
#pragma config(Motor,  port2,           backLeftMotor, tmotorNone, openLoop)
#pragma config(Motor,  port3,           frontRightMotor, tmotorNone, openLoop)
#pragma config(Motor,  port4,           backRightMotor, tmotorNone, openLoop)
#pragma config(Motor,  port5,           arm,           tmotorNone, openLoop)
#pragma config(Motor,  port6,           leftLift,      tmotorNone, openLoop)
#pragma config(Motor,  port7,           rightLift,     tmotorNone, openLoop)
#pragma config(Motor,  port8,           claw,          tmotorNone, openLoop)
#pragma config(Motor,  port9,           middleRightMotor, tmotorNone, openLoop)
#pragma config(Motor,  port10,          middleLeftMotor, tmotorNone, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"



void pre_auton() {
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

task autonomous() {
}


bool mobileGoalDirection; //true = up, false = down

task mobileGoalIntake() {
	if(mobileGoalDirection) {
			motor[arm] = 127;
			wait(.5);
			motor[arm] = 0;
	} else {
			motor[arm] = -127;
			wait(.5);
			motor[arm] = 0;
	}
}

task usercontrol () {

	while(1 == 1)
	{
		//arcade control (left joystick)
		int left = vexRT[Ch4] + vexRT[Ch3];
		int right = vexRT[Ch4] - vexRT[Ch3];

		//creates a deadzone so that it doesn't move slightly to left/right/forward/backward
		if (abs(left) < 5)
			left = 0;
		if (abs(right) < 5)
			right = 0;

		motor[frontLeftMotor]  = left;
		motor[backLeftMotor] = left;
		motor[middleLeftMotor] = left;

		motor[frontRightMotor]  = right;
		motor[middleRightMotor] = right;
		motor[backRightMotor] = right;

		//PRIMARY INTAKE - left buttons (AUTOMATIC)
		if (vexRT[Btn7U] == 1) {
			mobileGoalDirection = true;
			startTask(mobileGoalIntake);
		} else if (vexRT[Btn7D] == 1) {
			mobileGoalDirection = false;
			startTask(mobileGoalIntake);
		} else {
			motor[arm] = 0;
		}

		/*
		//PRIMARY INTAKE - left buttons (MANUAL)
		if (vexRT[Btn7U] == 1) {
			motor[arm] = 127;
		} else if (vexRT[Btn7D] == 1) {
			motor[arm] = -127;
		} else {
			motor[arm] = 0;
		}
		*/


		if (vexRT[Btn8U] == 1) {
			motor[rightLift] = 127;
			motor[leftLift] = 127;

			} else if (vexRT[Btn8D] == 1) {
			motor[rightLift] = -127;
			motor[leftLift] = -127;

			} else {
			motor[rightLift] = 0;
			motor[leftLift] = 0;
		}

		if (vexRT[Btn6U] == 1) {
			motor[claw] = 127;

			} else if (vexRT[Btn6D] == 1) {
			motor[claw] = -127;

			} else {
			motor[claw] = 0;
		}

	}
}