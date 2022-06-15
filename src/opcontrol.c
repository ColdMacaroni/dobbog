// Pins for the motors
// TODO: Check if reversed positions are ok
#define MOTOR_FL 1
#define MOTOR_FR 2  // Reversed
#define MOTOR_BL 3
#define MOTOR_BR 4  // Reversed

/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

// Declarations
/*
 * Rotates the motors just enough to take one step.
 * It's a strict step because it stops all motor movement before and after.
 */
void strict_step(int speed);

// -- Constants
const int THRESHOLD = 0;

// 127 is full forward
const int SPEED = 64;

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {

    int xLeftJoy;
    int yLeftJoy;

    int xRightJoy;
    int yRightJoy;

    /* joystickGetAnalog(unsigned char joystick, unsigned char axis); */
    while (1) {
        // Apply the threshold
        // TODO: Check that these are the correct channels
        xLeftJoy = (abs(joystickGetAnalog(1, 4)) <= THRESHOLD) ? 0 : joystickGetAnalog(1, 4);
        yLeftJoy = (abs(joystickGetAnalog(1, 3)) <= THRESHOLD) ? 0 : joystickGetAnalog(1, 3);

        xRightJoy = (abs(joystickGetAnalog(1, 1)) <= THRESHOLD) ? 0 : joystickGetAnalog(1, 1);
        yRightJoy = (abs(joystickGetAnalog(1, 2)) <= THRESHOLD) ? 0 : joystickGetAnalog(1, 2);
		
		// For testing only. Should make the bot take a steo front and back
		if (yRightJoy >= 64) {
			strict_step(SPEED);
		} else if (yRightJoy <= -64) {
			strict_step(-SPEED);
		}
		

        delay(20);
    }
}

void strict_step(int speed) {
	// Avoid any motor issues
    motorStopAll();

    // This way we can do steps FL,BR and then FR,BL and repeat. Rather than taking two steps.
    // The side to which it refers to is which front leg is moving, the back leg will be at
    // the opp. side.
    enum Side { left, right };
    static Side side = left;

    // Motors on the right side should be reversed
    if (side == left) {
        motorSet(MOTOR_FL, speed);
        motorSet(MOTOR_BR, -speed);
        side = right;

    } else if (side == right) {
        motorSet(MOTOR_FR, -speed);
        motorSet(MOTOR_BL, speed);
        side = left;
    }

    // How long to complete the step, TODO: Find this value
    delay(500);
    
    motorStopAll();
}