#ifndef PID_TASK_C
#define PID_TASK_C

#include "pid_includes.h"

task PID()
{
	while(true)
	{
		// LEFT MOTORS //
		int leftError = leftMotorRequestedSpeed - GetLeftMotorSpeed();
		pidLeftProportional = leftError;
		pidLeftIntegral += (leftError * pidChangeTime);
		pidLeftDerivative = (leftError - pidLeftPreviousError) / pidChangeTime;
		int finalLeftMotorPower = (pidPConst * pidLeftProportional) + (pidIConst * pidLeftIntegral) + (pidDConst * pidLeftDerivative);
		pidLeftPreviousError = leftError;

		SetLeftMotorSpeed(finalLeftMotorPower);

		// RIGHT MOTORS //
		int rightError = rightMotorRequestedSpeed - GetRightMotorSpeed();
		pidRightProportional = rightError;
		pidRightIntegral += (rightError * pidChangeTime);
		pidRightDerivative = (rightError - pidRightPreviousError) / pidChangeTime;
		int finalRightMotorPower = (pidPConst * pidRightProportional) + (pidIConst * pidRightIntegral) + (pidDConst * pidRightDerivative);
		pidRightPreviousError = rightError;

		SetRightMotorSpeed(finalRightMotorPower);

		// Time Delay //
		wait1Msec(pidChangeTime);
	}
}

#endif
