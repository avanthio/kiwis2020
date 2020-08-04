#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

 constexpr int loopDelayMsec = 20;
 constexpr double wheelCircumference = 4.0*M_PI;//Never, ever, under any circumstances mess with this
 double calcDriveDegreesWheel( double targetDistanceInInches ) {
   //for calculating distance driving forward, not turning, in inches
     //divides goal distance by tire circumference
     //(calculate wheel rotations needed to move a given distance)
     //then multiply by 360 to get the degrees of motor rotation
     return targetDistanceInInches / wheelCircumference * 240.0 ;
 }
 double calcDriveDegreesTrackingWheel( double targetDistanceInInches ) {
   //for calculating distance driving forward, not turning, in inches
     //divides goal distance by tire circumference
     //(calculate wheel rotations needed to move a given distance)
     //then multiply by 360 to get the degrees of motor rotation
     return targetDistanceInInches / trackingWheelCircumference * 360.0 ;
 }
 int calcStep(int timeToAccelMsec){
   //calculates the number of loops you go through to accelerate
   // based on the time spent to accelerate (in msec)
   // and the delay in the loop (in msec)
   return timeToAccelMsec/loopDelayMsec;
 }
 int calcAccel(int goalVelocity){
   //calculates the velocity increase per step based on # of steps and goal velocity
   const int accelTimeMsec = 700;
   return goalVelocity/(calcStep(accelTimeMsec));
 }

 void moveForwardTrackingWheel(double goalDistanceInches, int maxVelocityPCT){

   	double goalDegrees = calcDriveDegreesTrackingWheel(goalDistanceInches);
   	int maxVelocity = maxVelocityPCT*2;
    int step = calcAccel(maxVelocity);
    int initialVelocity = calcAccel(maxVelocity);
    int actualVelocity = maxVelocity;
		double currEncDegrees = 0;

   	leftFrontMotor.tarePosition();
   	rightFrontMotor.tarePosition();
   	leftBackMotor.tarePosition();
   	rightBackMotor.tarePosition();
		rightTrackingWheel.reset();

   	while(abs(currEncDegrees)<abs(goalDegrees)){
   		currEncDegrees = rightTrackingWheel.get();

   		leftFrontMotor.moveVelocity(actualVelocity);
   		rightFrontMotor.moveVelocity(actualVelocity);
   		leftBackMotor.moveVelocity(actualVelocity);
   		rightBackMotor.moveVelocity(actualVelocity);

			std::string as = std::to_string(currEncDegrees);
			master.setText(1,2,as);

   		pros::delay(loopDelayMsec);
   	}


     leftFrontMotor.moveVelocity(0);
     rightFrontMotor.moveVelocity(0);
     leftBackMotor.moveVelocity(0);
     rightBackMotor.moveVelocity(0);


 }

void initialize() {
	pros::delay(100);
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
void opcontrol() {

	int x = 0;
  int y = 0;
	int axis1 = 0;
	int axis3 = 0;
	int axis4 = 0;
	bool speedy = false;
	int speedyScale = 200;
	int slowScale = 134;
	int scale = slowScale;
  int loopCount = 0;

	while(true){

		if (turboBtn.changedToPressed()){
			speedy = !speedy;
		}

		if(speedy==true){
			scale = speedyScale;
			master.setText(2,1,"speedy.");
		}
		else{
			scale = slowScale;
			master.setText(2,1,"!speedy");
		}

		axis1 = master.getAnalog(okapi::ControllerAnalog::rightX)*200;
		axis3 = master.getAnalog(okapi::ControllerAnalog::leftY)*scale;
		axis4 = master.getAnalog(okapi::ControllerAnalog::leftX)*scale;

		int leftFrontSpeed = axis3 + axis4;
		int leftBackSpeed = axis3 + axis4;
		int rightFrontSpeed = axis3 - axis4;
		int rightBackSpeed = axis3 - axis4;
		int hSpeed = axis1;

		leftFrontMotor.moveVelocity(leftFrontSpeed);
		leftBackMotor.moveVelocity(leftBackSpeed);
		rightFrontMotor.moveVelocity(rightFrontSpeed);
		rightBackMotor.moveVelocity(rightBackSpeed);
		hMotor.moveVelocity(hSpeed);


		if(intakeInBtn.isPressed()){
			x=1;
		}
		else if(intakeStopBtn.isPressed()){
			x=0;
		}

		switch(x){
      case 1:
        Intake.moveVelocity(200);
        break;
      case 0:
        Intake.moveVelocity(0);
        break;
    }

    if(conveyorStartBtn.isPressed()){
			y=1;
		}
		else if(conveyorStopBtn.isPressed()){
			y=0;
		}

		switch(y){
      case 1:
        conveyorMotor.moveVelocity(200);
        break;
      case 0:
        conveyorMotor.moveVelocity(0);
        break;
    }

	   pros::delay(20);
	}
}
