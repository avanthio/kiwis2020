#include "autons.hpp"
#include "ballmovement.hpp"
#include "drivetrain.hpp"
#include "tracking.hpp"
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
 	goToPosition(goalPos);
 	Intake.moveVelocity(0);
 	bottomConveyorMotor.moveVelocity(0);
  //Goal I
 	goalPos = {14.75,12.8,0};
 	turnToFacePosition(goalPos);
 	goToBlueBall(goalPos);
 	bottomConveyorMotor.moveVelocity(200);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(600);
 	topConveyorMotor.moveVelocity(0);
 	bottomConveyorMotor.moveVelocity(0);

 	goalPos = {31.6,24.3,0,true};
 	//turnToFacePosition(goalHeading);
 	/*straightPID.setMaxOutput(5500);
 	straightPID.setMinOutput(-5500);*/
 	goToPosition(goalPos);
 	/*straightPID.setMaxOutput(7750);
 	straightPID.setMinOutput(-7750);*/
 	goalPos = {20,72,0};
 	Intake.moveVelocity(200);
 	bottomConveyorMotor.moveVelocity(200);

 	turnToFacePosition(goalPos);
  goalPos = {25,72,0};
 	goToRedBall(goalPos);
  Intake.moveVelocity(0);
 	bottomConveyorMotor.moveVelocity(0);
  struct Position currPos = getPosition();
  //goal H
 	goalPos = {10,currPos.y,0};

 	turnToFacePosition(goalPos);
 	Intake.moveVelocity(0);
 	bottomConveyorMotor.moveVelocity(0);
  
 	goToBlueBall(goalPos);

 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	topConveyorMotor.moveVelocity(0);
  currPos = getPosition();
 	goalPos = {28,currPos.y,0,true};
 	//turnToFacePosition(goalHeading);
 
 	goToPosition(goalPos);

 	goalPos = {35,123.4,0};
 	turnToFacePosition(goalPos);
 	Intake.moveVelocity(200);
 	goToRedBall(goalPos);
 	bottomConveyorMotor.moveVelocity(300);
 	Intake.moveVelocity(0);
  //goal G
 	goalPos = {17,132.7,0};
 	turnToFacePosition(goalPos);
 	bottomConveyorMotor.moveVelocity(0);
 	goToBlueBall(goalPos);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	topConveyorMotor.moveVelocity(0);

 	goalPos = {15,123.4,0,true};
  //turnToFaceHeading(3*M_PI_4);
 	//turnToFacePositionContinuous(goalPos);
 	
 	      rightFrontMotor.moveVoltage(-4000);
        rightBackMotor.moveVoltage(-4000);
        leftFrontMotor.moveVoltage(-4000);
        leftBackMotor.moveVoltage(-4000);  
        pros::delay(500);
    rightFrontMotor.moveVoltage(0);
    leftFrontMotor.moveVoltage(0);
    rightBackMotor.moveVoltage(0);
    leftBackMotor.moveVoltage(0);
    turnToFaceHeading(3*M_PI_4);
    rightFrontMotor.moveVoltage(-4000);
    rightBackMotor.moveVoltage(-4000);
    leftFrontMotor.moveVoltage(-4000);
    leftBackMotor.moveVoltage(-4000);  
    pros::delay(1500);
    rightFrontMotor.moveVoltage(0);
    leftFrontMotor.moveVoltage(0);
    rightBackMotor.moveVoltage(0);
    leftBackMotor.moveVoltage(0);
    pros::delay(500);


 	goalPos = {71,95,0};
 	turnToFacePosition(goalPos);
  Intake.moveVelocity(200);
  bottomConveyorMotor.moveVelocity(300);
 	goToRedBall(goalPos);
  bottomConveyorMotor.moveVelocity(0);
  currPos = getPosition();
  goalPos = {currPos.x,76,0,true};
  turnToFacePosition(goalPos);
  alignToBlue(goalPos);
  Intake.moveVelocity(0);
  

  //goal D
 	goalPos = {71,124,0};
 //turnToFacePosition(goalHeading);
 	goToBlueBall(goalPos);
 	//bottomConveyorMotor.moveVelocity(600);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	//bottomConveyorMotor.moveVelocity(0);
 	topConveyorMotor.moveVelocity(0);
 	goalPos = {71,100,0,true};
 	//turnToFacePosition(goalHeading);
  alignToBlue(goalPos);
  rightFrontMotor.moveVoltage(4000);
  rightBackMotor.moveVoltage(4000);
  leftFrontMotor.moveVoltage(4000);
  leftBackMotor.moveVoltage(4000);  
  pros::delay(1500);
  rightFrontMotor.moveVoltage(0);
  leftFrontMotor.moveVoltage(0);
  rightBackMotor.moveVoltage(0);
  leftBackMotor.moveVoltage(0);
 	goalPos = {115,121,0};
  Intake.moveVelocity(200);
  bottomConveyorMotor.moveVelocity(300);
 	turnToFacePosition(goalPos);
 	goToRedBall(goalPos);

  //goal A
 	goalPos = {125,127,0};
 	//turnToFacePosition(goalPos);
  bottomConveyorMotor.moveVelocity(0);
 	Intake.moveVelocity(0);
   turnToFaceHeading(M_PI/6);
 	goToBlueBall(goalPos);
 	topConveyorMotor.moveVelocity(600);
 	pros::delay(750);
 	topConveyorMotor.moveVelocity(0);

 	      rightFrontMotor.moveVoltage(-4000);
        rightBackMotor.moveVoltage(-4000);
        leftFrontMotor.moveVoltage(-4000);
        leftBackMotor.moveVoltage(-4000);  
        pros::delay(1000);
    rightFrontMotor.moveVoltage(0);
    leftFrontMotor.moveVoltage(0);
    rightBackMotor.moveVoltage(0);
    leftBackMotor.moveVoltage(0);
    pros::delay(500);
  //goal E
  goalPos = {75,77,0};
  //Intake.moveVelocity(200);
  turnToFacePosition(goalPos);
  Intake.moveVelocity(0);
  goToBlueBallSoft(goalPos);
  bottomConveyorMotor.moveVelocity(600);
  topConveyorMotor.moveVelocity(400);
  pros::delay(750);
  goalPos = {96,90,0,true};
   rightFrontMotor.moveVoltage(-4000);
        rightBackMotor.moveVoltage(-4000);
        leftFrontMotor.moveVoltage(-4000);
        leftBackMotor.moveVoltage(-4000);  
        pros::delay(1000);
    rightFrontMotor.moveVoltage(0);
    leftFrontMotor.moveVoltage(0);
    rightBackMotor.moveVoltage(0);
    leftBackMotor.moveVoltage(0);
    pros::delay(500);
  bottomConveyorMotor.moveVelocity(0);
  topConveyorMotor.moveVelocity(0);
  goalPos = {93,68,0};
  turnToFacePosition(goalPos);
  Intake.moveVelocity(200);
  goToRedBall(goalPos);
  goalPos = {115,70,0};
  bottomConveyorMotor.moveVelocity(300);
  turnToFacePosition(goalPos);
  goalPos = {122,70,0};
  goToBlueBall(goalPos);
  Intake.moveVelocity(0);
  bottomConveyorMotor.moveVelocity(0);
  topConveyorMotor.moveVelocity(600);
  pros::delay(600);
  topConveyorMotor.moveVelocity(0);
  Intake.moveVelocity(0);
  goalPos = {110,70,0,true};
  goToPosition(goalPos);
  goalPos = {127,17,0};
  bottomConveyorMotor.moveVelocity(600);
  turnToFacePosition(goalPos);
  goToBlueBall(goalPos);
  topConveyorMotor.moveVelocity(600);






 	leftFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
 	rightBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
 	rightFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
 	leftBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

}

void testFn(){
  pros::Task trackingTask(trackPosition);
  //struct Position testPos{40,0,0};
  while(trackingStarted == false){
    pros::delay(20);
  }
  struct Position goalPos{35,47.5,0};
  alignToBlue(goalPos);

  //goToRedBall();
  /*struct Position goalPos{35,47.5,0};
 	goForDistance(goalPos);*/
  /*goalPos= {75,47,0};
  turnToFacePosition(goalPos);
  goToPosition(goalPos);
  goalPos = {75,7.5,0};
  turnToFacePosition(goalPos);
  goToPosition(goalPos);
  goalPos = {35,7.5,0};
  turnToFacePosition(goalPos);
  goToPosition(goalPos);*/

}
