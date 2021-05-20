#pragma once
#include "pid.hpp"
#include "main.h"

/*extern void moveForward(double goalDistance, int velocityPCT);
extern void turnForDegrees(double degreeGoal, int turnVelocityPCT);*/
//These are the PIDs used to control the voltage for the drivetrain motors.
//There is one for turning and one for going straight

extern void findBlueBall();
extern void setUpPIDs();
extern double distanceToPoint(struct Position current, struct Position goal);
extern double calcHeadingToGoalPos(struct Position curr,struct Position goal);
extern void turnToFacePosition(Position goal);
extern void turnToFaceHeading(double goalHeading);
extern void goToPosition(struct Position goal);
extern void goToPositionContinuous(struct Position goal);
extern void turnToFacePositionContinuous(struct Position goal);
extern void printToSD(std::string stringToSave);
extern void goForDistance(struct Position goal);