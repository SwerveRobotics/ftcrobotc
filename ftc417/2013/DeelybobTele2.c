#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     seeker,         sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     Right,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Right2,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     Left,          tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     Left2,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     Hook,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     flag,          tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    gearshifter,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    flipper,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
//zone in which the joystick does not send values to the motors.
int deadZone = 15;



//This is the slow mode function that allows you to use the slow mode. Slow mode is the mode that allows you to slow down the robot.
void slowMode()
{
	//if the absolute value of joystick.joy1_y1 is greater than varible deadZone.
	if (abs(joystick.joy1_y1) > deadZone)
	{
		//The left motor's value is equal to the value joystick.joy1_y1 divided by 4.
		motor[Right] = joystick.joy1_y1 / 3;
		motor[Right2] = joystick.joy1_y1 / 3;
	}
	//if the if statement above is not entered then
	else
	{
		//The left motor's value equals 0.
		motor[Right] = 0;
		motor[Right2] = 0;
	}
	//This is the same code as above but for the right side
	if (abs(joystick.joy1_y2) > deadZone)
	{
		motor[Left] = joystick.joy1_y2 / 3;
		motor[Left2] = -joystick.joy1_y2 / 3;
	}
	else
	{
		motor[Left] = 0;
		motor[Left2] = 0;
	}
}

//This is the second task that splits the two joysticks into two tasks to help with efficency
task Joystick2()
{
	while (true)
	{
		//This gets the value of the joysticks from the robot
		getJoystickSettings(joystick);

		if (joy2Btn(4) == 1)
		{
			motor[flag] = 100;
		}
		else if (joy2Btn(1) == 1)
		{
			motor[flag] = -100;
		}
		else
		{
			motor[flag] = 0;
		}

		if(joystick.joy2_TopHat == 0)
		{
			motor[Hook] = 80;
		}
		else if(joystick.joy2_TopHat == 4)
		{
			motor[Hook] = -80;
		}
		else
		{
			motor[Hook] = 0;
		}

		if (joystick.joy2_TopHat == 2)
		{
			servo[flipper] = 128;
		}
		else if (joystick.joy2_TopHat == 6)
		{
			servo[flipper] = 0;
		}
	}
}


task main()
{
	servo[gearshifter] = 0;
	servo[flipper] = 128;
	waitForStart();
	StartTask(Joystick2);
	while (true)
	{

		getJoystickSettings(joystick);
		if (joy1Btn(8) == 1)
		{
			slowMode();
		}
		else
		{
			if (abs(joystick.joy1_y1) > deadZone)
			{
				motor[Right] = joystick.joy1_y1;
				motor[Right2] = joystick.joy1_y1;
			}
			else
			{
				motor[Right] = 0;
				motor[Right2] = 0;
			}

			if (abs(joystick.joy1_y2) > deadZone)
			{
				motor[Left] = joystick.joy1_y2;
				motor[Left2] = -joystick.joy1_y2;
			}
			else
			{
				motor[Left] = 0;
				motor[Left2] = 0;
			}

			if (joystick.joy1_TopHat == 0)
			{
				servo[gearshifter] = 180;
			}
			else if (joystick.joy1_TopHat == 4)
			{
				servo[gearshifter] = 0;
			}
		}
	}
}
