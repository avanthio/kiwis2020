#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */



void initialize() {
	pros::delay(100);
	debugType();
	if(buttons){
		create_buttons();
	}
	setUpPIDs();
  setBrakeTypes();
  resetDevices();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	if(buttons){
  	selectionResult();
	}
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */


void autonomous() {

	blueBackAuton();
	/*if(buttons){
		runChosenAuton();
	}*/
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 *  If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void testFunct(){
	leftFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
	rightBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
	rightFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
	leftBackMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
}
void opcontrol() {

	int x = 0;
  int y = 0;
  int leftFrontSpeed = 0;
  int rightFrontSpeed = 0;
  int rightBackSpeed = 0;
  int leftBackSpeed = 0;
  int axis4 = 0;
	int axis2 = 0;
	int axis3 = 0;
  bool driveSam = true;
  int loopCount = 0;

	while(true){



    if (driveSwitchBtn.changedToPressed()){
			driveSam = !driveSam;
		}

    if(driveSam){
			axis3 = master.getAnalog(okapi::ControllerAnalog::leftY)*12000;
			axis2 = master.getAnalog(okapi::ControllerAnalog::rightY)*12000;

		  leftFrontSpeed = axis3;
      leftBackSpeed = axis3;
      rightFrontSpeed = axis2;
      rightBackSpeed = axis2;
			master.setText(1,1,"tank drive  ");
    }
    else{
      axis3 = master.getAnalog(okapi::ControllerAnalog::leftY)*12000;
  		axis4 = master.getAnalog(okapi::ControllerAnalog::leftX)*12000;

      leftFrontSpeed = axis3+axis4;
      leftBackSpeed = axis3+axis4;
      rightFrontSpeed = axis3-axis4;
      rightBackSpeed = axis3-axis4;
		  master.setText(1,1,"arcade drive");

    }

		leftFrontMotor.moveVoltage(leftFrontSpeed);
		leftBackMotor.moveVoltage(leftBackSpeed);
		rightFrontMotor.moveVoltage(rightFrontSpeed);
		rightBackMotor.moveVoltage(rightBackSpeed);


		if(intakeInBtn.isPressed()){
			x=1;
		}
		else if(intakeStopBtn.isPressed()){
			x=0;
		}
    else if(intakeReverseBtn.isPressed()){
      x=-1;
    }

    switch(x){
      case 1:
        Intake.moveVelocity(200);
        break;
      case 0:
        Intake.moveVelocity(0);
        break;
      case -1:
        Intake.moveVelocity(-200);
    }

    if(conveyorTopBtn.isPressed()){
			topConveyorMotor.moveVelocity(600);
		}
		else if(conveyorTopReverseBtn.isPressed()){
			topConveyorMotor.moveVelocity(-400);
		}
		else{
			topConveyorMotor.moveVelocity(0);
		}

		if(conveyorBottomBtn.isPressed()){
			bottomConveyorMotor.moveVelocity(600);
		}
		else if(conveyorBottomReverseBtn.isPressed()){
			bottomConveyorMotor.moveVelocity(-600);
		}
		else{
			bottomConveyorMotor.moveVelocity(0);
		}



	   pros::delay(20);
	}
}
