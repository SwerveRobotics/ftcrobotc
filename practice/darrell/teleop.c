#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     left,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     right,         tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma debuggerWindows("nxtLCDScreen");
//#pragma debuggerWindows("Servos");
#pragma debuggerWindows("joystickSimple");

#include "JoystickDriver.c"
#include "drive_tank.c"
#include "colors.c"
#include "sensors.c"

task main()
{
	StartTask(Drive);

	InitColorValues();
	if(LightSensorOnColor(BLACK_COLOR_ENUM, 35))
		int x = 3;

	while(true)
	{
		// Loop is empty because we need to loop so the other task keeps running
	}
}
