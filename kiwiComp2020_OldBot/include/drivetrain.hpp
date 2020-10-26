#pragma once
#include "main.h"

/*extern void moveForward(double goalDistance, int velocityPCT);
extern void turnForDegrees(double degreeGoal, int turnVelocityPCT);*/
void goToPosition(struct Position goal,int velocityPCT, bool reversed = false);
