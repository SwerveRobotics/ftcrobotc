#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorFR,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorFL,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorBL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorBR,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorArm,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    servoFR,              tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servoBR,              tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servoBL,              tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    servoFL,              tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c";

float degToServo = (255.0/192.0); // converts degrees into servo values

task main()
{
	waitForStart();

	nMotorEncoder[motorBL] = 0; // zero encoder

	// set servos to default position
	servo[servoFL] = 90 * degToServo;
	servo[servoFR] = 90 * degToServo;
	servo[servoBL] = 90 * degToServo;
	servo[servoBR] = 90 * degToServo;
	wait1Msec(200);

	while(nMotorEncoder[motorBL] > (-1440 * 0.25)) // back away from wall 0.5 rev
	{
		motor[motorFL] = -50;
		motor[motorFR] = -50;
		motor[motorBL] = -50;
		motor[motorBR] = -50;
	}
	// stop motors
	motor[motorFL] = 0;
	motor[motorFR] = 0;
	motor[motorBL] = 0;
	motor[motorBR] = 0;

	// line up servos so the robot can move to line up with the ramp
	servo[servoFL] = 135 * degToServo;
	servo[servoFR] = 135 * degToServo;
	servo[servoBL] = 135 * degToServo;
	servo[servoBR] = 135 * degToServo;
	wait1Msec(200);

	while(nMotorEncoder[motorBL] > (-1440 * 2)) // move robot to line up with ramp 1.75 rev
	{
		motor[motorFL] = -50;
		motor[motorFR] = -50;
		motor[motorBL] = -50;
		motor[motorBR] = -50;
	}
	// stop motors
	motor[motorFL] = 0;
	motor[motorFR] = 0;
	motor[motorBL] = 0;
	motor[motorBR] = 0;

	// line up servos so the robot can move up the ramp
	servo[servoFL] = 90 * degToServo;
	servo[servoFR] = 90 * degToServo;
	servo[servoBL] = 90 * degToServo;
	servo[servoBR] = 90 * degToServo;
	wait1Msec(200);

	nMotorEncoder[motorBL] = 0;
	while(nMotorEncoder[motorBL] > (-1440 * 2)) // move robot to line up with ramp 3 rev
	{
		motor[motorFL] = -100;
		motor[motorFR] = -100;
		motor[motorBL] = -100;
		motor[motorBR] = -100;
	}
	// stop motors
	motor[motorFL] = 0;
	motor[motorFR] = 0;
	motor[motorBL] = 0;
	motor[motorBR] = 0;
}
