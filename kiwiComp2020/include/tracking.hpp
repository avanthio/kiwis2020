#pragma once
#include "main.h"

extern pros::Mutex positionData;

constexpr double trackingWheelCircumference = 3.25*M_PI;
struct Position{
  double x;
  double y;
  double angle;
};

extern Position position;

extern double degreesToRadians(double inputInDegrees);
extern double radiansToDegrees(double inputInRadians);


extern void trackPosition();
