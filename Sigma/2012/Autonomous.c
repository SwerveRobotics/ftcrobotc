#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     irsensor,       sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeft,     tmotorNormal, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorArm,      tmotorNormal, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorRight,    tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorNone, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servoRight,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servoWristRight,      tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servoLeft,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servoWristLeft,       tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "C:\ftc\drivers\2.3\drivers\HTIRS2-driver.h"
#include "JoystickDriver.c"

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
		case motorLeft:
		motorIndex = 0;
		break;
		case motorRight:
		motorIndex = 1;
		break;
		case motorArm:
		default:
		motorIndex = 2;
		break;
	}
  int cur = nMotorEncoder[motorSentTo];//current encoder value of motor

if((wantedPower < -30 || wantedPower > 30)&&(cur == valueOfLastMove[motorIndex]))
{
	if(timeStalling[motorIndex] + 150 >= time1[T1])
	{
		if(timeStoppedMoving[motorIndex] == 0)
		{
			timeStoppedMoving[motorIndex] = time1[T1];
		}
		if(timeStoppedMoving[motorIndex] + 10 >= time1[T1])
		{
			return 0;
		}
		else
		{
		    valueOfLastMove[motorIndex] = cur;
			timeStoppedMoving[motorIndex] = 0;
			timeStalling[motorIndex] = time1[T1];
		}
	}
	return wantedPower;
}
timeStalling[motorIndex] = time1[T1];
return wantedPower;
}

task main ()
{
    waitForStart(); //wait until FCS tells us to go
    InitializeStallCode();

    servo[servoWristLeft] = 0;
    servo[servoWristRight] = 180;
    servo[servoLeft] = 100;
    servo[servoRight] = 160;

    //move forward away from wall
   /* motor[motorLeft] = StallCode(motorLeft, 50);
    motor[motorRight] = StallCode(motorRight, 50);
    wait1Msec(200);
    motor[motorLeft] = StallCode(motorLeft, 0);
    motor[motorRight] = StallCode(motorRight, 0);

    //lift arm so hand is at height of lowest peg. check time.
    motor[motorArm] = StallCode(motorArm, 100);
    wait1Msec(500);
    motor[motorArm] = StallCode(motorArm, 0);*/

    //create variables to store sensor outputs and set it to AC 1200Hz
    int dirAC = 1;
    int acs1, acs2, acs3, acs4, acs5 = 0;
    int maxSig = 0;
    int val = 0;
    tHTIRS2DSPMode mode = DSP_1200;

    while(dirAC != 0) //End the loop when the sensor can't read a value. Testing shows that this happens when the sensor is below the peg in front of the IR column.
    {
        dirAC = HTIRS2readACDir(irsensor);
        HTIRS2readAllACStrength(irsensor, acs1, acs2, acs3, acs4, acs5);
        maxSig = (acs1 > acs2) ? acs1 : acs2;
        maxSig = (maxSig > acs3) ? maxSig : acs3;
        maxSig = (maxSig > acs4) ? maxSig : acs4;
        maxSig = (maxSig > acs5) ? maxSig : acs5;
        writeDebugStreamLine("dir=%d", dirAC);
        writeDebugStreamLine("sig=%d", maxSig);
        val = dirAC - 6;

        if ( val == 0 )
        {
            motor[motorLeft] = StallCode(motorLeft, 50);
            motor[motorRight] = StallCode(motorRight, 50);
        }
        else
        {
            motor[motorLeft] = StallCode(motorLeft, 20 * val);
            motor[motorRight] = StallCode(motorRight, 20 * -val);
        }

        servo[servoRight] = 160;
        servo[servoLeft] = 90;

        wait10Msec(2);
    }
    return;
    /*//drive forwards into peg
    motor[motorLeft] = 10;
    motor[motorRight] = 10;
    wait1Msec(200); // check time for proper peg touching
    motor[motorLeft] = 0;
    motor[motorRight] = 0;*/

    //Place ring on rack. Servos are involved. Perhaps adjusting the arm position or the robot position.
    //Open hand?
    servo[servoRight] = 50;
    servo[servoLeft] = 200;
    wait10Msec(20);

    servo[servoWristLeft] = 100 * (255.0/180.0);
    servo[servoWristRight]= 80 * (255.0/180.0);

    motor[motorArm] = StallCode(motorArm, -100);
    wait1Msec(500);
    motor[motorArm] = StallCOde(motorArm, 0);

    motor[motorLeft] = -50;
    motor[motorRight] = -50;
    wait1Msec(250);
    motor[motorLeft] = 0;
    motor[motorRight] = 0;
}
