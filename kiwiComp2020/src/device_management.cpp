#include "device_management.hpp"

void setBrakeTypes(){
 Intake.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
 leftBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
 rightBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
 rightFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
 leftFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
 topConveyorMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
 bottomConveyorMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
}


void resetDevices(){
  Intake.tarePosition();
  leftFrontMotor.tarePosition();
  rightBackMotor.tarePosition();
  leftBackMotor.tarePosition();
  rightFrontMotor.tarePosition();
  topConveyorMotor.tarePosition();
  bottomConveyorMotor.tarePosition();

}
