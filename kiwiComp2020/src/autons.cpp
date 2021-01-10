#include "autons.hpp"

void redFrontAuton(){


}

void redBackAuton(){

}

void blueFrontAuton(){
  struct Position current = position;
  turnToFacePosition(limitAngle(current.angle+M_PI_2));

}

void blueBackAuton(){
  straightPID.setMaxOutput(12000);
  straightPID.setMinOutput(-12000);
  position = {31,12.25,M_PI};
  pros::Task trackingTask(trackPosition);
  struct Position goalPos{14.75,12.8,0};
  Position current = position;
  Intake.moveVelocity(200);
  double goalHeading = calcHeadingToGoalPos(current,goalPos);
  goToPosition(goalPos);
  Intake.moveVelocity(0);
  turnToFacePosition((-3*M_PI_4));
  goToPosition(goalPos);
  bottomConveyorMotor.moveVelocity(300);
  topConveyorMotor.moveVelocity(600);
  Intake.moveVelocity(-200);
  pros::delay(750);
  Intake.moveVelocity(0);
  topConveyorMotor.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);
  goalPos = {70.5,47.8,0};
  current = position;
  straightPID.setMaxOutput(7500);
  straightPID.setMinOutput(-7500);
  goToPosition(goalPos,true);
  straightPID.setMaxOutput(12000);
  straightPID.setMinOutput(-12000);
  goalPos = {69.4,17.2,0};
  current = position;
  goalHeading = calcHeadingToGoalPos(current,goalPos);
  turnToFacePosition(goalHeading);
  goToPosition(goalPos);
  bottomConveyorMotor.moveVelocity(300);
  topConveyorMotor.moveVelocity(600);
  pros::delay(750);
  topConveyorMotor.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);

  leftFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  rightBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  rightFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  leftBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);


}

void autonSkills(){
 	Intake.moveVelocity(200);
 	bottomConveyorMotor.moveVelocity(600);
 	struct Position goalPos{34.5,24.9,0};
 	goToPosition(goalPos);
 	Intake.moveVelocity(0);
 	bottomConveyorMotor.moveVelocity(0);
 	Position current = position;
 	goalPos = {14.75,12.8,0};
 	double goalHeading = calcHeadingToGoalPos(current,goalPos);
 	turnToFacePosition(goalHeading);
 	goToPosition(goalPos);
 	bottomConveyorMotor.moveVelocity(300);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	topConveyorMotor.moveVelocity(0);
 	bottomConveyorMotor.moveVelocity(0);
 	current = position;
 	goalPos = {31.6,24.3,0};
 	goalHeading = limitAngle(calcHeadingToGoalPos(current,goalPos)+M_PI);
 	//turnToFacePosition(goalHeading);
 	straightPID.setMaxOutput(5000);
 	straightPID.setMinOutput(-5000);
 	goToPosition(goalPos,true);
 	straightPID.setMaxOutput(7500);
 	straightPID.setMinOutput(-7500);
 	goalPos = {23.5,71.9,0};
 	Intake.moveVelocity(200);
 	bottomConveyorMotor.moveVelocity(600);
 	current = position;
 	goalHeading = calcHeadingToGoalPos(current,goalPos);
 	turnToFacePosition(goalHeading);
 	goToPosition(goalPos);
 	goalPos = {16.8,71.9,0};
 	current = position;
 	goalHeading = calcHeadingToGoalPos(current,goalPos);
 	turnToFacePosition(goalHeading);
 	Intake.moveVelocity(0);
 	bottomConveyorMotor.moveVelocity(0);
 	goToPosition(goalPos);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	topConveyorMotor.moveVelocity(0);
 	current = position;
 	goalPos = {30.1,71.2,0};
 	goalHeading = limitAngle(calcHeadingToGoalPos(current,goalPos)+M_PI);
 	//turnToFacePosition(goalHeading);
 	straightPID.setMaxOutput(5000);
 	straightPID.setMinOutput(-5000);
 	goToPosition(goalPos,true);
 	straightPID.setMaxOutput(7500);
 	straightPID.setMinOutput(-7500);
 	current=position;
 	goalPos = {40.2,123.4,0};
 	goalHeading = calcHeadingToGoalPos(current, goalPos);
 	turnToFacePosition(goalHeading);
 	Intake.moveVelocity(200);
 	goToPosition(goalPos);
 	bottomConveyorMotor.moveVelocity(600);
 	Intake.moveVelocity(0);
 	current=position;
 	goalPos = {17,131.7,0};
 	goalHeading = calcHeadingToGoalPos(current, goalPos);
 	turnToFacePosition(goalHeading);
 	bottomConveyorMotor.moveVelocity(0);
 	goToPosition(goalPos);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	topConveyorMotor.moveVelocity(0);
 	current = position;
 	goalPos = {37.1,114,0};
 	goalHeading = limitAngle(calcHeadingToGoalPos(current,goalPos)+M_PI);
 	turnToFacePosition(goalHeading);
 	straightPID.setMaxOutput(5000);
 	straightPID.setMinOutput(-5000);
 	goToPosition(goalPos,true);
 	straightPID.setMaxOutput(7500);
 	straightPID.setMinOutput(-7500);
 	current = position;
 	goalPos = {75.7,114,0};
 	goalHeading = calcHeadingToGoalPos(current,goalPos);
 	turnToFacePosition(goalHeading);
 	goToPosition(goalPos);
 	current = position;
 	goalPos = {75,123.7,0};
 	goalHeading = calcHeadingToGoalPos(current,goalPos);
 	turnToFacePosition(goalHeading);
 	goToPosition(goalPos);
 	bottomConveyorMotor.moveVelocity(600);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	bottomConveyorMotor.moveVelocity(0);
 	topConveyorMotor.moveVelocity(0);
 	current = position;
 	goalPos = {75.7,114,0};
 	goalHeading = limitAngle(calcHeadingToGoalPos(current,goalPos)+M_PI);
 	turnToFacePosition(goalHeading);
 	goToPosition(goalPos,true);
 	current = position;
 	goalPos = {110.1,113.2,0};
 	goalHeading = calcHeadingToGoalPos(current,goalPos);
 	turnToFacePosition(goalHeading);
 	Intake.moveVelocity(200);
 	goToPosition(goalPos);
 	current = position;
 	goalPos = {130.2,122.7,0};
 	goalHeading = calcHeadingToGoalPos(current,goalPos);
 	bottomConveyorMotor.moveVelocity(600);
 	turnToFacePosition(goalHeading);
 	Intake.moveVelocity(0);
 	goToPosition(goalPos);
 	bottomConveyorMotor.moveVelocity(0);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	topConveyorMotor.moveVelocity(0);

 	leftFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
 	rightBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
 	rightFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
 	leftBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

}
