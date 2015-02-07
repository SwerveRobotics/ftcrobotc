#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Hubs,  S3, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     motorFan1,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     motorFan2,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     motorSweep,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servoFL,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_2,    servoBL,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_3,    servoTubeSlide,       tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_4,    servo1_3_4,           tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_5,    servo1_3_5,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_6,    servo1_3_6,           tServoStandard)
#pragma config(Servo,  srvo_S2_C3_1,    servoFR,              tServoStandard)
#pragma config(Servo,  srvo_S2_C3_2,    servoBR,              tServoStandard)
#pragma config(Servo,  srvo_S2_C3_3,    servoTubeLift,           tServoStandard)
#pragma config(Servo,  srvo_S2_C3_4,    servo2_3_4,           tServoStandard)
#pragma config(Servo,  srvo_S2_C3_5,    servo2_3_5,           tServoStandard)
#pragma config(Servo,  srvo_S2_C3_6,    servo2_3_6,           tServoStandard)
#pragma config(Servo,  srvo_S3_C1_1,    servoSweepArm,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S3_C1_2,    servoTubeWinch,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S3_C1_3,    servoLoader,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S3_C1_4,    servo3_1_4,           tServoContinuousRotation)
#pragma config(Servo,  srvo_S3_C1_5,    servo3_1_5,           tServoStandard)
#pragma config(Servo,  srvo_S3_C1_6,    servo3_1_6,           tServoStandard)
#pragma config(Servo,  srvo_S3_C2_1,    servoSweep1,        tServoStandard)
#pragma config(Servo,  srvo_S3_C2_2,    servoSweep2,       tServoStandard)
#pragma config(Servo,  srvo_S3_C2_3,    servoGrabber,         tServoStandard)
#pragma config(Servo,  srvo_S3_C2_4,    servo3_2_4,           tServoStandard)
#pragma config(Servo,  srvo_S3_C2_5,    servo3_2_5,           tServoStandard)
#pragma config(Servo,  srvo_S3_C2_6,    servo3_2_6,           tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "../includes/read_write.c"
#include "../JoystickDriver.c"
#include "../../library/drive_modes/simple_swerve_4m.c"
#include "../includes/manipulators.c"
task main()
{
	RegisterMotors(
	motorFL,
	motorFR,
	motorBL,
	motorBR,
	motorSweep,
	motorFan1,
	motorFan2
	);
	RegisterServos(
	servoFR,
	servoFL,
	servoBL,
	servoBR,
	servoGrabber,
	servoSweepArm,
	servoTubeWinch,
	servoTubeLift,
	servoTubeSlide,
	servoLoader,
	servoSweep1,
	servoSweep2,
	);


	float Kp = 0.008;
	float Ki = 0.015;
	float Kd = 0.000;
	float errorPrevSum = 0;
	float errorPrev = 0;
	float error;
	float ang = 0.0;
	float newAng = 0.0;
	float n = 0.0;
	float angPrev = 0.0;
	float newAngPrev = 0.0;
	float servoSpeed = 0.0;

	//

	float errorPrevSum2 = 0;
	float errorPrev2 = 0;
	float error2;
	float ang2 = 0.0;
	float newAng2 = 0.0;
	float n2 = 0.0;
	float angPrev2 = 0.0;
	float newAngPrev2 = 0.0;
	float servoSpeed2 = 0.0;

	//

	float errorPrevSum3 = 0;
	float errorPrev3 = 0;
	float error3;
	float ang3 = 0.0;
	float newAng3 = 0.0;
	float n3 = 0.0;
	float angPrev3 = 0.0;
	float newAngPrev3 = 0.0;
	float servoSpeed3 = 0.0;

	//

	float errorPrevSum4 = 0;
	float errorPrev4 = 0;
	float error4;
	float ang4 = 0.0;
	float newAng4 = 0.0;
	float n4 = 0.0;
	float angPrev4 = 0.0;
	float newAngPrev4 = 0.0;
	float servoSpeed4 = 0.0;

	waitForStart();
	StartTask(manipulators);
	float joyDistance;
	float joyAngle;
	int joyX;
	int joyY;
	int joyZ;

	while(true)
	{
		joyX = joystick.joy1_x2;
		joyY = joystick.joy1_y2;
		joyZ = joystick.joy1_x1;
		joyDistance = sqrt( pow(joyX, 2) + pow( joyY, 2) );
		joyAngle = 57.3 * atan2(joyY, joyX);

		if (JoystickToRotRate(joyZ) > 0)
		{
			int powe = JoystickToMagnitude(joyZ);
			motor[Assembly[FRONT_LEFT].driveMotor] = powe;
			motor[Assembly[FRONT_RIGHT].driveMotor] = powe;
			motor[Assembly[BACK_LEFT].driveMotor] = powe;
			motor[Assembly[BACK_RIGHT].driveMotor] = powe;

		}
		else
		{
			int powe = JoystickToMagnitude(joyDistance);
			motor[Assembly[FRONT_LEFT].driveMotor] = -1 *powe;
			motor[Assembly[FRONT_RIGHT].driveMotor] = powe;
			motor[Assembly[BACK_LEFT].driveMotor] = -1 * powe;
			motor[Assembly[BACK_RIGHT].driveMotor] = powe;
		}

		angPrev = ang;
		newAngPrev = newAng;
		if (JoystickToRotRate(joyZ) > 0)
		{
			newAng = -45.0 + n;
		}
		else if (JoystickToMagnitude(joyDistance) > 0)
		{
			ang = joyAngle;

			if (abs(ang) > 90)
			{
				if (sgn(ang * angPrev) == -1)
				{
					n = n + -1 * sgn(ang);
				}
			}
			if (n > 3)
			{
				n = 4.0;
			}
			else if (n < -3)
			{
				n = -3.0;
			}
			newAng = ang + n * 360 - 90;
		}
		error = newAng - GetCRServoPosition(FRONT_LEFT);
		servoSpeed = ( Kp * error ) + ( Ki * errorPrevSum ) + ( Kd * (error - errorPrev) );

		servo[Assembly[FRONT_LEFT].driveServo] = 127 * ( -1 * servoSpeed + 1);

		errorPrev = error;
		errorPrevSum = errorPrevSum + errorPrev * 0.005;

		//

		angPrev2 = ang2;
		newAngPrev2 = newAng2;
		if (JoystickToRotRate(joyZ) > 0)
		{
			newAng2 = 225.0 + n2;
		}
		else if ( JoystickToMagnitude(joyDistance) > 0)
		{
			ang2 = joyAngle;

			if (abs(ang2) > 90)
			{
				if (sgn(ang2 * angPrev2) == -1)
				{
					n2 = n2 + -1 * sgn(ang2);
				}
			}
			if (n2 > 3)
			{
				n2 = 4.0;
			}
			else if (n2 < -3)
			{
				n2 = -3.0;
			}
			newAng2 = ang2 + n2 * 360 - 90;
		}
		error2 = newAng2 - GetCRServoPosition(FRONT_RIGHT);
		servoSpeed2 = ( Kp * error2 ) + ( Ki * errorPrevSum2 ) + ( Kd * (error2 - errorPrev2) );

		servo[Assembly[FRONT_RIGHT].driveServo] = 127 * (servoSpeed2 + 1);

		errorPrev2 = error2;
		errorPrevSum2 = errorPrevSum2 + errorPrev2 * 0.005;

		//

		angPrev3 = ang3;
		newAngPrev3 = newAng3;
		if (JoystickToRotRate(joyZ) > 0)
		{
			newAng3 = -135.0 + n3 + 180;
		}
		else if ( JoystickToMagnitude(joyDistance) > 0)
		{
			ang3 = joyAngle;

			if (abs(ang3) > 90)
			{
				if (sgn(ang3 * angPrev3) == -1)
				{
					n3 = n3 + -1 * sgn(ang3);
				}
			}
			if (n3 > 3)
			{
				n3 = 4.0;
			}
			else if (n3 < -3)
			{
				n3 = -3.0;
			}
			newAng3 = ang3 + n3 * 360 - 90;
		}
		error3 = newAng3 - GetCRServoPosition(BACK_LEFT);
		servoSpeed3 = ( Kp * error3 ) + ( Ki * errorPrevSum3 ) + ( Kd * (error3 - errorPrev3) );

		servo[Assembly[BACK_LEFT].driveServo] = 127 * (-1 * servoSpeed3 + 1);

		errorPrev3 = error3;
		errorPrevSum3 = errorPrevSum3 + errorPrev3 * 0.005;

		//

		angPrev4 = ang4;
		newAngPrev4 = newAng4;
		if (JoystickToRotRate(joyZ) > 0)
		{
			newAng4 = -45.0 + n4 + 180;
		}
		else if ( JoystickToMagnitude(joyDistance) > 0)
		{
			ang4 = joyAngle;

			if (abs(ang4) > 90)
			{
				if (sgn(ang4 * angPrev4) == -1)
				{
					n4 = n4 + -1 * sgn(ang4);
				}
			}
			if (n4 > 3)
			{
				n4 = 4.0;
			}
			else if (n4 < -3)
			{
				n4 = -3.0;
			}
			newAng4 = ang4 + n4 * 360 - 90;
		}

		error4 = newAng4 - GetCRServoPosition(BACK_RIGHT);
		servoSpeed4 = ( Kp * error4 ) + ( Ki * errorPrevSum4 ) + ( Kd * (error4 - errorPrev4) );

		servo[Assembly[BACK_RIGHT].driveServo] = 127 * (servoSpeed4 + 1);

		errorPrev4 = error4;
		errorPrevSum4 = errorPrevSum4 + errorPrev4 * 0.005;

		wait1Msec(100);

	}
}