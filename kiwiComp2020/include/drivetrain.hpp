#pragma once
#include "main.h"

/*extern void moveForward(double goalDistance, int velocityPCT);
extern void turnForDegrees(double degreeGoal, int turnVelocityPCT);*/
extern KiwiPID straightPID;
extern KiwiPID turnPID;
extern void setUpPIDs();
extern double calcHeadingToGoalPos(struct Position curr,struct Position goal);
extern void turnToFacePosition(struct Position goal);
extern void goToPosition(struct Position goal);
//extern void goToPositions(struct Position points[2]);
extern void printToSD();
