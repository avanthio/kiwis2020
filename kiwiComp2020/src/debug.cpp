#include "debug.hpp"


bool drivetrainDebug = false;

bool trackingDebug = false;

bool buttons = false;

int debugTy = 1;


void debugType(){

  switch(debugTy){
    case 1:
      drivetrainDebug = true;
      trackingDebug = false;
      buttons = false;
      break;
    case 2:
      drivetrainDebug = false;
      trackingDebug = true;
      buttons = false;
      break;
    case 3:
      buttons = true;
      drivetrainDebug = false;
      trackingDebug = false;
    case 0:
      break;
}
}
