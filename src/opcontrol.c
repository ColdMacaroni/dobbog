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
 * Rotates the motors just enough to take a singular step.
 */
void step(void);

// -- Constants
const int threshold = 0;

// 127 is full forward
const int speed = 64;

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
        xLeftJoy = (abs(joystickGetAnalog(1, 4)) <= threshold) ? 0 : joystickGetAnalog(1, 4);
        yLeftJoy = (abs(joystickGetAnalog(1, 3)) <= threshold) ? 0 : joystickGetAnalog(1, 3);

        xRightJoy = (abs(joystickGetAnalog(1, 1)) <= threshold) ? 0 : joystickGetAnalog(1, 1);
        yRightJoy = (abs(joystickGetAnalog(1, 2)) <= threshold) ? 0 : joystickGetAnalog(1, 2);

        delay(20);
    }
}
