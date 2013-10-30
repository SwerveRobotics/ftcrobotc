 #pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S3,     seeker,         sensorHiTechnicMagnetic)
#pragma config(Motor,  mtr_S1_C1_1,     Left,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Right,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     launcher,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     flag,          tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    arm,                  tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    rotater,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
//zone in which the joystick does not send values to the motors.
int deadZone = 15;
//int shootingSpeed = 100;

//This is the slow mode function that allows you to use the slow mode. Slow mode is the mode that allows you to slow down the robot.
void slowMode()
{
	//if the absolute value of joystick.joy1_y1 is greater than varible deadZone.
	if (abs(joystick.joy1_y1) > deadZone)
	{
		//The left motor's value is equal to the value joystick.joy1_y1 divided by 5.
		motor[Left] = joystick.joy1_y1 / 3;
	}
	//if the if statement above is not entered then
	else
	{
		//The left motor's value equals 0.
		motor[Left] = 0;
	}

	if (abs(joystick.joy1_y2) > deadZone)
	{
		motor[Right] = joystick.joy1_y2 / 3;
	}
	else
	{
		motor[Right] = 0;
	}
}

/*void flagSpinnerSlow()
{
if (joy2Btn(3) == 1)
{
motor[flag] = 100 / 4;
}
else if (joy2Btn(4) == 1)
{
motor[flag] = -100 / 4;
}
}*/

//This is th secound task that splits the two joysticks into two tasks to help with efficency
task Joystick2()
{
	while (true)
	{
		getJoystickSettings(joystick);

		while (joystick.joy2_TopHat == 4)
		{
			if (joy2Btn(3) == 1)
			{
				motor[flag] = 100 / 3;
			}
			else if (joy2Btn(2) == 1)
			{
				motor[flag] = -100 / 3;// jack was here
			}
			else
			{
				motor[flag] = 0;
			}
		}

		if (joy2Btn(3) == 1)
		{
			motor[flag] = 100;
		}
		else if (joy2Btn(2) == 1)
		{
			motor[flag] = -100;
		}
		else
		{
			motor[flag] = 0;
		}

		/*if (joy2Btn(6) == 1)
		{
		flagSpinnerSlow();
		}
		else
		{
		motor[flag] = 0;
		}*/

		if (joystick.joy2_TopHat == 4)
		{
			servo[arm] = 127;
		}
		else if(joystick.joy2_TopHat == 0)
		{
			servo[arm] = -127; //and here
		}

		if (joy2Btn(7) == 1)
		{
			motor[launcher] = 100;
		}
		else
		{
			motor[launcher] = 0;
		}

		if (joy2Btn(1) == 1)
		{
			servo[rotater] += 1;
		}
	}
}

task main()
{
	waitForStart();
	StartTask(Joystick2);
	while (true)
	{
		getJoystickSettings(joystick);
		if (joy1Btn(7) == 1)
		{
			slowMode();

			/*if (abs(joystick.joy1_y1) > deadZone)
			{
			motor[Left] = joystick.joy1_y1 / 5;
			}
			else
			{
			motor[Left] = 0;
			}

			if (abs(joystick.joy1_y2) > deadZone)
			{
			motor[Right] = joystick.joy1_y2 / 5;
			}
			else
			{
			motor[Right] = 0;
			}*/
		}
		else
		{
			if (abs(joystick.joy1_y1) > deadZone)
			{
				motor[Left] = joystick.joy1_y1;
			}
			else
			{
				motor[Left] = 0;
			}

			if (abs(joystick.joy1_y2) > deadZone)
			{
				motor[Right] = joystick.joy1_y2;
			}
			else
			{
				motor[Right] = 0;//annd here
			}
		}

		/*if (joy2Btn(7) == 1)
		{
		if (joystick.joy2_Buttons == 1)
		{
		motor[flag] = 100 / 2;
		}
		else if (joystick.joy2_Buttons == 2)
		{
		motor[flag] = -100 / 2;
		}
		else
		{
		motor[flag] = 0;
		}
		}
		else
		{
		if (joystick.joy2_Buttons == 1)
		{
		motor[flag] = 100;
		}
		else if (joystick.joy2_Buttons == 2)
		{
		motor[flag] = -100;
		}
		else
		{
		motor[flag] = 0;
		}
		}

		if (joystick.joy2_TopHat == 4)
		{
		servo[arm] = 127;
		}
		else if(joystick.joy2_TopHat == 0)
		{
		servo[arm] = -127;
		}

		/*float joyPos = 0;

		joyPosY = joystick.joy2_y2;
		joyPosX = joystick.joy2_x2;

		/*if (joystick.joy2_TopHat == 4 && shootingSpeed > 0)
		{
		shootingSpeed -= 10;
		}
		else if (joystick.joy2_TopHat == 0 && shootingSpeed < 100
		{
		shootingSpeed += 10;
		}
		else
		{

		}

		if (joy2Btn(1) == 1)
		{
		motor[shootingLeft] = shootingSpeed;
		motor[shootingRight] = shootingSpeed;
		}*/
	}
}
