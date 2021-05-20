#pragma once

#include "main.h"

extern okapi::Controller master;
extern okapi::Controller partner;
extern okapi::ControllerButton conveyorTopReverseBtn;
extern okapi::ControllerButton intakeInBtn;
extern okapi::ControllerButton intakeStopBtn;
extern okapi::ControllerButton conveyorTopBtn;
extern okapi::ControllerButton conveyorBottomBtn;
extern okapi::ControllerButton intakeReverseBtn;
extern okapi::ControllerButton conveyorBottomReverseBtn;
extern okapi::ControllerButton redBtn;
extern okapi::ControllerButton blueBtn;


extern okapi::Motor  leftFrontMotor;
extern okapi::Motor  leftBackMotor;
extern okapi::Motor  rightFrontMotor;
extern okapi::Motor  rightBackMotor;
extern okapi::Motor  leftIntakeMotor;
extern okapi::Motor  rightIntakeMotor;
extern okapi::Motor  topConveyorMotor;
extern okapi::Motor bottomConveyorMotor;
extern pros::Vision visionSensor;
extern pros::vision_signature_s_t blue_Ball;
extern pros::vision_signature_s_t red_Ball;
extern pros::Optical opticalSens;
extern pros::Rotation rightTrackingWheel;
extern pros::Rotation leftTrackingWheel;
extern pros::Rotation backTrackingWheel;

extern okapi::MotorGroup Intake;


extern void setBrakeTypes();
