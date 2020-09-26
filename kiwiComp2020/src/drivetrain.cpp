#include "drivetrain.hpp"


std::string info;
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
  /*
  leftFrontMotor.moveAbsolute(goalDegrees,finalVelocity);
  rightFrontMotor.moveAbsolute(-goalDegrees,finalVelocity);
  leftBackMotor.moveAbsolute(goalDegrees, finalVelocity);
  rightBackMotor.moveAbsolute(-goalDegrees,finalVelocity);


  while(abs(currEnc)<abs(goalDegrees)){
    currEnc =((leftFrontMotor.getPosition()+leftBackMotor.getPosition())-(rightFrontMotor.getPosition()+rightBackMotor.getPosition()))/4.0;
    pros::delay(loopDelay);
  }*/
  master.setText(1,1,info);

}

/*//decides which way is fastest to turn and reach goal heading. true = CC, false = C
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

int calcStep(int timeToAccel){//calculates the number of steps needed based on the time spent to accelerate and the delay in the loop
  return timeToAccel/10;
}
int calcAccel(int goalVelocity){//calculates the velocity increase per step based on # of steps and goal velocity
  int accelTime = 300;
  return goalVelocity/(calcStep(accelTime));
}

//calculate the necessary heading of the robot to reach a goal position,
//based on current position and goal position
double calcHeadingToGoalPos(struct Position curr, struct Position goal){

  double theta = 0;

  if((goal.x-curr.x)!=0){
    theta = atan((goal.y-curr.y)/(goal.x-curr.x));
    int signTheta = getSign(theta);
    if(goal.y>curr.y){
      if(signTheta == -1){
        theta+=M_PI;
      }
    }
    else if(goal.y<curr.y){
      if(signTheta == 1){
        theta+=M_PI;
      }
      else if(signTheta==-1){
        theta+=(2*M_PI);
      }
    }
  }

  return theta;
}


//input goal position (x,y,heading), velocity, and turn direction of the robot
//note: turnDefault will just turn the robot in whichever direction is
//fastest to reach the goal heading, but you can set it to false
//if there is an obstacle that prevents you from doing so


//turns the robot towards a point, moves to it, and then adjusts the heading.
//can only drive forward, so far.
int goToPosition(struct Position goal,int velocityPCT, bool turnDefault){

  double goalVoltage = velocityPCT*120;
  //positionData.take(20);
  struct Position current = position;
  //positionData.give();
  double headingToGoalPos = calcHeadingToGoalPos(current,goal);
  bool turnDirection = whichWayToTurn(current.angle,headingToGoalPos);
  int step = calcStep(goalVoltage);
  int actualVoltage = 0;
  bool notAtGoal = true;
  int signVolt = getSign(goalVoltage);
  int leftVoltage;
  int rightVoltage;
  double distanceToGoalPos;
  struct Position error;
  error.angle = headingToGoalPos-current.angle;
  limitAngle(error.angle);


  //turn towards the goal position
  while(abs(error.angle)>(degreesToRadians(5))){


    if(abs(actualVoltage)<abs(goalVoltage)){
      actualVoltage= goalVoltage;
    }

    if(turnDirection){
      rightVoltage = actualVoltage;
      leftVoltage = -actualVoltage;
      leftFrontMotor.moveVoltage(leftVoltage);
      leftBackMotor.moveVoltage(leftVoltage);
      rightFrontMotor.moveVoltage(rightVoltage);
      rightBackMotor.moveVoltage(rightVoltage);
    }
    else{
      rightVoltage = -actualVoltage;
      leftVoltage = actualVoltage;
      rightFrontMotor.moveVoltage(rightVoltage);
      rightBackMotor.moveVoltage(rightVoltage);
      leftFrontMotor.moveVoltage(leftVoltage);
      leftBackMotor.moveVoltage(leftVoltage);
    }

    //positionData.take(20);
    current = position;
    //positionData.give();



        if(signVolt == -1){
          headingToGoalPos = calcHeadingToGoalPos(current, goal)+M_PI;
          if(headingToGoalPos>=(M_PI*2)){
            headingToGoalPos-=(2*M_PI);
          }
          else if(headingToGoalPos<0){
            headingToGoalPos+=2*M_PI;
          }
        }
    headingToGoalPos = calcHeadingToGoalPos(current,goal);
    turnDirection = whichWayToTurn(current.angle,headingToGoalPos);
    error.angle = headingToGoalPos-current.angle;
    limitAngle(error.angle);

    pros::delay(20);

  }

  //positionData.take(20);
  current = position;
  //positionData.give();

  error.x = goal.x-current.x;
  error.y = goal.y-current.y;


  distanceToGoalPos = sqrt((error.x*error.x)+(error.y*error.y));
  int angleAdjustment = 0;

  while(abs(error.x)>2 && abs(error.y)>2){

    angleAdjustment = 0;

    if(error.angle>(degreesToRadians(0.5))){
      angleAdjustment = radiansToDegrees(error.angle)*100;
    }


    if(abs(actualVoltage)<abs(goalVoltage)){
        actualVoltage+=step;
    }


    if(turnDirection){
      leftVoltage = actualVoltage - angleAdjustment;
      rightVoltage = actualVoltage;
    }
    else{
      leftVoltage = actualVoltage;
      rightVoltage = actualVoltage-angleAdjustment;
    }


    leftFrontMotor.moveVoltage(leftVoltage);
    leftBackMotor.moveVoltage(leftVoltage);
    rightFrontMotor.moveVoltage(rightVoltage);
    rightBackMotor.moveVoltage(rightVoltage);

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

  return 1;
}*/
