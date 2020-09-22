#include "drivetrain.hpp"

//calculate the sign of a number (+,-,0)
int getSign(double x){
    int sign = 0;
    if(x>0){
      sign = 1;
    }
    else if(x<0){
      sign = -1;
    }
    else{
      sign = 0;
    }
    return sign;
}

//decides which way is fastest to turn and reach goal heading. true = CC, false = C
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
double calcHeadingToGoalPos(Position curr, Position goal){

  double theta = 0;

  if((curr.x-goal.x)!=0){
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


//sets the goal position (x,y,heading), velocity, and turn direction of the robot
//note: turnDefault will just turn the robot in whichever direction is fastest to reach the goal heading
//you can set it to false if there is an obstacle that prevents you from doing so
void goToPosition(Position goalPosition, int velocityPCT, bool turnDefault = true){

  double goalVoltage = velocityPCT*12000;
  Position current = position;
  double headingToGoalPos = calcHeadingToGoalPos(current,goalPosition);
  bool turnDirection;
  int step = calcStep(goalVoltage);
  int actualVoltage = 0;
  bool notAtGoal = true;
  int signVolt = getSign(goalVoltage);


  while(abs(headingToGoalPos-current.angle)>(degreesToRadians(5))){
    current = position;

    /*
    if(signVolt == -1){
      headingToGoalPos = calcHeadingToGoalPos(current, goalPosition)+M_PI;
      if(headingToGoalPos>=(M_PI*2)){
        headingToGoalPos-=(2*M_PI);
      }
      else if(headingToGoalPos<0){
        headingToGoalPos+=2*M_PI;
      }
    }*/
    headingToGoalPos = calcHeadingToGoalPos(current, goalPosition);
    turnDirection = whichWayToTurn(current.angle, headingToGoalPos);


    if(actualVoltage!=goalVoltage){
      actualVoltage+=step;
    }


    if(turnDirection){
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
    pros::delay(20);

  }
}
