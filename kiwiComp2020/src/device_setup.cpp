#include "device_setup.hpp"

okapi::Controller master(okapi::ControllerId::master);
okapi::Controller partner(okapi::ControllerId::partner);
okapi::ControllerButton intakeInBtn(okapi::ControllerId::master,okapi::ControllerDigital::L1);
okapi::ControllerButton intakeStopBtn(okapi::ControllerId::master,okapi::ControllerDigital::L2);
okapi::ControllerButton conveyorTopBtn(okapi::ControllerId::master,okapi::ControllerDigital::R2);
okapi::ControllerButton conveyorBottomBtn(okapi::ControllerId::master,okapi::ControllerDigital::R1);
okapi::ControllerButton conveyorTopReverseBtn(okapi::ControllerId::master,okapi::ControllerDigital::B);
okapi::ControllerButton conveyorBottomReverseBtn(okapi::ControllerId::master, okapi::ControllerDigital::A);
okapi::ControllerButton driveSwitchBtn(okapi::ControllerId::master,okapi::ControllerDigital::down);
okapi::ControllerButton intakeReverseBtn(okapi::ControllerId::master,okapi::ControllerDigital::left);



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
