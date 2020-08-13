#include "device_setup.hpp"

okapi::Controller master;
okapi::ControllerButton intakeInBtn(okapi::ControllerDigital::L1);
okapi::ControllerButton intakeStopBtn(okapi::ControllerDigital::L2);
okapi::ControllerButton conveyorStartBtn(okapi::ControllerDigital::R1);
okapi::ControllerButton conveyorStopBtn(okapi::ControllerDigital::R2);
okapi::ControllerButton turboBtn(okapi::ControllerDigital::X);
okapi::ControllerButton intakeReverseBtn(okapi::ControllerDigital::left);

okapi::Motor  hMotor(14,false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  leftFrontMotor(11,false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  leftBackMotor(1,false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightFrontMotor(20,true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightBackMotor(10,true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  leftIntakeMotor(9, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightIntakeMotor(2, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  conveyorMotor(6,false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);

okapi::ADIEncoder rightTrackingWheel('G','H',true);
okapi::ADIEncoder leftTrackingWheel('C','D');
okapi::ADIEncoder backTrackingWheel('A','B');

okapi::MotorGroup Intake({leftIntakeMotor,rightIntakeMotor});
