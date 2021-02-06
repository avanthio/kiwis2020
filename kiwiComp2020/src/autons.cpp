#include "autons.hpp"

void redFrontAuton(){


}

void redBackAuton(){

}

void blueFrontAuton(){

  /*straightPID.setMaxOutput(6000);
  straightPID.setMinOutput(-6000);
  position = {116,13,0};
  pros::Task trackingTask(trackPosition);
  pros::delay(100);
  struct Position goalPos{122,13,0};
  Position current = position;
  Intake.moveVelocity(100);
  double goalHeading = calcHeadingToGoalPos(current,goalPos);
  goToPosition(goalPos);
  Intake.moveVelocity(0);
  turnToFacePosition((-1*M_PI/6));
  goalPos = {123,10,0};
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
  straightPID.setMaxOutput(6000);
  straightPID.setMinOutput(-6000);
  goToPosition(goalPos);
  straightPID.setMaxOutput(9000);
  straightPID.setMinOutput(-9000);
  goalPos = {69.4,17.2,0};
  current = position;
  goalHeading = calcHeadingToGoalPos(current,goalPos);
  turnToFacePosition(goalHeading);
  goToPosition(goalPos);
  bottomConveyorMotor.moveVelocity(300);
  topConveyorMotor.moveVelocity(600);
  pros::delay(750);
  topConveyorMotor.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);*/

}

void blueBackAuton(){
  straightPID.setMaxOutput(10000);
  straightPID.setMinOutput(-10000);
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
  straightPID.setMaxOutput(8000);
  straightPID.setMinOutput(-8000);
  goToPosition(goalPos);
  straightPID.setMaxOutput(12000);
  straightPID.setMinOutput(-12000);
  goalPos = {69.4,17.2,0};
  current = position;
  turnToFacePosition(goalPos);
  goToPosition(goalPos);
  bottomConveyorMotor.moveVelocity(600);
  topConveyorMotor.moveVelocity(600);
  pros::delay(750);
  topConveyorMotor.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);
  goalPos = {70.5,47.8,0,true};
  current = position;
  straightPID.setMaxOutput(8000);
  straightPID.setMinOutput(-8000);
  goToPosition(goalPos);
  straightPID.setMaxOutput(12000);
  straightPID.setMinOutput(-12000);
  goalPos = {124.5,10,0};
  current = position;
  turnToFacePosition(goalPos);
  Intake.moveVelocity(100);
  goToPosition(goalPos);
  topConveyorMotor.moveVelocity(600);
  bottomConveyorMotor.moveVelocity(600);
  Intake.moveVelocity(0);


}

void autonSkills(){

  pros::Task trackingTask(trackPosition);
  pros::delay(100);

  /*struct Position current;
  double goalHeading;
  for(int q = 0; q<4;++q){
    current = position;
    goalHeading = limitAngle(current.angle+M_PI_2);
    turnToFacePosition(goalHeading);
  }*/

 	Intake.moveVelocity(200);
 	bottomConveyorMotor.moveVelocity(600);
 	struct Position goalPos{34.5,24.9,0};
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
 	goalPos = {31.6,24.3,0, true};
 	//turnToFacePosition(goalHeading);
 	straightPID.setMaxOutput(5500);
 	straightPID.setMinOutput(-5500);
 	goToPosition(goalPos);
 	straightPID.setMaxOutput(7750);
 	straightPID.setMinOutput(-7750);
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
  straightPID.setMaxOutput(5500);
 	straightPID.setMinOutput(-5500);
 	goToPosition(goalPos);
 	straightPID.setMaxOutput(7750);
 	straightPID.setMinOutput(-7750);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	topConveyorMotor.moveVelocity(0);
  current = position;
 	goalPos = {30.1,71.9,0,true};
 	//turnToFacePosition(goalHeading);
 	straightPID.setMaxOutput(5500);
 	straightPID.setMinOutput(-5500);
 	goToPosition(goalPos);
 	straightPID.setMaxOutput(7750);
 	straightPID.setMinOutput(-7750);
 	current=position;
 	goalPos = {40.2,123.4,0};
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
 	straightPID.setMaxOutput(5500);
 	straightPID.setMinOutput(-5500);
 	goToPosition(goalPos);
 	straightPID.setMaxOutput(7750);
 	straightPID.setMinOutput(-7750);
 	current = position;
 	goalPos = {75.7,84,0};
 	turnToFacePosition(goalPos);
  Intake.moveVelocity(200);
  bottomConveyorMotor.moveVelocity(600);
 	goToPosition(goalPos);
  Intake.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);
  current = position;
  goalPos = {73.5,79,0,true};
  turnToFacePosition(goalPos);
  goToPosition(goalPos);
  current = position;
  //goal D
 	goalPos = {75,122,0};
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
 	goalPos = {110.1,109,0};
 	turnToFacePosition(goalPos);
 	Intake.moveVelocity(200);
 	goToPosition(goalPos);
 	current = position;
  //goal A
 	goalPos = {130.5,118,0};
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
  straightPID.setMaxOutput(5500);
  straightPID.setMinOutput(-5500);
  goToPosition(goalPos);
  straightPID.setMaxOutput(7750);
  straightPID.setMinOutput(-7750);
  current = position;
  goalPos = {76.5,75.5,0};
  turnToFacePosition(goalPos);
  goToPosition(goalPos);
  bottomConveyorMotor.moveVelocity(600);
  topConveyorMotor.moveVelocity(600);


 	leftFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
 	rightBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
 	rightFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
 	leftBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

}
