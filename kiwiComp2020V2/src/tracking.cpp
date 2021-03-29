#include "tracking.hpp"


pros::Mutex positionData;
int mutexWait = 50;
bool trackingStarted = false;

//The wall behind the robot is where 0,0 is
//PI/2 radians (90 deg) is where the robot is perpendicular to the wall
//The range for the angle of the robot is -pi, pi.
std::string trackDebugStr;
struct Position position{35,7.5,M_PI_2};
//distance from each tracking wheel to tracking center/center of robot
constexpr double offsetLeft = 7.54/2;
constexpr double offsetRight = 7.54/2;
constexpr double offsetBack = 5;
//distance between left and right wheels
constexpr double distBetweenLandR = 7.54;

//last encoder value for each wheel
double lastLeftEncVal = 0;
double lastRightEncVal = 0;
double lastBackEncVal = 0;
int loopNumber;
static lv_obj_t* labelTrackingDebug;
std::string trackingDebugString;
std::string encoderDebugStr;
double robotAngleInDegrees;
//a boolean that decides whether the the robot should be tracking its position or not
bool tracking = true;

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

//calculate the distance the tracking wheel has travelled, in inches
double calcTrackingWheelDistTravelled(double trackingWheelEncoderValue){
  return trackingWheelEncoderValue/360*trackingWheelCircumference;
}

//convert an angle measure in degrees to radians
double degreesToRadians(double inputInDegrees){
  return inputInDegrees*M_PI/180;
}

//convert an angle measuer in radians to degrees
double radiansToDegrees(double inputInRadians){
  return inputInRadians*180/M_PI;
}

//keep angle between -PI and PI.
double limitAngle(double angle) {
    while (angle > M_PI || angle <= -M_PI) {
        while (angle > M_PI) {
            angle -= 2 * M_PI;
        }
        while (angle < -M_PI) {
            angle += 2 * M_PI;
        }
    }
    return angle;
}

void setStartPoint(Position startPoint){
  positionData.take(mutexWait);
  position.x = startPoint.x;
  position.y = startPoint.y;
  position.angle = startPoint.angle;
  positionData.give();
}

//track the position of the robot using tracking wheel encoder values and math
void trackPosition(){
  if(trackingDebug){
    lv_obj_clean(lv_scr_act());
    labelTrackingDebug = lv_label_create(lv_scr_act(), NULL);
  }

  //printf("Zero %d;%d;%d\n", leftTrackingWheel.get(),rightTrackingWheel.get(),backTrackingWheel.get());

  double currLeftEncVal;
  double currRightEncVal;
  double currBackEncVal;
  double totalAngle;
  double changeInY;
  double distTravelled;
  double changeInX;
  double changeInAngle;
  double distTravelledBackWheel;
  double backDistTravelled;
  double leftDistTravelled;
  double rightDistTravelled;
  double sinTotalAngle;
  double cosTotalAngle;
  double halfChangeInAngle;

  rightTrackingWheel.set_reversed(true);
  backTrackingWheel.set_reversed(true);
  pros::delay(20);
  leftTrackingWheel.reset_position();
  rightTrackingWheel.reset_position();
  backTrackingWheel.reset_position();
  pros::delay(20);


  //printf("First %d;%d;%d\n", leftTrackingWheel.get(),rightTrackingWheel.get(),backTrackingWheel.get());



  while(tracking){
    //get and store all the tracking wheel encoder values in variables
    currLeftEncVal = leftTrackingWheel.get_position()/100;
    currRightEncVal = rightTrackingWheel.get_position()/100;
    currBackEncVal = backTrackingWheel.get_position()/100;

    //printf("Second %d;%d;%d\n", leftTrackingWheel.get(),rightTrackingWheel.get(),backTrackingWheel.get());

    //calculate the distance travelled by each tracking wheel since the last cycle
    leftDistTravelled = calcTrackingWheelDistTravelled((currLeftEncVal-lastLeftEncVal));
    rightDistTravelled = calcTrackingWheelDistTravelled((currRightEncVal-lastRightEncVal));
    backDistTravelled = calcTrackingWheelDistTravelled((currBackEncVal-lastBackEncVal));

    //calculate the change in the angle of the robot since the last cycle

    changeInAngle = (rightDistTravelled - leftDistTravelled)/distBetweenLandR;
    halfChangeInAngle = changeInAngle/2;

    //if the change in angle is 0, you don't want to divide by zero
    //instead you just set the distance travelled to the distance travelled by the wheel.
    if(changeInAngle!=0){
    //calculate the distance the robot has travelled since the last cycle with the left tracking wheel
    distTravelled = 2*(sin(halfChangeInAngle))*(leftDistTravelled/changeInAngle+offsetLeft);

    //calculate the distance the robot has travelled since the last cycle, but with the back tracking wheel
    distTravelledBackWheel = 2*(sin(halfChangeInAngle))*(backDistTravelled/changeInAngle-offsetBack);
    }
    else{
      distTravelledBackWheel = backDistTravelled;
      distTravelled = leftDistTravelled;
    }

    positionData.take(mutexWait);
    totalAngle = position.angle + halfChangeInAngle;
    positionData.give();

    sinTotalAngle = sin(totalAngle);
    cosTotalAngle = cos(totalAngle);

    //calculate the change in the robot's absolute position on the field since the last cycle
    changeInX = distTravelled*cosTotalAngle+distTravelledBackWheel*sinTotalAngle;
    changeInY = distTravelled*sinTotalAngle+distTravelledBackWheel*-cosTotalAngle;

    //add the change in the robot's position from this cycle
    //to its absolute position after the last cycle
    //to find its current position
    positionData.take(mutexWait);
    position.angle+=changeInAngle;
    position.angle = limitAngle(position.angle);
    robotAngleInDegrees = radiansToDegrees(position.angle);
    position.x+=changeInX;
    position.y+=changeInY;
    positionData.give();

    //printf("Third %d;%d;%d\n", leftTrackingWheel.get(),rightTrackingWheel.get(),backTrackingWheel.get());

   if(trackingDebug){
      //print some information to screens for debugging purposes (angle and coordinates of robot)
      if(loopNumber%20){
        positionData.take(mutexWait);
          trackingDebugString = "Angle = " + std::to_string(robotAngleInDegrees) + "\nCoordinates: (" + std::to_string(position.x) + "," + std::to_string(position.y) + ")" + '\n' + "Back Tracking Wheel: " + std::to_string(currBackEncVal) + "\nLeft Tracking Wheel: " + std::to_string(currLeftEncVal) + "\nRight Tracking Wheel: " + std::to_string(currRightEncVal)+"\n";
          lv_label_set_text(labelTrackingDebug, trackingDebugString.c_str());
          //printf(trackingDebugString.c_str());
        positionData.give();
      }
    }

    //set the last encoder value equal to the current encoder value;
    lastLeftEncVal = currLeftEncVal;
    lastBackEncVal = currBackEncVal;
    lastRightEncVal = currRightEncVal;

    //printf("Fourth %i;%i;%i\n", leftTrackingWheel.get(),rightTrackingWheel.get(),backTrackingWheel.get());
    trackingStarted = true;
    //a quick delay so the brain doesn't go crazy
    pros::delay(20); //previously 10 ms
    ++loopNumber;
  }
}

Position getPosition(){
  positionData.take(mutexWait);
  Position givePos = position;
  positionData.give();
  return givePos;
}
