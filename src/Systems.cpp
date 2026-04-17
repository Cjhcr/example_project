#include "Systems.hpp"
#include "lemlib/api.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);

//your motors and other devices here, the intake and piston are just examples, you can change them to match your own code
//negative ports are reversed, so the motors will spin in the opposite direction
pros::Motor intake(8, pros::MotorGearset::blue);
pros::adi::DigitalOut piston ('A');

//drive train motors
pros::MotorGroup leftMotors({-5, 4, -3}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({6, -9, 7}, pros::MotorGearset::blue);

pros::Imu imu(10);

pros::Rotation horizontalEnc(20);
pros::Rotation verticalEnc(-11);

lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_2, 0);
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_2, 0);

lemlib::Drivetrain drivetrain(&leftMotors,
                              &rightMotors,
                              10,
                              lemlib::Omniwheel::NEW_4,
                              450,
                              2);

lemlib::ControllerSettings linearController(10,
                                            0,
                                            3,
                                            3,
                                            1,
                                            100,
                                            3,
                                            500,
                                            20);

lemlib::ControllerSettings angularController(2,
                                             0,
                                             10,
                                             3,
                                             1,
                                             100,
                                             3,
                                             500,
                                             0);

lemlib::OdomSensors sensors(&vertical,  //vertical 1
                            nullptr,    //vertical 2 (optional)
                            &horizontal,    //horizontal 1
                            nullptr,    //horizontal 2 (optional)
                            &imu);

lemlib::ExpoDriveCurve throttleCurve(3,
                                     10,
                                     1.019);

lemlib::ExpoDriveCurve steerCurve(3,
                                  10,
                                  1.019);

lemlib::Chassis chassis(drivetrain,
                       linearController,
                       angularController,
                       sensors,
                       &throttleCurve,
                       &steerCurve);
