#include "tracking.hpp"

struct Position position{0,0,0};
//distance from each tracking wheel to tracking center/center of robot
constexpr double offsetLeft = 4.27;
constexpr double offsetRight = 4.27;
constexpr double offsetBack = 6.625;
//distance between left and right wheels
constexpr double distBetweenLandR = 8.5;

//last encoder value for each wheel
double lastLeftEncVal = 0;
double lastRightEncVal = 0;
double lastBackEncVal = 0;
int loopNumber;
static lv_obj_t* labelTrackingDebug;
std::string trackingDebugString;
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

//keep angle between 0 and 2 PI
double limitAngle(double angle){
  while(angle>=2*M_PI||angle<0){
    while(angle>=(2*M_PI)){
      angle-=2*M_PI;
    }
    while(angle<0){
      angle+=2*M_PI;
    }
  }
  return angle;
}
void setStartPoint(Position startPoint){
  //positionData.take(1000);
  position.x = startPoint.x;
  position.y = startPoint.y;
  position.angle = startPoint.angle;
  //positionData.give();
}

//track the position of the robot using tracking wheel encoder values and math
void trackPosition(){

  lv_obj_clean(lv_scr_act());
  labelTrackingDebug = lv_label_create(lv_scr_act(), NULL);

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

  while(tracking){
    //get and store all the tracking wheel encoder values in variables
    currLeftEncVal = leftTrackingWheel.get();
    currRightEncVal = rightTrackingWheel.get();
    currBackEncVal = backTrackingWheel.get();

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

    //positionData.take(20);
    totalAngle = position.angle + halfChangeInAngle;
    //positionData.give();

    sinTotalAngle = sin(totalAngle);
    cosTotalAngle = cos(totalAngle);

    //calculate the change in the robot's absolute position on the field since the last cycle
    changeInX = distTravelled*sinTotalAngle+distTravelledBackWheel*cosTotalAngle;
    changeInY = distTravelled*cosTotalAngle+distTravelledBackWheel*-sinTotalAngle;

    //add the change in the robot's position from this cycle
    //to its absolute position after the last cycle
    //to find its current position
    //positionData.take(20);
    position.angle+=changeInAngle;
    position.angle = limitAngle(position.angle);

    position.x+=changeInX;
    position.y+=changeInY;
    //positionData.give();

    //print some information to screens for debugging purposes (angle and coordinates of robot)
    if(loopNumber%20){
      robotAngleInDegrees = radiansToDegrees(position.angle);
      trackingDebugString = "Angle = " + std::to_string(robotAngleInDegrees) + "\nCoordinates: (" + std::to_string(position.x) + "," + std::to_string(position.y) + ")" + '\n' + "Back Tracking Wheel: " + std::to_string(currBackEncVal) + "\nLeft Tracking Wheel: " + std::to_string(currLeftEncVal) + "\nRight Tracking Wheel: " + std::to_string(currRightEncVal);
      lv_label_set_text(labelTrackingDebug, trackingDebugString.c_str());
      master.setText(1, 1, std::to_string(currBackEncVal)+" "+std::to_string(currLeftEncVal));
    }

    //set the last encoder value equal to the current encoder value;
    lastLeftEncVal = currLeftEncVal;
    lastBackEncVal = currBackEncVal;
    lastRightEncVal = currRightEncVal;

    //a quick delay so the brain doesn't go crazy
    pros::delay(10);
    ++loopNumber;
  }
}
