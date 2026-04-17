#include "Auton.hpp"
#include "Systems.hpp"

void example() {
  chassis.setPose(0, 0,
                  0); // set the pose of the chassis to x = 0, y = 0, theta = 0

  chassis.moveToPoint(
      10, 10, 4000); // move the chassis to (10, 10), with a timeout of 4000 ms
  // move the chassis to x = 20, y = 15 with a timeout of 4000ms
  // but face the point with the back of the chassis

  chassis.moveToPoint(20, 15, 4000, {.forwards = false}, true);
  // turn the robot to face the point x = 45, y = -45, with a timeout of 1000ms

  chassis.moveToPose(10, 10, 90, 4000); // move the chassis to (10, 10, 90)
                                        // with a timeout of 4000 ms

  chassis.moveToPose(0, 0, 0, 4000, {.horizontalDrift = 8, .lead = 0.3});

  chassis.turnToPoint(45, -45, 1000);
  // turn the robot to face the point x = 45, y = -45, with a timeout of 1000ms
  // but face the point with the back of the robot

  chassis.turnToPoint(45, -45, 1000, {.forwards = false});
  // turn the robot to face the point x = -20, 32.5 with a timeout of 2000ms
  // and a maximum speed of 60

  chassis.turnToPoint(-20, 32.5, 2000, {.maxSpeed = 60});
  // turn the robot to face the point x = -30, y = 22.5 with a timeout of 1500ms
  // and turn counterclockwise

  chassis.turnToPoint(-30, 22.5, 1500,
                      {.direction = AngularDirection::CCW_COUNTERCLOCKWISE});
  // turn the robot to face the point x = 10, y = 10 with a timeout of 500ms
  // with a minSpeed of 20 and a maxSpeed of 60

  chassis.turnToPoint(10, 10, 500, {.maxSpeed = 60, .minSpeed = 20});
  // turn the robot to face the point x = 7.5, y = 7.5 with a timeout of 2000ms
  // and a minSpeed of 60, and exit the movement if the robot is within 5
  // degrees of the target

  chassis.turnToPoint(7.5, 7.5, 2000, {.minSpeed = 60, .earlyExitRange = 5});

  intake.move(127);  // move the intake motor forward at full speed
  pros::delay(1000); // wait for 1 second

  intake.move(0);         // stop the intake motor
  piston.set_value(true); // activate the piston
  pros::delay(500);       // wait for 0.5 seconds

  piston.set_value(false); // deactivate the piston
}

void awp() {}
// create more auton functions here and call them in autonomous() in main.cpp
// you should also declare the functions in Auton.hpp
