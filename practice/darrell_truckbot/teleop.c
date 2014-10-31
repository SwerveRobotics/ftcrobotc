#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     left1,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     left2,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     right1,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     right2,        tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#pragma debuggerWindows("nxtLCDScreen");
//#pragma debuggerWindows("Servos");
//#pragma debuggerWindows("joystickSimple");
#pragma debuggerWindows("joystickGame");

#include "JoystickDriver.c"
#include "drive_tank.c"
#include "drive_arcade.c"

task main()
{
	waitForStart();

	StartTask(DriveTank);

	bool tankMode = true;

	while(true)
	{
		if(joy1Btn(10) == 1) // start button
		{
			StopTask(DriveTank);
			StopTask(DriveArcade);
			while(joy1Btn(10) == 1)
			{
			}
			if(tankMode == true)
			{
				StartTask(DriveArcade);
				tankMode = false;
			}
			else
			{
				StartTask(DriveTank);
				tankMode = true;
			}
		}
	}
}
