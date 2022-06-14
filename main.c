#pragma config(Motor,  port1,           frontLeftMotor,    tmotorNormal, openLoop)
#pragma config(Motor,  port2,           frontRightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           backLeftMotor,     tmotorNormal, openLoop)
#pragma config(Motor,  port4,           backRightMotor,     tmotorNormal, openLoop, reversed)

task main()
{
	// Threshhold in case the joystick doesnt stop exactly at centre
	const float threshold = 5.0;
	const float speed = 0.5;

	float xLeftJoy;
	float yLeftJoy;

	float xRightJoy;
	float yRightJoy;

	// Main loop
	while(1)
	{
		// Apply the threshold
		xLeftJoy = (abs(vexRT[Ch4]) <= threshold) ? 0 : vexRT[Ch4];
		yLeftJoy = (abs(vexRT[Ch3]) <= threshold) ? 0 : vexRT[Ch3];

		xRightJoy = (abs(vexRT[Ch1]) <= threshold) ? 0 : vexRT[Ch1];
		yRightJoy = (abs(vexRT[Ch2]) <= threshold) ? 0 : vexRT[Ch2];

        // The commented out code is from https://github.com/ColdMacaroni/robotcafe-attempt/blob/main/cafe.c

        /*
		//Driving Motor Control
		motor[forwardMotorA] = joyFwdA * speed;
		motor[forwardMotorB] = joyFwdB * speed;

		motor[sideMotorA] = joySidA * speed;
		motor[sideMotorB] = joySidB * speed;
        */
        /*
		//Carriage Control
		if(vexRT[Btn8D])
		{
			motor[carriageMotor] = carriageSpeed;
		}
		else if(vexRT[Btn8R])
		{
			motor[carriageMotor] = carriageSpeed * -1;
		}
		else
		{
			motor[carriageMotor] = 0;
		}
        */

        /*
		// Hand control
		// I'm not sure which is open and which is close
		if(vexRT[Btn7D])
		{
			motor[handMotor] = handSpeed;
		}
		else if(vexRT[Btn7R])
		{
			motor[handMotor] = handSpeed * -1;
		}
		else
		{
			motor[handMotor] = 0;
		}
        */
	}
}
