#include "device_management.hpp"

void setBrakeTypes(){
 Intake.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
 leftBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
 rightBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
 rightFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
 leftFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
 hMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
 conveyorMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
}

void resetDevices(){
  Intake.tarePosition();
  leftFrontMotor.tarePosition();
  rightBackMotor.tarePosition();
  leftBackMotor.tarePosition();
  rightFrontMotor.tarePosition();
  conveyorMotor.tarePosition();
  hMotor.tarePosition();
  leftTrackingWheel.reset();
  rightTrackingWheel.reset();
  backTrackingWheel.reset();

}
