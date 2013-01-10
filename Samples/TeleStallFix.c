#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C2_1,     Left,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     Right,         tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     ForkLift,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//All comments to most of this code is in TeleOpJarrod.c
#include "JoystickDriver.c"
int deadZone = 15;
int pegPos[] = {2196, 5548, 8584};
//variables used for stall code
long timeStalling[3]; //amount of time the motors are stalling
int valueOfLastMove[3]; //the value of the encoders when the motor last moved
long timeStoppedMoving[3]; //the time the motors stopped

void InitializeStallCode()
{
	for(int i = 0; i <3; i++)
	{
		timeStalling[i] = 0;
		valueOfLastMove[i] = 0;
		timeStoppedMoving[i] = 0;
	}
}

int StallCode(int motorSentTo, int wantedPower)
{
	int motorIndex;//index value for the arrays
	switch(motorSentTo)//which motor power is being sent to
	{
		case Left:
		motorIndex = 0;
		break;
		case Right:
		motorIndex = 1;
		break;
		case ForkLift:
		default:
		motorIndex = 2;
		break;
	}
  int Cur = nMotorEncoder[motorSentTo];//current encoder value of motor

if((wantedPower < -15 || wantedPower > 15)&&(Cur == valueOfLastMove[motorIndex]))
{
	if(timeStalling[motorIndex] + 150 >= time1[T1])
	{
		if(timeStoppedMoving[motorIndex] == -1)
		{
			timeStoppedMoving[motorIndex] = time1[T1];
		}
		if(timeStoppedMoving[motorIndex] + 10 >= time1[T1])
		{
			return 0;
		}
		else
		{
			valueOfLastMove[motorIndex] = Cur;
			timeStoppedMoving[motorIndex] = 0;
			timeStalling[motorIndex] = time1[T1];
		}
	}
	return wantedPower;
}
timeStalling[motorIndex] = time1[T1];
return wantedPower;
}

void moveToPeg(int pegNum)
{
	int curPos = nMotorEncoder[ForkLift];
	int targetPos = pegPos[pegNum - 1];
	int moveToPos = targetPos - curPos;
	if(moveToPos < 0)
	{
		nMotorEncoderTarget[ForkLift] = -moveToPos;
	  motor[ForkLift] = 60;
	}
	else if(moveToPos > 0)
	{
		nMotorEncoderTarget[ForkLift] = moveToPos;
		motor[ForkLift] = -60;
	}
}

task main()
{
//waitForStart();
	ClearTimer(T1);
	nMotorEncoder[ForkLift] = 0;
	InitializeStallCode();
	while(true)
	{
		getJoystickSettings(joystick);
		if(joy1Btn(7) == 1)
		{
			if(abs(joystick.joy1_y1) > deadZone)
			{
  			motor[Left] = StallCode(Left, (joystick.joy1_y1) / 5);
			}
			else
			{
			  motor[Left] = StallCode(Left, 0);
			}

			if(abs(joystick.joy1_y2) > deadZone)
			{
				motor[Right] = StallCode(Right, (joystick.joy1_y2) / 5);
			}
			else
			{
			  motor[Right] = StallCode(Right, 0);
			}
		}
		else
		{
		  if(abs(joystick.joy1_y1) > deadZone)
		  {
			  motor[Left] = StallCode(Left, (joystick.joy1_y1));
		  }
		  else
		  {
			  motor[Left] = StallCode(Left, 0);
		  }

		  if(abs(joystick.joy1_y2) > deadZone)
		  {
		  	motor[Right] = StallCode(Right, (joystick.joy1_y2));
		  }
		  else
		  {
		  	motor[Right] = StallCode(Right, 0);
		  }
  	}

/*
		if(joystick.joy2_TopHat ==0)
  	{
  	  motor[ForkLift] = StallCode(ForkLift, -70);
  	}
  	else if(joystick.joy2_TopHat ==4)
  	{
  	  motor[ForkLift] = StallCode(ForkLift, 70);
  	}
  	else
  	{
  	  motor[ForkLift] = StallCode(ForkLift, 0);
  	}

  	if(joystick.joy2_Buttons == 2)
  	{
  		moveToPeg(1);
  	}
  	else if(joystick.joy2_Buttons == 1)
  	{
  		moveToPeg(2);
  	}
  	else if(joystick.joy2_Buttons == 4)
  	{
  		moveToPeg(3);
  	}
*/
	}
}
