#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     IRseeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     LeftMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     RightMotor,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     RightMotor2,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motorH,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    Flipper,              tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//#pragma config(Motor,  mtr_S1_C1_2,     LeftMotor2,    tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.C";
//int IRvalue;
int distancetoIR;

bool isbasketbasket4;
int deadZone = 15;

//start of stall code
//------------
//------------
long wayTooLong = 1000;  // millisecond threshold for absolute stall
long tooLong = 350;  // millisecond threshod for partial stall
long sigMove = 100; // How many encoder ticks is a 'significant' movement

//variables used for stall code need to be initialized
int lastDirection[] = {0, 0, 0}; // Direction of last power -1 (reverse), 0 (stopped) or 1 (forward)
long timeLastSigMove[] = {0, 0, 0}; // Time last significant move occurred
long encLastSigMove[] = {0, 0, 0}; // Encoder reading at last significant move

int StallCode(tMotor motorSentTo, int wantedPower)
{
	int motorIndex;  //index value for the arrays we are storing values in.
	int direction = 0;
	switch(motorSentTo) //which motor power is being sent to
	{
		case LeftMotor: // This is the name of one of the motors as referenced in the configuraiton.
			motorIndex = 0;
			break;
		case RightMotor:
			motorIndex = 1;
			break;
		/*case ForkLift:
			motorIndex = 2;
			break;*/
		default:
			break;
	}

	if (abs(wantedPower) < deadZone)  // Power below threshold, mark as stopped.
		direction = 0;
  else
  	direction = (wantedPower < 0) ? -1 : 1;

	if (direction == 0 || lastDirection[motorIndex] != direction)  // Stopped or changed direction.	Allow whatever power desired this time.
		{
    	lastDirection[motorIndex] = direction;
			timeLastSigMove[motorIndex]	 = time1[T1];
			encLastSigMove[motorIndex] = nMotorEncoder[motorSentTo];

			return wantedPower;
		}

 	lastDirection[motorIndex] = direction;

	if ( abs(encLastSigMove[motorIndex] - nMotorEncoder[motorSentTo]) > sigMove)  // Moved far enough to be considered significant, mark
		{
			timeLastSigMove[motorIndex]	= time1[T1];
			encLastSigMove[motorIndex] = nMotorEncoder[motorSentTo];

			return wantedPower;
		}

	if ( (time1[T1] - timeLastSigMove[motorIndex]) > wayTooLong )  // Time since last significant move too long, stalled
		{
			PlayTone(650,4);
			return 0;
		}

	if ( (time1[T1] - timeLastSigMove[motorIndex]) > tooLong )  // Time since last significant move too long, stalled
		{
			PlayTone(365,4);
			return wantedPower / 2;
		}

	return wantedPower;	// Haven�t moved far enough yet to be significant but haven�t timed out yet
}
//end of stall code-------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

task main()
{
	waitForStart();

	nMotorEncoder[LeftMotor] = 0;
	nMotorEncoder[RightMotor] = 0;
	//decides if IR is on basket 4
	if (SensorValue[IRseeker] == 3)
	{
		isbasketbasket4 = true;
	}

	//goes to basket 4
	while (nMotorEncoder[LeftMotor] > -250)
	{
		motor[LeftMotor] =  -35;
		motor[RightMotor] = -35;
	}
		motor[LeftMotor] =  0;
		motor[RightMotor] = 0;

		//if basket 4 is IR then it flips
	if (isbasketbasket4 == true)
	{
		servo[Flipper] = 224;

		wait1Msec(1000);

		//adjust distance to be positive and slightly smaller
		distancetoIR = nMotorEncoder[LeftMotor];
		distancetoIR = distancetoIR * -1;
		distancetoIR = distancetoIR - 1000;

		//reset motors and encoders
		nMotorEncoder[LeftMotor] = 0;
		nMotorEncoder[RightMotor] = 0;
		motor[LeftMotor] = 0;
		motor[RightMotor] = 0;

			//goes back to wall
		while (nMotorEncoder[LeftMotor] < distancetoIR)
		{
		motor[LeftMotor] =  35;
		motor[RightMotor] = 35;
		}

		nMotorEncoder[LeftMotor] = 0;

	//resets flipper
		motor[LeftMotor] =  0;
		servo[Flipper] = 75;

		//turns to block zone
		while (nMotorEncoder[LeftMotor] > -900)
		{
			motor[LeftMotor] =  -35;
		}
		nMotorEncoder[LeftMotor] = 0;


		//drive towards block zone
		while (nMotorEncoder[LeftMotor] < 3000)
		{
			motor[LeftMotor] =  35;
			motor[RightMotor] = 35;
		}
		motor[LeftMotor] =  0;
		motor[RightMotor] = 0;

		nMotorEncoder[LeftMotor] = 0;

		//turn towards ramp
		while (nMotorEncoder[LeftMotor] > -450)
		{
			motor[LeftMotor] =  -35;
			motor[RightMotor] = 35;
		}
		motor[LeftMotor] =  0;
		motor[RightMotor] = 0;

		nMotorEncoder[LeftMotor] = 0;
		nMotorEncoder[RightMotor] = 0;


		//drive onto ramp
		while (nMotorEncoder[LeftMotor] < 3700)
		{
			motor[LeftMotor] = StallCode(LeftMotor, (100));
			motor[RightMotor] = StallCode(RightMotor, (100));
		}
		motor[LeftMotor] =  0;
		motor[RightMotor] = 0;
		//stops program
		return;
		}

		//if not basket 4 then...

	//goes to basket 3
	while (nMotorEncoder[LeftMotor] > -800)
	{
		motor[LeftMotor] =  -35;
		motor[RightMotor] = -35;
	}

		motor[LeftMotor] = 0;

		motor[RightMotor] = 0;
		//decides if basket 3 is IR
		if (SensorValue[IRseeker] == 3)
		{
			//flips block
			servo[Flipper] = 224;
			wait1Msec(1000);
			distancetoIR = nMotorEncoder[LeftMotor];
			distancetoIR = distancetoIR * -1;
			distancetoIR = distancetoIR - 1000;
			nMotorEncoder[LeftMotor] = 0;

			//goes back to wall
		while (nMotorEncoder[LeftMotor] < distancetoIR)
		{
		motor[LeftMotor] =  35;
		motor[RightMotor] = 35;
		}

		//resets flipper
		motor[LeftMotor] = 0;
			nMotorEncoder[LeftMotor] = 0;
		servo[Flipper] = 75;

		//turns towards block zone
		while (nMotorEncoder[LeftMotor] > -200)
		{
			motor[LeftMotor] =  -35;
		}
		motor[LeftMotor] = 0;
		nMotorEncoder[LeftMotor] = 0;

		//drive towards block zone
		while (nMotorEncoder[LeftMotor] < 2500)
		{
			motor[LeftMotor] =  35;
			motor[RightMotor] = 35;
		}
		motor[LeftMotor] =  0;
		motor[RightMotor] = 0;

		nMotorEncoder[LeftMotor] = 0;

		//turn towards ramp
		while (nMotorEncoder[LeftMotor] > -450)
		{
			motor[LeftMotor] =  -35;
			motor[RightMotor] = 35;
		}
		motor[LeftMotor] =  0;
		motor[RightMotor] = 0;

		nMotorEncoder[LeftMotor] = 0;
		nMotorEncoder[RightMotor] = 0;

		//drive onto ramp
		while (nMotorEncoder[LeftMotor] < 3700)
		{
			motor[LeftMotor] = StallCode(LeftMotor, (100));
			motor[RightMotor] = StallCode(RightMotor, (100));
		}
		motor[LeftMotor] =  0;
		motor[RightMotor] = 0;

		return;
		}
		//if basket 3 is not IR then...

			motor[LeftMotor] = 0;
		motor[RightMotor] = 0;

		//goes to basket 2
	while (nMotorEncoder[LeftMotor] > -2100)
	{
		motor[LeftMotor] =  -35;
		motor[RightMotor] = -35;
	}
		motor[LeftMotor] = 0;
		motor[RightMotor] = 0;

		//decides if basket 2 is IR basket
		if (SensorValue[IRseeker] == 3)
	{
		while (nMotorEncoder[LeftMotor] > -2000)
		{
			motor[LeftMotor] = 35;
			motor[RightMotor] = 35;
		}
		//if so, flips block
		servo[Flipper] = 224;

		wait1Msec(1000);

		distancetoIR = nMotorEncoder[LeftMotor];
		distancetoIR = distancetoIR * -1;
		distancetoIR = distancetoIR - 1000;
		nMotorEncoder[LeftMotor] = 0;

			//goes back to wall
		while (nMotorEncoder[LeftMotor] < distancetoIR)
		{
		motor[LeftMotor] =  35;
		motor[RightMotor] = 35;
		}

		motor[LeftMotor] =  0;

		nMotorEncoder[LeftMotor] = 0;
		//resets flipper
		servo[Flipper] = 75;

		//turns towards block zone
		while (nMotorEncoder[LeftMotor] > -1100)
		{
			motor[LeftMotor] =  -35;
		}
		nMotorEncoder[LeftMotor] = 0;

		//drives towards block zone
		while (nMotorEncoder[LeftMotor] < 2500)
		{
			motor[LeftMotor] =  35;
			motor[RightMotor] = 35;
		}
		motor[LeftMotor] =  0;
		motor[RightMotor] = 0;

		nMotorEncoder[LeftMotor] = 0;

		//turns towards ramp
		while (nMotorEncoder[LeftMotor] > -450)
		{
			motor[LeftMotor] =  -35;
			motor[RightMotor] = 35;
		}
		motor[LeftMotor] =  0;
		motor[RightMotor] = 0;

		nMotorEncoder[LeftMotor] = 0;
		nMotorEncoder[RightMotor] = 0;

		//drive onto ramp
		while (nMotorEncoder[LeftMotor] < 3700)
		{
			motor[LeftMotor] = StallCode(LeftMotor, (100));
			motor[RightMotor] = StallCode(RightMotor, (100));
		}
		motor[LeftMotor] =  0;
		motor[RightMotor] = 0;
		return;
	}

	//if basket 2 is not IR then...

	//same comments as other 3 baskets

	//goes to basket 1
	while (nMotorEncoder[LeftMotor] > -2800)
	{
		motor[LeftMotor] =  -35;
		motor[RightMotor] = -35;
	}
		motor[LeftMotor] = 0;
		motor[RightMotor] = 0;

		servo[Flipper] = 224;
		wait1Msec(1000);
		distancetoIR = nMotorEncoder[LeftMotor];
		distancetoIR = distancetoIR * -1;
		distancetoIR = distancetoIR - 1000;

		nMotorEncoder[LeftMotor] = 0;

			//goes back to wall
		while (nMotorEncoder[LeftMotor] < distancetoIR)
		{
		motor[LeftMotor] =  35;
		motor[RightMotor] = 35;
		}

		nMotorEncoder[LeftMotor] = 0;


		motor[LeftMotor] =  0;
		motor[RightMotor] = 0;
		servo[Flipper] = 75;

		//turns toward block zone
		while (nMotorEncoder[LeftMotor] > -600)
		{
			motor[LeftMotor] =  -35;
		}
		nMotorEncoder[LeftMotor] = 0;

		//drives towards block zone
		while (nMotorEncoder[LeftMotor] < 2800)
		{
			motor[LeftMotor] =  35;
			motor[RightMotor] = 35;
		}
		motor[LeftMotor] =  0;
		motor[RightMotor] = 0;

		nMotorEncoder[LeftMotor] = 0;

		//turns towards ramp
		while (nMotorEncoder[LeftMotor] > -450)
		{
			motor[LeftMotor] =  -35;
			motor[RightMotor] = 35;
		}
		motor[LeftMotor] =  0;
		motor[RightMotor] = 0;

		nMotorEncoder[LeftMotor] = 0;
		nMotorEncoder[RightMotor] = 0;

			//resets flipper
		motor[LeftMotor] = 0;
			nMotorEncoder[LeftMotor] = 0;
		servo[Flipper] = 75;

		//drives towards ramp
		while (nMotorEncoder[LeftMotor] < 3700)
		{
			motor[LeftMotor] = StallCode(LeftMotor, (100));
			motor[RightMotor] = StallCode(RightMotor, (100));
		}
		motor[LeftMotor] =  0;
		motor[RightMotor] = 0;
		return;
}
