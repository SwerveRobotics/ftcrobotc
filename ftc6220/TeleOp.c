#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S3_C1_1,    servoFR,              tServoStandard)
#pragma config(Servo,  srvo_S3_C1_2,    servoFL,              tServoStandard)
#pragma config(Servo,  srvo_S3_C1_3,    servoBL,              tServoStandard)
#pragma config(Servo,  srvo_S3_C1_4,    servoBR,              tServoStandard)
#pragma config(Servo,  srvo_S3_C1_5,    servoBrush1,          tServoStandard)
#pragma config(Servo,  srvo_S3_C1_6,    servoBrush2,          tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define MOTOR_GEAR_RATIO (1.206)
#define MOTOR_RADIUS (5.3)

#include "Joystick_Swive_Functions.c"
#include "Swive_Drive.c"
#include "Manipulator_Control.c"

task main()
{
	StartTask(Drive);
	while(true)
	{
		//...
	}

}
