#include "device_setup.hpp"

okapi::Controller master;
okapi::ControllerButton intakeInBtn(okapi::ControllerDigital::L1);
okapi::ControllerButton intakeStopBtn(okapi::ControllerDigital::L2);
okapi::ControllerButton conveyorTopBtn(okapi::ControllerDigital::R1);
okapi::ControllerButton conveyorBottomBtn(okapi::ControllerDigital::R2);
okapi::ControllerButton conveyorReverseBtn(okapi::ControllerDigital::B);
okapi::ControllerButton turboBtn(okapi::ControllerDigital::X);
okapi::ControllerButton driveSwitchBtn(okapi::ControllerDigital::down);
okapi::ControllerButton intakeReverseBtn(okapi::ControllerDigital::left);

okapi::Motor  leftFrontMotor(1,false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  leftBackMotor(13,false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightFrontMotor(10,true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightBackMotor(17,true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  leftIntakeMotor(12, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightIntakeMotor(9, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  topConveyorMotor(2,true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor bottomConveyorMotor(11,true,okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::ADIEncoder rightTrackingWheel('G','H',true);
okapi::ADIEncoder leftTrackingWheel('C','D');
okapi::ADIEncoder backTrackingWheel('A','B');

okapi::MotorGroup Intake({leftIntakeMotor,rightIntakeMotor});
