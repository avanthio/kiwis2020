#pragma once
#include "main.h"

extern void strPIDsettings();
extern bool checkBlue();
extern void redCycleSimple();
extern void redCycleFull();
extern void blueCycleSimple();
extern void blueCycleFull();
extern void goToRedBall(struct Position goalP);
extern void goToBlueBall(struct Position goalP);
extern void goToBlueBallSoft(struct Position goalP);
extern void alignToBlue(struct Position goalP);