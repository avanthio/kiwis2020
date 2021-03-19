#include "autons.hpp"
//helloworld
void redBackAuton(){
  positionData.take(mutexWait);
  position = {26.5,12,M_PI};
  positionData.give();

  pros::Task trackingTask(trackPosition);
  while(trackingStarted == false){
    pros::delay(20);
  }
  struct Position goalPos{19.5,12,0};
  Intake.moveVelocity(200);
  goToPosition(goalPos);
  Intake.moveVelocity(0);

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
  goalPos = {30,30,0,true};
  turnToFacePosition(goalPos);
  goToPosition(goalPos);

}

void redFrontAuton(){

  positionData.take(mutexWait);
  position = {116.5,12,0};
  positionData.give();
  pros::Task trackingTask(trackPosition);
  while(trackingStarted == false){
    pros::delay(20);
  }
  struct Position goalPos{123.5,12,0};
  Intake.moveVelocity(200);
  goToPosition(goalPos);
  Intake.moveVelocity(0);
  goalPos = {126,10,0};

  turnToFacePosition(goalPos);
  goToPosition(goalPos);
  bottomConveyorMotor.moveVelocity(600);
  topConveyorMotor.moveVelocity(600);
  Intake.moveVelocity(-200);
  pros::delay(750);
  Intake.moveVelocity(0);
  topConveyorMotor.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);
  goalPos = {100,30,0,true};

  turnToFacePosition(goalPos);
  goToPosition(goalPos);

}

void blueFrontAuton(){
  positionData.take(mutexWait);
  position = {116.5,12,0};
  positionData.give();
  pros::Task trackingTask(trackPosition);
  while(trackingStarted == false){
    pros::delay(20);
  }
  struct Position goalPos{123.5,12,0};
  Intake.moveVelocity(200);
  goToPosition(goalPos);
  Intake.moveVelocity(0);
  goalPos = {126,10,0};

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

  turnToFacePosition(goalPos);
  goToPosition(goalPos);
  goalPos = {71,17.2,0};

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

  positionData.take(mutexWait);
  position = {26.5,12,M_PI};
  positionData.give();

  pros::Task trackingTask(trackPosition);
  while(trackingStarted == false){
    pros::delay(20);
  }
  struct Position goalPos{19.5,12,0};
  Intake.moveVelocity(200);
  goToPosition(goalPos);
  Intake.moveVelocity(0);

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

  //straightPID.setMaxOutput(8000);
  //straightPID.setMinOutput(-8000);
  goToPosition(goalPos);
  //straightPID.setMaxOutput(12000);
  //straightPID.setMinOutput(-12000);
  goalPos = {69.4,17.2,0};

  turnToFacePosition(goalPos);
  goToPosition(goalPos);
  bottomConveyorMotor.moveVelocity(600);
  topConveyorMotor.moveVelocity(600);
  pros::delay(750);
  topConveyorMotor.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);
  goalPos = {70.5,60,0,true};
  //goalPos = {70.5,47.8,0};

  //straightPID.setMaxOutput(8000);
  //straightPID.setMinOutput(-8000);
  /*//straightPID.setMaxOutput(12000);
  //straightPID.setMinOutput(-12000);
  goalPos = {124.5,10,0};

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
  while(trackingStarted == false){
    pros::delay(20);
  }

  Intake.moveVelocity(200);
  bottomConveyorMotor.moveVelocity(200);
 	struct Position goalPos{34.75,24.9,0};
 	goToPosition(goalPos);
 	Intake.moveVelocity(0);
 	bottomConveyorMotor.moveVelocity(0);
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

 	turnToFacePosition(goalPos);
 	goToPosition(goalPos);
  //goal H
 	goalPos = {17,72.5,0};

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

 	goalPos = {30.1,72.5,0,true};
 	//turnToFacePosition(goalHeading);
 	/*straightPID.setMaxOutput(5500);
 	straightPID.setMinOutput(-5500);*/
 	goToPosition(goalPos);
 	/*straightPID.setMaxOutput(7750);
 	straightPID.setMinOutput(-7750);*/
 	goalPos = {38.0,123.4,0};
 	turnToFacePosition(goalPos);
 	Intake.moveVelocity(200);
 	goToPosition(goalPos);
 	bottomConveyorMotor.moveVelocity(600);
 	Intake.moveVelocity(0);
  //goal G
 	goalPos = {17,131.7,0};
 	turnToFacePosition(goalPos);
 	bottomConveyorMotor.moveVelocity(0);
 	goToPosition(goalPos);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	topConveyorMotor.moveVelocity(0);

 	goalPos = {37.1,114,0,true};
 	turnToFacePosition(goalPos);
 	/*straightPID.setMaxOutput(5500);
 	straightPID.setMinOutput(-5500);*/
 	goToPosition(goalPos);
 	/*straightPID.setMaxOutput(7750);
 	straightPID.setMinOutput(-7750);*/

 	goalPos = {71,92,0};
 	turnToFacePosition(goalPos);
  Intake.moveVelocity(200);
  bottomConveyorMotor.moveVelocity(600);
 	goToPosition(goalPos);
  Intake.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);

  goalPos = {71,80,0,true};
  turnToFacePosition(goalPos);
  goToPosition(goalPos);

  //goal D
 	goalPos = {71,124,0};
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

 	goalPos = {109,117,0};
 	turnToFacePosition(goalPos);
 	Intake.moveVelocity(200);
 	goToPosition(goalPos);

  //goal A
 	goalPos = {130.5,130,0};
 	bottomConveyorMotor.moveVelocity(600);
 	turnToFacePosition(goalPos);
 	Intake.moveVelocity(0);
 	goToPosition(goalPos);
 	bottomConveyorMotor.moveVelocity(0);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	topConveyorMotor.moveVelocity(0);
  //goal E?

  goalPos = {110,100,0,true};
  turnToFacePosition(goalPos);
  /*straightPID.setMaxOutput(5500);
  straightPID.setMinOutput(-5500);*/
  goToPosition(goalPos);
  /*straightPID.setMaxOutput(7750);
  straightPID.setMinOutput(-7750);*/

  goalPos = {76,78.0,0};
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
  topConveyorMotor.moveVelocity(600);
  pros::delay(600);
  topConveyorMotor.moveVelocity(0);
  Intake.moveVelocity(0);
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

void testFn(){
  pros::delay(1000);
}