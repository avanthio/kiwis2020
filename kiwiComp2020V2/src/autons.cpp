#include "autons.hpp"
//helloworld
void redLeftOne(){
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
  redCycleFull();
  goalPos = {30,30,0,true};

  turnToFacePosition(goalPos);
  goToPosition(goalPos);

}

void blueLeftOne(){
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
  blueCycleFull();
  goalPos = {30,30,0,true};
  
  turnToFacePosition(goalPos);
  goToPosition(goalPos);

}

void redRightOne(){

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
  redCycleFull();
  goalPos = {100,30,0,true};

  turnToFacePosition(goalPos);
  goToPosition(goalPos);

}

void blueRightOne(){
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
  blueCycleFull();
  goalPos = {100,30,0,true};

  turnToFacePosition(goalPos);
  goToPosition(goalPos);
}

void redRightTwo(){
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
  redCycleSimple();
  goalPos = {72,47.8,0,true};

  turnToFacePosition(goalPos);
  goToPosition(goalPos);
  Intake.moveVelocity(-200);
  bottomConveyorMotor.moveVelocity(-600);
  goalPos = {71,16,0};
  pros::delay(500);
  Intake.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);

  turnToFacePosition(goalPos);
  bottomConveyorMotor.moveVelocity(600);
  goToPosition(goalPos);
  topConveyorMotor.moveVelocity(600);
  pros::delay(500);
  topConveyorMotor.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);

  goalPos = {71,24,0,true};
  goToPosition(goalPos);

}

void blueRightTwo(){
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
  blueCycleSimple();
  goalPos = {72,47.8,0,true};

  turnToFacePosition(goalPos);
  goToPosition(goalPos);
  Intake.moveVelocity(-200);
  bottomConveyorMotor.moveVelocity(-600);
  goalPos = {71,16,0};
  pros::delay(500);
  Intake.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);

  turnToFacePosition(goalPos);
  bottomConveyorMotor.moveVelocity(600);
  goToPosition(goalPos);
  topConveyorMotor.moveVelocity(600);
  pros::delay(500);
  topConveyorMotor.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);

  goalPos = {71,24,0,true};
  goToPosition(goalPos);


}

void autonSkills(){

  pros::Task trackingTask(trackPosition);
  while(trackingStarted == false){
    pros::delay(20);
  }

  Intake.moveVelocity(200);
  bottomConveyorMotor.moveVelocity(200);
 	struct Position goalPos{34.75,24.9,0};
 	goToPositionContinuous(goalPos);
 	Intake.moveVelocity(0);
 	bottomConveyorMotor.moveVelocity(0);
  //Goal I
 	goalPos = {14.75,12.8,0};
 	turnToFacePositionContinuous(goalPos);
 	goToPosition(goalPos);
 	bottomConveyorMotor.moveVelocity(200);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(400);
 	topConveyorMotor.moveVelocity(0);
 	bottomConveyorMotor.moveVelocity(0);

 	goalPos = {31.6,24.3,0,true};
 	//turnToFacePosition(goalHeading);
 	/*straightPID.setMaxOutput(5500);
 	straightPID.setMinOutput(-5500);*/
 	goToPositionContinuous(goalPos);
 	/*straightPID.setMaxOutput(7750);
 	straightPID.setMinOutput(-7750);*/
 	goalPos = {23.5,71.9,0};
 	Intake.moveVelocity(200);
 	bottomConveyorMotor.moveVelocity(200);

 	turnToFacePositionContinuous(goalPos);
 	goToPositionContinuous(goalPos);
  //goal H
 	goalPos = {16,72,0};

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
  turnToFacePositionContinuous(goalPos);
 	goToPositionContinuous(goalPos);
 	/*straightPID.setMaxOutput(7750);
 	straightPID.setMinOutput(-7750);*/
 	goalPos = {36.0,123.4,0};
 	turnToFacePositionContinuous(goalPos);
 	Intake.moveVelocity(200);
 	goToPositionContinuous(goalPos);
 	bottomConveyorMotor.moveVelocity(300);
 	Intake.moveVelocity(0);
  //goal G
 	goalPos = {15,131.7,0};
 	turnToFacePositionContinuous(goalPos);
 	bottomConveyorMotor.moveVelocity(0);
 	goToPosition(goalPos);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	topConveyorMotor.moveVelocity(0);

 	goalPos = {37.1,114,0,true};
 	turnToFacePositionContinuous(goalPos);
 	/*straightPID.setMaxOutput(5500);
 	straightPID.setMinOutput(-5500);*/
 	goToPositionContinuous(goalPos);
 	/*straightPID.setMaxOutput(7750);
 	straightPID.setMinOutput(-7750);*/

 	goalPos = {70,94,0};
 	turnToFacePositionContinuous(goalPos);
  Intake.moveVelocity(200);
  bottomConveyorMotor.moveVelocity(300);
 	goToPositionContinuous(goalPos);
  Intake.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);

  goalPos = {70,80,0,true};
  turnToFacePositionContinuous(goalPos);
  goToPosition(goalPos);

  //goal D
 	goalPos = {71,121.5,0};
 //turnToFacePosition(goalHeading);
 	goToPosition(goalPos);
 	//bottomConveyorMotor.moveVelocity(600);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	//bottomConveyorMotor.moveVelocity(0);
 	topConveyorMotor.moveVelocity(0);
 	goalPos = {70,100,0,true};
 	//turnToFacePosition(goalHeading);
 	goToPositionContinuous(goalPos);

 	goalPos = {115,119,0};
  Intake.moveVelocity(200);
  bottomConveyorMotor.moveVelocity(300);
 	turnToFacePositionContinuous(goalPos);
 	goToPositionContinuous(goalPos);

  //goal A
 	goalPos = {125,125,0};
 	turnToFacePositionContinuous(goalPos);
  bottomConveyorMotor.moveVelocity(0);
 	Intake.moveVelocity(0);
 	goToPosition(goalPos);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	topConveyorMotor.moveVelocity(0);

  goalPos = {110,100,0,true};
  turnToFacePositionContinuous(goalPos);
  /*straightPID.setMaxOutput(5500);
  straightPID.setMinOutput(-5500);*/
  goToPositionContinuous(goalPos);
  /*straightPID.setMaxOutput(7750);
  straightPID.setMinOutput(-7750);*/

  //goal E
  goalPos = {75,77,0};
  Intake.moveVelocity(200);
  turnToFacePositionContinuous(goalPos);
  Intake.moveVelocity(0);
  goToPosition(goalPos);
  bottomConveyorMotor.moveVelocity(600);
  topConveyorMotor.moveVelocity(600);
  pros::delay(750);
  goalPos = {96,90,0,true};
  goToPositionContinuous(goalPos);
  bottomConveyorMotor.moveVelocity(0);
  topConveyorMotor.moveVelocity(0);
  goalPos = {93,68,0};
  turnToFacePositionContinuous(goalPos);
  Intake.moveVelocity(200);
  goToPositionContinuous(goalPos);
  goalPos = {115,70,0};
  bottomConveyorMotor.moveVelocity(300);
  turnToFacePositionContinuous(goalPos);
  goToPositionContinuous(goalPos);
  Intake.moveVelocity(0);
  goalPos = {122,70,0};
  goToPosition(goalPos);
  bottomConveyorMotor.moveVelocity(0);
  topConveyorMotor.moveVelocity(600);
  pros::delay(600);
  topConveyorMotor.moveVelocity(0);
  Intake.moveVelocity(0);
  goalPos = {110,70,0,true};
  goToPositionContinuous(goalPos);
  goalPos = {127,17,0};
  bottomConveyorMotor.moveVelocity(600);
  turnToFacePositionContinuous(goalPos);
  goToPosition(goalPos);
  topConveyorMotor.moveVelocity(600);






 	leftFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
 	rightBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
 	rightFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
 	leftBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

}

void testFn(){
  pros::Task trackingTask(trackPosition);
  while(trackingStarted == false){
    pros::delay(20);
  }
  /*struct Position goalPos;
  for(int n = 0; n<3;++n){
    goalPos = {35,57.5,0};
    goToPosition(goalPos);
    goalPos = {35,7.5,0,true};
    goToPosition(goalPos);
  }*/
  leftFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  rightBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  rightFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  leftBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
}
