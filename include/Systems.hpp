#pragma once

#include "api.h"
#include "lemlib/api.hpp"

//remember to initialize your sensors here
//the name should match the name used in your Systems.cpp file
extern pros::Motor intake;
extern pros::adi::DigitalOut piston;

extern pros::Controller master;

extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

extern pros::Imu imu;

extern pros::Rotation horizontalEnc;
extern pros::Rotation verticalEnc;

extern lemlib::TrackingWheel horizontal;
extern lemlib::TrackingWheel vertical;

extern lemlib::Drivetrain drivetrain;

extern lemlib::ControllerSettings linearController;
extern lemlib::ControllerSettings angularController;

extern lemlib::OdomSensors sensors;

extern lemlib::ExpoDriveCurve throttleCurve;
extern lemlib::ExpoDriveCurve steerCurve;

extern lemlib::Chassis chassis;
