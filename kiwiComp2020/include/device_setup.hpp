#pragma once

#include "main.h"

extern okapi::Controller master;
extern okapi::ControllerButton intakeInBtn;
extern okapi::ControllerButton intakeStopBtn;
extern okapi::ControllerButton conveyorStartBtn;
extern okapi::ControllerButton conveyorStopBtn;
extern okapi::ControllerButton turboBtn;
extern okapi::ControllerButton intakeReverseBtn;

extern okapi::Motor  hMotor;
extern okapi::Motor  leftFrontMotor;
extern okapi::Motor  leftBackMotor;
extern okapi::Motor  rightFrontMotor;
extern okapi::Motor  rightBackMotor;
extern okapi::Motor  leftIntakeMotor;
extern okapi::Motor  rightIntakeMotor;
extern okapi::Motor  conveyorMotor;

extern okapi::ADIEncoder rightTrackingWheel;
extern okapi::ADIEncoder leftTrackingWheel;
extern okapi::ADIEncoder backTrackingWheel;

extern okapi::MotorGroup Intake;

extern void setBrakeTypes();
