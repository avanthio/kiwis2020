#include "device_setup.hpp"


okapi::Controller master;
okapi::ControllerButton intakeInBtn(okapi::ControllerDigital::L1);
okapi::ControllerButton intakeStopBtn(okapi::ControllerDigital::L2);
okapi::ControllerButton conveyorFastBtn(okapi::ControllerDigital::R1);
okapi::ControllerButton conveyorSlowBtn(okapi::ControllerDigital::A);
okapi::ControllerButton conveyorStopBtn(okapi::ControllerDigital::R2);
okapi::ControllerButton conveyorReverseBtn(okapi::ControllerDigital::B);
okapi::ControllerButton turboBtn(okapi::ControllerDigital::X);
okapi::ControllerButton driveSwitchBtn(okapi::ControllerDigital::down);
okapi::ControllerButton intakeReverseBtn(okapi::ControllerDigital::left);

okapi::Motor  leftFrontMotor(11,false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  leftBackMotor(1,false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightFrontMotor(20,true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightBackMotor(10,true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  leftIntakeMotor(2, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightIntakeMotor(9, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  topConveyorMotor(6,false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor bottomConveyorMotor(7,true,okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);
okapi::ADIEncoder rightTrackingWheel('G','H',true);
okapi::ADIEncoder leftTrackingWheel('C','D');
okapi::ADIEncoder backTrackingWheel('A','B');

okapi::MotorGroup Intake({leftIntakeMotor,rightIntakeMotor});
