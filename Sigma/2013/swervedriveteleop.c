#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorFR,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorBR,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorBL,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorFL,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    servoBL,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servoFL,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servoBR,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    servoFR,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c";

float slowMult = 1;
int deadZone = 10;
float degToServo = (255.0/192.0);

task main()
{
	servo[servoFL] = 0;
	servo[servoFR] = 0;
	servo[servoBL] = 0;
	servo[servoBR] = 0;

	while (true)
	{
		getJoystickSettings(joystick);

		int pos = atan(joystick.joy1_y2 / joystick.joy1_x2);
		if(joystick.joy1_x2 == 0)
		{
			pos = 0;
		}
		float dist = sqrt(joystick.joy1_y2 * joystick.joy1_y2 + joystick.joy1_x2 * joystick.joy1_x1);

		if (joystick.joy1_Buttons == 6)
		{
			slowMult = 1;
		}
		else
		{
			slowMult = 0.3;
		}

		int motorPower = (int)(dist * slowMult * 0.75);

		if (joystick.joy1_y2 > deadZone && joystick.joy1_x2 > deadZone)
		{
			motor[motorFL] = motorPower;
			motor[motorFR] = motorPower;
			motor[motorBL] = motorPower;
			motor[motorBR] = motorPower;

			int servoPos = (int)(pos * degToServo);

			servo[servoFL] = servoPos;
			servo[servoFR] = servoPos;
			servo[servoBL] = servoPos;
			servo[servoBR] = servoPos;
		}
		else if (joystick.joy1_y2 > deadZone && joystick.joy1_x2 < (-1 * deadZone))
		{
			motor[motorFL] = motorPower;
			motor[motorFR] = motorPower;
			motor[motorBL] = motorPower;
			motor[motorBR] = motorPower;

			int servoPos = (int)((pos + 90) * degToServo);

			servo[servoFL] = servoPos;
			servo[servoFR] = servoPos;
			servo[servoBL] = servoPos;
			servo[servoBR] = servoPos;
		}
		else if (joystick.joy1_y2 < (-1 * deadZone) && joystick.joy1_x2 < (-1 * deadZone))
		{
			motor[motorFL] = motorPower * -1;
			motor[motorFR] = motorPower * -1;
			motor[motorBL] = motorPower * -1;
			motor[motorBR] = motorPower * -1;

			int servoPos = (int)(pos * degToServo);

			servo[servoFL] = servoPos;
			servo[servoFR] = servoPos;
			servo[servoBL] = servoPos;
			servo[servoBR] = servoPos;
		}
		else if (joystick.joy1_y2 < (-1 * deadZone) && joystick.joy1_x2 > deadZone)
		{
			motor[motorFL] = motorPower * -1;
			motor[motorFR] = motorPower * -1;
			motor[motorBL] = motorPower * -1;
			motor[motorBR] = motorPower * -1;

			int servoPos = (int)((pos + 90) * degToServo);

			servo[servoFL] = servoPos;
			servo[servoFR] = servoPos;
			servo[servoBL] = servoPos;
			servo[servoBR] = servoPos;
		}
		else
		{
			motor[motorFL] = 0;
			motor[motorFR] = 0;
			motor[motorBL] = 0;
			motor[motorBR] = 0;
		}

	}

}
