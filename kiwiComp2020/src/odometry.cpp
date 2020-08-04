#include "odometry.hpp"

constexpr double offsetLeft = 4.125;
constexpr double offsetRight = 4.125;
constexpr double offsetBack = 6.625;
constexpr double distBetweenLandR = offsetLeft+offsetRight;
double lastLeftEncVal = 0;
double lastRightEncVal = 0;
double lastBackEncVal = 0;
double angle = 0;
double xCoord = 0;
double yCoord = 0;

double calcTrackingWheelDistTravelled(double trackingWheelEncoderValue){
  return trackingWheelEncoderValue/360*trackingWheelCircumference;
}
double degreesToRadians(double inputInDegrees){
  return inputInDegrees*M_PI/180;
}
double radiansToDegrees(double inputInRadians){
  return inputInRadians*180/M_PI;
}

void trackPosition(){

  double currLeftEncVal = leftTrackingWheel.get();
  double currRightEncVal = rightTrackingWheel.get();
  double currBackEncVal = backTrackingWheel.get();

  double leftDistTravelled = calcTrackingWheelDistTravelled(currLeftEncVal-lastLeftEncVal);
  double rightDistTravelled = calcTrackingWheelDistTravelled(currRightEncVal-lastRightEncVal);
  double backDistTravelled = calcTrackingWheelDistTravelled(currBackEncVal-lastBackEncVal);

  double changeInAngle = (rightDistTravelled - leftDistTravelled)/distBetweenLandR;

  double distTravelled = 2*(sin(changeInAngle/2))*(leftDistTravelled/changeInAngle+offsetLeft);
  double distTravelledBackWheel = 2*(sin(changeInAngle/2))*(backDistTravelled/changeInAngle+offsetBack);

  double totalAngle = angle + changeInAngle/2;

  double changeInX = distTravelled*(cos(totalAngle))+distTravelledBackWheel*(-sin(totalAngle));
  double changeInY = distTravelled*(sin(totalAngle))+distTravelledBackWheel*cos(totalAngle);

  angle+=changeInAngle;
  xCoord+=changeInX;
  yCoord+=changeInY;

}
