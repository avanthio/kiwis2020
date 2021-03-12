#include "device_setup.hpp"

okapi::Controller master(okapi::ControllerId::master);
okapi::Controller partner(okapi::ControllerId::partner);
okapi::ControllerButton intakeInBtn(okapi::ControllerId::partner,okapi::ControllerDigital::L1);
okapi::ControllerButton intakeStopBtn(okapi::ControllerId::partner,okapi::ControllerDigital::L2);
okapi::ControllerButton conveyorTopBtn(okapi::ControllerId::partner,okapi::ControllerDigital::R2);
okapi::ControllerButton conveyorBottomBtn(okapi::ControllerId::partner,okapi::ControllerDigital::R1);
okapi::ControllerButton conveyorTopReverseBtn(okapi::ControllerId::partner,okapi::ControllerDigital::B);
okapi::ControllerButton conveyorBottomReverseBtn(okapi::ControllerId::partner, okapi::ControllerDigital::A);
okapi::ControllerButton driveSwitchBtn(okapi::ControllerId::partner,okapi::ControllerDigital::down);
okapi::ControllerButton intakeReverseBtn(okapi::ControllerId::partner,okapi::ControllerDigital::left);



okapi::Motor  leftFrontMotor(9,true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  leftBackMotor(5,false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightFrontMotor(18,false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightBackMotor(6,true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  leftIntakeMotor(1, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightIntakeMotor(17, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  topConveyorMotor(10,true, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor bottomConveyorMotor(20,true,okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);
okapi::ADIEncoder rightTrackingWheel('G','H');
okapi::ADIEncoder leftTrackingWheel('C','D',true);
okapi::ADIEncoder backTrackingWheel('A','B');
pros::Vision visionSensor(21);
pros::vision_signature_s_t blue_Ball = pros::Vision::signature_from_utility(1, -3277, -1651, -2464, 10133, 15719, 12926, 3, 0);

okapi::MotorGroup Intake({leftIntakeMotor,rightIntakeMotor});
