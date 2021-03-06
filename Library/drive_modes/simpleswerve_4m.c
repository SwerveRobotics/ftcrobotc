#ifndef SWERVE_4M_C
#define SWERVE_4M_C

///////////// CODE REVIEW BY DRYW ///////////////////
// File name is too simialr to simple_swerve_4m.c and swerve_4m.c
// Some functions below need comments to describe what they do
// File doesn't compile

#include "../controllers/controller_defines.h"
#include "../motors/motors.c"

// these variables will be used to write to the motors and servos
tMotor FRONT_LEFT_MOTOR;
tMotor BACK_LEFT_MOTOR;
tMotor FRONT_RIGHT_MOTOR;
tMotor BACK_RIGHT_MOTOR;

TServoIndex FRONT_LEFT_SERVO;
TServoIndex BACK_LEFT_SERVO;
TServoIndex FRONT_RIGHT_SERVO;
TServoIndex BACK_RIGHT_SERVO;

int joystickRange = MAX_ANALOG - ANALOG_DEAD_ZONE; //allowed input range along any axis from the joystick.


//-------------------------------------------------------------------------------------------------//
// !!! IMPORTANT - The following three functions MUST be called, else the drive will not work. !!! //
//-------------------------------------------------------------------------------------------------//

//register the motors clockwise
void RegisterMotors(tMotor frontLeftM, tMotor backLeftM, tMotor frontRightM, tMotor backRightM)
{
	FRONT_LEFT_MOTOR = frontLeftM;
	BACK_LEFT_MOTOR = backLeftM;
	FRONT_RIGHT_MOTOR = frontRightM;
	BACK_RIGHT_MOTOR = backRightM;
}

//register the servos clockwise
void RegisterServos(TServoIndex frontLeftS, TServoIndex backLeftS, TServoIndex frontRightS, TServoIndex backRightS)
{
	FRONT_LEFT_SERVO = frontLeftS;
	BACK_LEFT_SERVO = backLeftS;
	FRONT_RIGHT_SERVO = frontRightS;
	BACK_RIGHT_SERVO = backRightS;
}



//--------------------------------------//
//   !!! End of required funtions !!!   //
//--------------------------------------//




//Attenuate the joystick used for rotation based on the maximum angular speed possible
//and find the "desired" angular velocity.
float JoystickToRotRate(float joystickZ)
{

	float attenuationSlope =  1 / joystickRange;
	//mapping maximum rotational speed to the allowed joystick input range, aka. finding the slope.

	float attenuationIntercept = -1 * ANALOG_DEAD_ZONE * sgn(joystickZ) * attenuationSlope;
	//finding the range taken up by the dead zone, aka. finding the intercept.

	if (abs(joystickZ) < ANALOG_DEAD_ZONE)
	{
		return 0;
	}
	else
	{
		return attenuationSlope * joystickZ + attenuationIntercept;
	}

}

float JoystickToCMPerSec(float joystickXorY)
{
	float attenuationSlope = joystickRange / MAX_MOTOR_POWER;

	float attenuationIntercept = -1 * sgn(joystickXorY) * attenuationSlope

	if (abs(joystickXorY) < ANALOG_DEAD_ZONE)
	{
		return 0;
	}
	else
	{
		return (joystickXorY * attenuationSlope) + attenuationIntercept;
	}
}

float CalculateDriveAngle(float valueX, float valueY)
{
	int tangent = 57.3 * atan2(valueX, valueY); //drive angle
	if (tangent < 0)
	{
		return tangent + 360;
	}
	else
	{
		return tangent;
	}

}

void SimpleWriteToDevices(int magnitude, int servoPosition){

	mpsToMotor(  FRONT_RIGHT_MOTOR, magnitude);
	mpsToMotor(  FRONT_LEFT_MOTOR,  magnitude);
	mpsToMotor(  BACK_LEFT_MOTOR,   magnitude);
	mpsToMotor(  BACK_RIGHT_MOTOR,  magnitude);

	degToCRServo(FRONT_RIGHT_SERVO, servoPosition);
	degToCRServo(FRONT_LEFT_SERVO,  servoPosition);
	degToCRServo(BACK_LEFT_SERVO,   servoPosition);
	degToCRServo(BACK_RIGHT_SERVO,  servoPosition);
}

#endif
