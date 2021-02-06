#include "device_setup.hpp"

okapi::Controller master(okapi::ControllerId::master);
okapi::Controller partner(okapi::ControllerId::partner);
okapi::ControllerButton intakeInBtn(okapi::ControllerId::partner,okapi::ControllerDigital::L1);
okapi::ControllerButton intakeStopBtn(okapi::ControllerId::partner,okapi::ControllerDigital::L2);
okapi::ControllerButton conveyorTopBtn(okapi::ControllerId::partner,okapi::ControllerDigital::R2);
okapi::ControllerButton conveyorBottomBtn(okapi::ControllerId::partner,okapi::ControllerDigital::R1);
okapi::ControllerButton conveyorTopReverseBtn(okapi::ControllerId::partner,okapi::ControllerDigital::B);
okapi::ControllerButton conveyorBottomReverseBtn(okapi::ControllerId::partner, okapi::ControllerDigital::A);
okapi::ControllerButton driveSwitchBtn(okapi::ControllerId::master,okapi::ControllerDigital::down);
okapi::ControllerButton intakeReverseBtn(okapi::ControllerId::partner,okapi::ControllerDigital::left);



okapi::Motor  leftFrontMotor(9,false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  leftBackMotor(5,false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightFrontMotor(18,true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightBackMotor(6,true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  leftIntakeMotor(1, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightIntakeMotor(17, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  topConveyorMotor(10,true, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor bottomConveyorMotor(20,true,okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);
okapi::ADIEncoder rightTrackingWheel('G','H');
okapi::ADIEncoder leftTrackingWheel('C','D',true);
okapi::ADIEncoder backTrackingWheel('A','B');

okapi::MotorGroup Intake({leftIntakeMotor,rightIntakeMotor});
