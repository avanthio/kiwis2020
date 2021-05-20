#include "device_setup.hpp"
#include "okapi/impl/device/controllerUtil.hpp"

okapi::Controller master(okapi::ControllerId::master);
okapi::Controller partner(okapi::ControllerId::partner);
okapi::ControllerButton intakeInBtn(okapi::ControllerId::master,okapi::ControllerDigital::L1);
okapi::ControllerButton intakeStopBtn(okapi::ControllerId::master,okapi::ControllerDigital::left);
okapi::ControllerButton conveyorTopBtn(okapi::ControllerId::master,okapi::ControllerDigital::R2);
okapi::ControllerButton conveyorBottomBtn(okapi::ControllerId::master,okapi::ControllerDigital::R1);
okapi::ControllerButton conveyorTopReverseBtn(okapi::ControllerId::master,okapi::ControllerDigital::B);
okapi::ControllerButton conveyorBottomReverseBtn(okapi::ControllerId::master, okapi::ControllerDigital::A);
okapi::ControllerButton intakeReverseBtn(okapi::ControllerId::master,okapi::ControllerDigital::L2);



okapi::Motor  leftFrontMotor(9,true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  leftBackMotor(5,false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightFrontMotor(18,false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightBackMotor(6,true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  leftIntakeMotor(1, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  rightIntakeMotor(17, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor  topConveyorMotor(10,true, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor bottomConveyorMotor(20,true,okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);
pros::Rotation rightTrackingWheel(11);
pros::Rotation leftTrackingWheel(13);
pros::Rotation backTrackingWheel(3);
pros::Vision visionSensor(21);
pros::vision_signature_s_t blue_Ball = pros::Vision::signature_from_utility(2, -3091, -1755, -2422, 8935, 13653, 11294, 3.000, 0);
pros::vision_signature_s_t red_Ball = pros::Vision::signature_from_utility(1, 5189, 8135, 6662, -555, 681, 64, 3.000, 0);
pros::Optical opticalSens(15);
okapi::MotorGroup Intake({leftIntakeMotor,rightIntakeMotor});
