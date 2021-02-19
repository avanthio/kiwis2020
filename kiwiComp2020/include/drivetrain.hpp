#pragma once
#include "pid.hpp"
#include "main.h"

/*extern void moveForward(double goalDistance, int velocityPCT);
extern void turnForDegrees(double degreeGoal, int turnVelocityPCT);*/
//These are the PIDs used to control the voltage for the drivetrain motors.
//There is one for turning and one for going straight


extern void setUpPIDs();
extern double calcHeadingToGoalPos(struct Position curr,struct Position goal);
extern void turnToFacePosition(Position goal);
extern void turnToFaceHeading(double goalHeading);
extern void goToPosition(struct Position goal);
extern void goToPositions(const std::vector<struct Position>& points);
extern void printToSD();
