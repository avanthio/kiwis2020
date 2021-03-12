#include "autons.hpp"
//helloworld
void redFrontAuton(){
  leftFrontMotor.moveVelocity(200);
  rightFrontMotor.moveVelocity(200);
  rightBackMotor.moveVelocity(200);
  leftBackMotor.moveVelocity(200);
  pros::delay(750);
  leftFrontMotor.moveVelocity(0);
  rightFrontMotor.moveVelocity(0);
  rightBackMotor.moveVelocity(0);
  leftBackMotor.moveVelocity(0);
  topConveyorMotor.moveVelocity(600);
  bottomConveyorMotor.moveVelocity(600);
}

void redBackAuton(){

  pros::Task trackingTask(trackPosition);
  pros::delay(100);

  Intake.moveVelocity(200);
  bottomConveyorMotor.moveVelocity(200);
 	struct Position goalPos{34.75,24.9,0};
 	goToPositionContinuous(goalPos);
 	Intake.moveVelocity(0);
 	bottomConveyorMotor.moveVelocity(0);
 	Position current = position;
  //Goal I
 	goalPos = {14.75,12.8,0};
 	turnToFacePositionContinuous(goalPos);
 	goToPosition(goalPos);
 	bottomConveyorMotor.moveVelocity(300);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(500);
  bottomConveyorMotor.moveVelocity(0);
  pros::delay(250);
 	topConveyorMotor.moveVelocity(0);
 	bottomConveyorMotor.moveVelocity(0);
 	current = position;
 	goalPos = {31.6,24.3,0,true};
 	//turnToFacePosition(goalHeading);
 	/*straightPID.setMaxOutput(5500);
 	straightPID.setMinOutput(-5500);*/
 	goToPosition(goalPos);
 	/*straightPID.setMaxOutput(7750);
 	straightPID.setMinOutput(-7750);*/
 	goalPos = {23.5,71.9,0};
 	Intake.moveVelocity(200);
 	bottomConveyorMotor.moveVelocity(600);
 	current = position;
 	turnToFacePositionContinuous(goalPos);
 	goToPosition(goalPos);
  //goal H
 	goalPos = {17,72.5,0};
 	current = position;
 	turnToFacePosition(goalPos);
 	Intake.moveVelocity(0);
 	bottomConveyorMotor.moveVelocity(0);
  /*straightPID.setMaxOutput(5500);
 	straightPID.setMinOutput(-5500);*/
 	goToPosition(goalPos);
 	/*straightPID.setMaxOutput(7750);
 	straightPID.setMinOutput(-7750);*/
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	topConveyorMotor.moveVelocity(0);
  current = position;
 	goalPos = {30.1,71.9,0,true};
 	//turnToFacePosition(goalHeading);
 	/*straightPID.setMaxOutput(5500);
 	straightPID.setMinOutput(-5500);*/
 	goToPosition(goalPos);
 	/*straightPID.setMaxOutput(7750);
 	straightPID.setMinOutput(-7750);*/
 	current=position;
 	goalPos = {38.0,123.4,0};
 	turnToFacePositionContinuous(goalPos);
 	Intake.moveVelocity(200);
 	goToPositionContinuous(goalPos);
 	bottomConveyorMotor.moveVelocity(600);
 	Intake.moveVelocity(0);
 	current=position;
  //goal G
 	goalPos = {17,131.7,0};
 	turnToFacePositionContinuous(goalPos);
 	bottomConveyorMotor.moveVelocity(0);
 	goToPosition(goalPos);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	topConveyorMotor.moveVelocity(0);
 	current = position;
 	goalPos = {37.1,114,0,true};
 	turnToFacePositionContinuous(goalPos);
 	/*straightPID.setMaxOutput(5500);
 	straightPID.setMinOutput(-5500);*/
 	goToPositionContinuous(goalPos);
 	/*straightPID.setMaxOutput(7750);
 	straightPID.setMinOutput(-7750);*/
 	current = position;
 	goalPos = {75.7,92,0};
 	turnToFacePositionContinuous(goalPos);
  Intake.moveVelocity(200);
  bottomConveyorMotor.moveVelocity(600);
 	goToPositionContinuous(goalPos);
  Intake.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);
  current = position;
  goalPos = {74,79,0,true};
  turnToFacePositionContinuous(goalPos);
  goToPositionContinuous(goalPos);
  current = position;
  //goal D
 	goalPos = {74,122,0};
 //turnToFacePosition(goalHeading);
 	goToPosition(goalPos);
 	//bottomConveyorMotor.moveVelocity(600);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	//bottomConveyorMotor.moveVelocity(0);
 	topConveyorMotor.moveVelocity(0);
 	goalPos = {75.7,100,0,true};
 	//turnToFacePosition(goalHeading);
 	goToPositionContinuous(goalPos);
 	current = position;
 	goalPos = {110.1,113,0};
 	turnToFacePositionContinuous(goalPos);
 	Intake.moveVelocity(200);
 	goToPositionContinuous(goalPos);
 	current = position;
  //goal A
 	goalPos = {130.5,124,0};
 	bottomConveyorMotor.moveVelocity(600);
 	turnToFacePositionContinuous(goalPos);
 	Intake.moveVelocity(0);
 	goToPosition(goalPos);
 	bottomConveyorMotor.moveVelocity(0);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	topConveyorMotor.moveVelocity(0);
  //goal E?
  current = position;
  goalPos = {110,100,0,true};
  turnToFacePosition(goalPos);
  /*straightPID.setMaxOutput(5500);
  straightPID.setMinOutput(-5500);*/
  goToPosition(goalPos);
  /*straightPID.setMaxOutput(7750);
  straightPID.setMinOutput(-7750);*/
  current = position;
  goalPos = {78,77.0,0};
  turnToFacePosition(goalPos);
  goToPosition(goalPos);
  bottomConveyorMotor.moveVelocity(600);
  topConveyorMotor.moveVelocity(600);
  pros::delay(1000);
  goalPos = {96,90,0,true};
  goToPosition(goalPos);
  bottomConveyorMotor.moveVelocity(0);
  topConveyorMotor.moveVelocity(0);
  goalPos = {93,65,0};
  turnToFacePosition(goalPos);
  Intake.moveVelocity(200);
  goToPosition(goalPos);
  goalPos = {115,65,0};
  turnToFacePosition(goalPos);
  bottomConveyorMotor.moveVelocity(500);
  goToPosition(goalPos);
  Intake.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);
  goalPos = {125,65,0};
  goToPosition(goalPos);
  topConveyorMotor.moveVelocity(600);
  pros::delay(750);
  topConveyorMotor.moveVelocity(0);
  goalPos = {110,65,0,true};
  goToPosition(goalPos);
  goalPos = {122,0,0};
  turnToFacePosition(goalPos);
  goToPosition(goalPos);

}

void blueFrontAuton(){

  position = {118.5,12,0};
  pros::Task trackingTask(trackPosition);
  pros::delay(100);
  struct Position goalPos{123.5,12,0};
  Position current = position;
  Intake.moveVelocity(200);
  goToPosition(goalPos);
  Intake.moveVelocity(0);
  goalPos = {126,10,0};
  current = position;
  turnToFacePosition(goalPos);
  goToPosition(goalPos);
  bottomConveyorMotor.moveVelocity(600);
  topConveyorMotor.moveVelocity(600);
  Intake.moveVelocity(-200);
  pros::delay(750);
  Intake.moveVelocity(0);
  topConveyorMotor.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);
  goalPos = {72,47.8,0,true};
  current = position;
  turnToFacePosition(goalPos);
  goToPosition(goalPos);
  goalPos = {71,17.2,0};
  current = position;
  turnToFacePosition(goalPos);
  goToPosition(goalPos);
  bottomConveyorMotor.moveVelocity(600);
  topConveyorMotor.moveVelocity(600);
  pros::delay(750);
  topConveyorMotor.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);

}

void blueBackAuton(){
  /*straightPID.setMaxOutput(10000);
  straightPID.setMinOutput(-10000);*/

  position = {24.5,12,M_PI};
  pros::Task trackingTask(trackPosition);
  pros::delay(100);
  struct Position goalPos{19.5,12,0};
  Position current = position;
  Intake.moveVelocity(200);
  goToPosition(goalPos);
  Intake.moveVelocity(0);
  current = position;
  goalPos = {16.5,10,0};
  turnToFacePosition(goalPos);
  goToPosition(goalPos);
  bottomConveyorMotor.moveVelocity(300);
  topConveyorMotor.moveVelocity(600);
  Intake.moveVelocity(-200);
  pros::delay(750);
  Intake.moveVelocity(0);
  topConveyorMotor.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);
  goalPos = {70.5,47.8,0,true};
  current = position;
  //straightPID.setMaxOutput(8000);
  //straightPID.setMinOutput(-8000);
  goToPosition(goalPos);
  //straightPID.setMaxOutput(12000);
  //straightPID.setMinOutput(-12000);
  goalPos = {69.4,17.2,0};
  current = position;
  turnToFacePosition(goalPos);
  goToPosition(goalPos);
  bottomConveyorMotor.moveVelocity(600);
  topConveyorMotor.moveVelocity(600);
  pros::delay(750);
  topConveyorMotor.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);
  goalPos = {70.5,60,0,true};
  //goalPos = {70.5,47.8,0};
  current = position;
  //straightPID.setMaxOutput(8000);
  //straightPID.setMinOutput(-8000);
  goToPosition(goalPos);
  /*//straightPID.setMaxOutput(12000);
  //straightPID.setMinOutput(-12000);
  goalPos = {124.5,10,0};
  current = position;
  goalHeading = calcHeadingToGoalPos(current, goalPos);
  turnToFacePosition(goalHeading);
  Intake.moveVelocity(100);
  goToPosition(goalPos);
  topConveyorMotor.moveVelocity(600);
  bottomConveyorMotor.moveVelocity(600);
  Intake.moveVelocity(0);*/


}

void autonSkills(){

  pros::Task trackingTask(trackPosition);
  pros::delay(100);

  Intake.moveVelocity(200);
  bottomConveyorMotor.moveVelocity(200);
 	struct Position goalPos{34.75,24.9,0};
 	goToPosition(goalPos);
 	Intake.moveVelocity(0);
 	bottomConveyorMotor.moveVelocity(0);
 	Position current = position;
  //Goal I
 	goalPos = {14.75,12.8,0};
 	turnToFacePosition(goalPos);
 	goToPosition(goalPos);
 	bottomConveyorMotor.moveVelocity(300);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(500);
  bottomConveyorMotor.moveVelocity(0);
  pros::delay(250);
 	topConveyorMotor.moveVelocity(0);
 	bottomConveyorMotor.moveVelocity(0);
 	current = position;
 	goalPos = {31.6,24.3,0,true};
 	//turnToFacePosition(goalHeading);
 	/*straightPID.setMaxOutput(5500);
 	straightPID.setMinOutput(-5500);*/
 	goToPosition(goalPos);
 	/*straightPID.setMaxOutput(7750);
 	straightPID.setMinOutput(-7750);*/
 	goalPos = {23.5,71.9,0};
 	Intake.moveVelocity(200);
 	bottomConveyorMotor.moveVelocity(600);
 	current = position;
 	turnToFacePosition(goalPos);
 	goToPosition(goalPos);
  //goal H
 	goalPos = {17,72.5,0};
 	current = position;
 	turnToFacePosition(goalPos);
 	Intake.moveVelocity(0);
 	bottomConveyorMotor.moveVelocity(0);
  /*straightPID.setMaxOutput(5500);
 	straightPID.setMinOutput(-5500);*/
 	goToPosition(goalPos);
 	/*straightPID.setMaxOutput(7750);
 	straightPID.setMinOutput(-7750);*/
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	topConveyorMotor.moveVelocity(0);
  current = position;
 	goalPos = {30.1,71.9,0,true};
 	//turnToFacePosition(goalHeading);
 	/*straightPID.setMaxOutput(5500);
 	straightPID.setMinOutput(-5500);*/
 	goToPosition(goalPos);
 	/*straightPID.setMaxOutput(7750);
 	straightPID.setMinOutput(-7750);*/
 	current=position;
 	goalPos = {38.0,123.4,0};
 	turnToFacePosition(goalPos);
 	Intake.moveVelocity(200);
 	goToPosition(goalPos);
 	bottomConveyorMotor.moveVelocity(600);
 	Intake.moveVelocity(0);
 	current=position;
  //goal G
 	goalPos = {17,131.7,0};
 	turnToFacePosition(goalPos);
 	bottomConveyorMotor.moveVelocity(0);
 	goToPosition(goalPos);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	topConveyorMotor.moveVelocity(0);
 	current = position;
 	goalPos = {37.1,114,0,true};
 	turnToFacePosition(goalPos);
 	/*straightPID.setMaxOutput(5500);
 	straightPID.setMinOutput(-5500);*/
 	goToPosition(goalPos);
 	/*straightPID.setMaxOutput(7750);
 	straightPID.setMinOutput(-7750);*/
 	current = position;
 	goalPos = {74,92,0};
 	turnToFacePosition(goalPos);
  Intake.moveVelocity(200);
  bottomConveyorMotor.moveVelocity(600);
 	goToPosition(goalPos);
  Intake.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);
  current = position;
  goalPos = {74,79,0,true};
  turnToFacePosition(goalPos);
  goToPosition(goalPos);
  current = position;
  //goal D
 	goalPos = {74,122,0};
 //turnToFacePosition(goalHeading);
 	goToPosition(goalPos);
 	//bottomConveyorMotor.moveVelocity(600);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	//bottomConveyorMotor.moveVelocity(0);
 	topConveyorMotor.moveVelocity(0);
 	goalPos = {75.7,100,0,true};
 	//turnToFacePosition(goalHeading);
 	goToPosition(goalPos);
 	current = position;
 	goalPos = {110.1,113,0};
 	turnToFacePosition(goalPos);
 	Intake.moveVelocity(200);
 	goToPosition(goalPos);
 	current = position;
  //goal A
 	goalPos = {130.5,124,0};
 	bottomConveyorMotor.moveVelocity(600);
 	turnToFacePosition(goalPos);
 	Intake.moveVelocity(0);
 	goToPosition(goalPos);
 	bottomConveyorMotor.moveVelocity(0);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	topConveyorMotor.moveVelocity(0);
  //goal E?
  current = position;
  goalPos = {110,100,0,true};
  turnToFacePosition(goalPos);
  /*straightPID.setMaxOutput(5500);
  straightPID.setMinOutput(-5500);*/
  goToPosition(goalPos);
  /*straightPID.setMaxOutput(7750);
  straightPID.setMinOutput(-7750);*/
  current = position;
  goalPos = {78,77.0,0};
  turnToFacePosition(goalPos);
  goToPosition(goalPos);
  bottomConveyorMotor.moveVelocity(600);
  topConveyorMotor.moveVelocity(600);
  pros::delay(750);
  goalPos = {96,90,0,true};
  goToPosition(goalPos);
  bottomConveyorMotor.moveVelocity(0);
  topConveyorMotor.moveVelocity(0);
  goalPos = {93,65,0};
  turnToFacePosition(goalPos);
  Intake.moveVelocity(200);
  goToPosition(goalPos);
  goalPos = {125,65,0};
  bottomConveyorMotor.moveVelocity(500);
  turnToFacePosition(goalPos);
  bottomConveyorMotor.moveVelocity(0);
  goToPosition(goalPos);
  Intake.moveVelocity(0);
  topConveyorMotor.moveVelocity(600);
  pros::delay(600);
  topConveyorMotor.moveVelocity(0);
  goalPos = {110,65,0,true};
  goToPosition(goalPos);
  goalPos = {121,13,0};
  bottomConveyorMotor.moveVelocity(600);
  turnToFacePosition(goalPos);
  goToPosition(goalPos);
  topConveyorMotor.moveVelocity(600);






 	leftFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
 	rightBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
 	rightFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
 	leftBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

}
