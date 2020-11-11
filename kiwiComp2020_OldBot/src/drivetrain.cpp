#include "drivetrain.hpp"


//IMPORTANT NOTES FOR DRIVETRAIN CODE:
//The input for all functions related to the angle of the robot must be in radians!!!

//As a result me wanting nice PID,
//the voltage/velocity for the drivetrain motors is only controlled by PID
//with the maximum being the maximum possible voltage (12000)
//and the minimum being the minimum possible voltage (-12000)

//the PID must be reset every time it is used (reset outputs and stored values, not gains)
//The setpoint (goal for the PID) is always 0 because the input is the current error
//therefore, the setpoints are set in the PID setup function



//These are the PIDs used to control the voltage for the drivetrain motors.
//There is one for turning and one for going straight
//They are not tuned yet

KiwiPID turnPID(12000,0,1000);
KiwiPID straightPID(1,0,0);

//This function manages the PIDs at the start of the program.
//It is called in the initialize function in main.cpp
void setUpPIDs(){
  turnPID.setMaxOutput(12000);
  turnPID.setMinOutput(-12000);
  straightPID.setMaxOutput(12000);
  straightPID.setMinOutput(-12000);
  turnPID.setSetpoint(0);
  straightPID.setSetpoint(0);

  turnPID.setMinErrForI(0);
  straightPID.setMinErrForI(0);
  turnPID.setIMax(12000);
  straightPID.setIMax(12000);

}


int distanceToPoint(Position current, Position goal){
  Position error;
  error.x = goal.x-current.x;
  error.y = goal.y-current.y;

  return sqrt(error.x*error.x+error.y*error.y);
}

//decides which way is fastest to turn and reach goal heading. true = CC, false = C
//this has also been checked for all cases in Visual Studio, and works :)
bool whichWayToTurn(double currHeading, double goalHeading){
  if((currHeading<goalHeading) && ((goalHeading-currHeading)<=M_PI)){
    return true;
  }
  else if((currHeading>goalHeading) &&((currHeading-goalHeading)>M_PI)){
    return true;
  }
  else if((currHeading<goalHeading) &&((goalHeading-currHeading)>M_PI)){
    return false;
  }
  else if((currHeading>goalHeading) &&((currHeading-goalHeading)<=M_PI)){
    return false;
  }
  return false;
}


/*
//calculate the number of steps needed based on the time spent to accelerate and the delay in the loop
int calcStep(int timeToAccel){
  return timeToAccel/10;
}
int calcAccel(int goalVelocity){//calculates the velocity increase per step based on # of steps and goal velocity
  int accelTime = 300;
  return goalVelocity/(calcStep(accelTime));
}*/

//calculate the necessary heading of the robot to reach a goal position,
//based on current position and goal position
//has been checked over with testing in visual studio
//it works in all quadrants and potential situations (y 0, x+- and x 0, y+-)
double calcHeadingToGoalPos(struct Position curr, struct Position goal) {

    double theta = 0;

    if ((goal.x - curr.x) != 0) {
        theta = atan((goal.y - curr.y) / (goal.x - curr.x));
        int signTheta = getSign(theta);
        if (goal.y > curr.y) {
            if (signTheta == -1) {
                theta += M_PI;
            }
        }
        else if (goal.y < curr.y) {
            if (signTheta == 1) {
                theta += M_PI;
            }
            else if (signTheta == -1) {
                theta += (2 * M_PI);
            }
        }
        else if (goal.y == curr.y) {
            if (goal.x > curr.x) {
                theta = 0;
            }
            else {
                theta = M_PI;
            }
        }
    }
    else {
        theta = M_PI_2;
        if (goal.y < curr.y) {
            theta *= -1;
        }
    }
    theta = limitAngle(theta);
    return theta;
}



//turns the robot to face an ABSOLUTE heading. ABSOLUTE. NOT RELATIVE.
//only input things in RADIANS.
//must calculate the ABSOLUTE heading to face the point separately
//to do this, use the calcHeadingToGoalPos function.
//If you want to face away from a point,remember that the heading you want is:
// limitAngle(calcHeadingToGoalPos(whatever position the bot should go to)+M_PI)
//otherwise, you can just input an ABSOLUTE heading you want the robot to face
static lv_obj_t* labelX;

void turnToFacePosition(double headingToFacePos){
  lv_obj_clean(lv_scr_act());
  labelX = lv_label_create(lv_scr_act(),NULL);
  turnPID.reset();
  int x = 0;
  struct Position current = position;
  int actualVoltage;
  struct Position error;
  error.angle = headingToFacePos-current.angle;
  limitAngle(error.angle);
  //save the original error to decide which side of the drivetrain goes forward and which side goes backward to start out
  double originalErr = error.angle;
  std::string voltageStr;

  while(1){

    actualVoltage = turnPID.getOutput(error.angle);
    voltageStr = std::to_string(actualVoltage);
    lv_label_set_text(labelX,voltageStr.c_str());

    if(getSign(originalErr) == 1){
      leftFrontMotor.moveVoltage(-actualVoltage);
      leftBackMotor.moveVoltage(-actualVoltage);
      rightFrontMotor.moveVoltage(actualVoltage);
      rightBackMotor.moveVoltage(actualVoltage);
    }
    else{
      rightFrontMotor.moveVoltage(-actualVoltage);
      rightBackMotor.moveVoltage(-actualVoltage);
      leftFrontMotor.moveVoltage(actualVoltage);
      leftBackMotor.moveVoltage(actualVoltage);
    }

    if(error.angle<degreesToRadians(0.5)){
      x+=1;
    }
    else{
      x = 0;
    }

    /*if(x>20){
      break;
    }*/

    current = position;
    error.angle = headingToFacePos-current.angle;
    pros::delay(20);
  }

  leftFrontMotor.moveVoltage(0);
  rightFrontMotor.moveVoltage(0);
  leftBackMotor.moveVoltage(0);
  rightBackMotor.moveVoltage(0);
}


//this one doesn't have the PID added yet, and cannot go backwards. I still need to fix it
//It is supposed to drive (straight) to a point.
void goToPosition(struct Position goal, bool reversed){
  int x = 0;
  //lv_label_create(lv_scr_act(),labelTestFn);
  //std::string testString;
  int minimumVoltage = 2500;//was 2500
  struct Position current = position;
  Position startOfDrive = current;
  double headingToGoalPos = calcHeadingToGoalPos(current,goal);
  bool turnDirection = whichWayToTurn(current.angle,headingToGoalPos);
  int actualVoltage = 6000;
  bool notAtGoal = true;
  int leftVoltage;
  int rightVoltage;
  double distanceToGoalPos = distanceToPoint(current,goal);
  struct Position error;
  error.angle = headingToGoalPos-current.angle;
  limitAngle(error.angle);

  int angleAdjustment = 0;

  while(distanceToGoalPos>3){

    angleAdjustment = 0;

    if(error.angle>(degreesToRadians(0.5))){
      angleAdjustment = radiansToDegrees(error.angle)*50;
    }


    if(turnDirection){
      leftVoltage = actualVoltage - angleAdjustment;
      rightVoltage = actualVoltage;
    }
    else{
      leftVoltage = actualVoltage;
      rightVoltage = actualVoltage-angleAdjustment;
    }


    //positionData.take(20);
    current = position;
    //positionData.give();

    error.x = goal.x-current.x;
    error.y = goal.y-current.y;

    headingToGoalPos = calcHeadingToGoalPos(current, goal);
    error.angle = headingToGoalPos-current.angle;
    limitAngle(error.angle);

    turnDirection = whichWayToTurn(current.angle, headingToGoalPos);
    distanceToGoalPos = sqrt((error.x*error.x)+(error.y*error.y));

    pros::delay(20);

  }

  leftFrontMotor.moveVoltage(0);
  leftBackMotor.moveVoltage(0);
  rightFrontMotor.moveVoltage(0);
  rightBackMotor.moveVoltage(0);

}


/*std::string info;
const int loopDelay = 20;
static lv_obj_t* labelMoveForwardDebug;
static lv_obj_t* labelTurnDebug;

const double tireCircumference = 3.25*M_PI;//Never, ever, under any circumstances mess with this
double calcDriveDegrees( double targetDistanceInInches ) {//for calculating distance driving forward, not turning, in inches
    //divides goal distance by tire circumference (calculate wheel rotations needed to move a given distance)
    //then multiply by 360 to get the degrees of motor rotation
    return targetDistanceInInches / tireCircumference *360.0 ;
}
double calcWheelDistTravelled(double trackingWheelEncoderValue){
  return trackingWheelEncoderValue/360*tireCircumference;
}

int calcStep(int timeToAccel){//calculates the number of steps needed based on the time spent to accelerate and the delay in the loop
  return timeToAccel/loopDelay;
}
int calcAccel(int goalVelocity){//calculates the velocity increase per step based on # of steps and goal velocity
  int accelTime = 700;
  return goalVelocity/(calcStep(accelTime));
}

double distBetweenLandR = 8.5;

void moveForward(double goalDistance, int velocityPCT){

  //lv_obj_clean(lv_scr_act());
  labelMoveForwardDebug = lv_label_create(lv_scr_act(), NULL);

  	double goal = calcDriveDegrees(goalDistance);
  	int goalVelocity = velocityPCT*2;
    int step = calcAccel(goalVelocity);
    int initialVelocity = calcAccel(goalVelocity);
    int actualVelocity = initialVelocity;
  	double currEnc = 0;
    double endEnc = 0;
  	double currInertVal = 0;
  	double redirect = 0;
    int loopNumber = 0;
    std::string moveForwardDebugString;

  	leftTrackingWheel.reset();
    rightTrackingWheel.reset();



  	while(abs(currEnc)<abs(goal)){
  		currEnc = (leftTrackingWheel.get()+rightTrackingWheel.get())/2.0;

      if(currEnc<=(0.5*goal)&&actualVelocity<goalVelocity){
        actualVelocity+=step;
        endEnc = currEnc;
      }
      else if((currEnc)>=(goal-endEnc)&&abs(actualVelocity)>abs(initialVelocity)){
        actualVelocity-=step;
      }




  		leftFrontMotor.moveVelocity(actualVelocity);
  		rightFrontMotor.moveVelocity(actualVelocity);
  		leftBackMotor.moveVelocity(actualVelocity);
  		rightBackMotor.moveVelocity(actualVelocity);



      if(loopNumber%20){
        moveForwardDebugString = "Left TW = " + std::to_string(leftTrackingWheel.get()) + "   " + "Right TW: " + std::to_string(rightTrackingWheel.get());
        lv_label_set_text(labelMoveForwardDebug, moveForwardDebugString.c_str());
        master.setText(1, 1, std::to_string(actualVelocity));
      }
      ++loopNumber;
  		pros::delay(loopDelay);
  	}

    leftFrontMotor.moveVelocity(1);
    rightFrontMotor.moveVelocity(1);
    leftBackMotor.moveVelocity(1);
    rightBackMotor.moveVelocity(1);


    leftFrontMotor.moveVelocity(0);
    rightFrontMotor.moveVelocity(0);
    leftBackMotor.moveVelocity(0);
    rightBackMotor.moveVelocity(0);


}


//turns the robot some number of degrees. negative degrees means counterclockwise
//velocity input in pct
//increases velocity slowly in beginning and decreases at end to prevent jolting (loss of cubes)
void turnForDegrees(double degreeGoal, int turnVelocityPCT){

  lv_obj_clean(lv_scr_act());
  labelTurnDebug = lv_label_create(lv_scr_act(), NULL);

  leftTrackingWheel.reset();
  rightTrackingWheel.reset();

  int goalVelocity = turnVelocityPCT*2;
  int step = calcAccel(goalVelocity);
  int initialVelocity = calcAccel(goalVelocity);
  int actualVelocity = goalVelocity;
  int finalVelocity = 50;
	double currEnc = 0;
  int endEnc = 0;
  double rightDistTravelled = 0;
  double leftDistTravelled = 0;
  double changeInAngle = 0;
  double endAngle = 0;
  int loopNumber = 0;
  std::string turnDebugString;

  leftFrontMotor.moveVelocity(initialVelocity);
  rightFrontMotor.moveVelocity(-initialVelocity);
  leftBackMotor.moveVelocity(initialVelocity);
  rightBackMotor.moveVelocity(-initialVelocity);

  master.clear();

  while(abs(changeInAngle)<abs(degreeGoal)){
    currEnc = (leftTrackingWheel.get()-rightTrackingWheel.get())/2.0;
    rightDistTravelled = calcWheelDistTravelled(rightTrackingWheel.get());
    leftDistTravelled = calcWheelDistTravelled(leftTrackingWheel.get());
    changeInAngle = ((leftDistTravelled-rightDistTravelled)/distBetweenLandR) *180/M_PI;



      leftFrontMotor.moveVelocity(actualVelocity);
      rightFrontMotor.moveVelocity(-actualVelocity);
      leftBackMotor.moveVelocity(actualVelocity);
      rightBackMotor.moveVelocity(-actualVelocity);



    if(loopNumber%100){
      turnDebugString = "Left TW = " + std::to_string(leftTrackingWheel.get()) + "   " + "Right TW: " + std::to_string(rightTrackingWheel.get()) + "   Angle: " + std::to_string(changeInAngle);
      lv_label_set_text(labelTurnDebug, turnDebugString.c_str());
    }
    ++loopNumber;
    pros::delay(loopDelay);
  }
  leftFrontMotor.moveVelocity(1);
  rightFrontMotor.moveVelocity(1);
  leftBackMotor.moveVelocity(1);
  rightBackMotor.moveVelocity(1);

  leftFrontMotor.moveVelocity(0);
  rightFrontMotor.moveVelocity(0);
  leftBackMotor.moveVelocity(0);
  rightBackMotor.moveVelocity(0);

  leftFrontMotor.moveAbsolute(goalDegrees,finalVelocity);
  rightFrontMotor.moveAbsolute(-goalDegrees,finalVelocity);
  leftBackMotor.moveAbsolute(goalDegrees, finalVelocity);
  rightBackMotor.moveAbsolute(-goalDegrees,finalVelocity);


  while(abs(currEnc)<abs(goalDegrees)){
    currEnc =((leftFrontMotor.getPosition()+leftBackMotor.getPosition())-(rightFrontMotor.getPosition()+rightBackMotor.getPosition()))/4.0;
    pros::delay(loopDelay);
  }
  master.setText(1,1,info);

}*/
