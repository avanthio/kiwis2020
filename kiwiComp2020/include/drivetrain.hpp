#pragma once
#include "main.h"

/*extern void moveForward(double goalDistance, int velocityPCT);
extern void turnForDegrees(double degreeGoal, int turnVelocityPCT);*/
extern void setUpPIDs();
extern double calcHeadingToGoalPos(struct Position curr,struct Position goal);
extern void turnToFacePosition(double);
extern void goToPosition(struct Position goal, bool reversed = false);
extern void printToSD();
