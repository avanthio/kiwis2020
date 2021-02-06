#pragma once
#include "main.h"

extern pros::Mutex positionData;

struct Position{
  double x;
  double y;
  double angle;
  bool reversed = false;
};

constexpr double trackingWheelCircumference = 3.25*M_PI;

extern Position position;

extern double degreesToRadians(double inputInDegrees);
extern double radiansToDegrees(double inputInRadians);
extern double limitAngle(double angle);
extern int getSign(double x);
extern bool trackingPause;
extern void trackPosition();
