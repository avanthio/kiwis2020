#include "device_setup.hpp"

okapi::Controller master;
okapi::ControllerButton intakeInBtn(okapi::ControllerDigital::L1);
okapi::ControllerButton intakeStopBtn(okapi::ControllerDigital::L2);
okapi::ControllerButton conveyorStartBtn(okapi::ControllerDigital::R1);
okapi::ControllerButton conveyorStopBtn(okapi::ControllerDigital::R2);
okapi::ControllerButton turboBtn(okapi::ControllerDigital::X);


okapi::Motor  hMotor(14,false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  leftFrontMotor(11,false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  leftBackMotor(1,false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightFrontMotor(20,true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightBackMotor(10,true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  leftIntakeMotor(9, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightIntakeMotor(2, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  conveyorMotor(6,true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);

okapi::ADIEncoder rightTrackingWheel('G','H',true);
okapi::ADIEncoder leftTrackingWheel('A','B');
okapi::ADIEncoder rearTrackingWheel('C','F');

okapi::MotorGroup Intake({leftIntakeMotor,rightIntakeMotor});

void setBrakeTypes(){
 Intake.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
 leftBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
 rightBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
 rightFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
 leftFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
}
