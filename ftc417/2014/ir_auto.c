#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S2,     IROne,          sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     IRTwo,          sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     Right,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Right2,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     Left,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     Left2,         tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* Code Review by Darrell
 - magic numbers need replaced with defined numbers
 - functions should be used
 - should be using code library
 - I've seen BeaconPos2 and BeaconPos1 defined in other files as well.
 You need to have them defined in *only* one location and then #include and use it.
*/

#include "Joystickdriver.c"

void BeconPos1()
{
		while(nMotorEncoder[Left] <= 4320)
		{
			motor[Right] = 60;
			motor[Right2] = 60;
			motor[Left] = 60;
			motor[Left2] = 60;
		}
		motor[Right] = 0;
		motor[Right2] = 0;
		motor[Left] = 0;
		motor[Left2] = 0;
		nMotorEncoder[Left] = 0;

		while(nMotorEncoder[Left] <= 720)
		{
			motor[Right] = 60;
			motor[Right2] = 60;
			motor[Left] = -60;
			motor[Left2] = -60;
		}
		motor[Right] = 0;
		motor[Right2] = 0;
		motor[Left] = 0;
		motor[Left2] = 0;
		nMotorEncoder[Left] = 0;

		while(nMotorEncoder[Left] <= 2160)
		{
			motor[Right] = 60;
			motor[Right2] = 60;
			motor[Left] = 60;
			motor[Left2] = 60;
		}
		motor[Right] = 0;
		motor[Right2] = 0;
		motor[Left] = 0;
		motor[Left2] = 0;
		nMotorEncoder[Left] = 0;
}

void BeaconPos2()
{
	while(nMotorEncoder[Left] <= 4320)
	{
		motor[Left] = 60;
		motor[Left2] = 60;
		motor[Right] = 60;
		motor[Right2] = 60;
	}
	motor[Left] = 0;
	motor[Left2] = 0;
	motor[Right] = 0;
	motor[Right2] = 0;
	nMotorEncoder[Left] = 0;

	while(nMotorEncoder[Left] <= )
}

task main()
{
	waitForStart();
	nMotorEncoder[Right] = 0;
	nMotorEncoder[Left] = 0;

	while(true)
	{
			if(SensorValue[IROne] == 4 && SensorValue[IRTwo] == 6)
			{
				BeconPos1();
			}
			else if(SensorValue[IROne] == 5 && SensorValue[IRTwo] == 7)
			{
				BeaconPos2();
			}
	}


}
