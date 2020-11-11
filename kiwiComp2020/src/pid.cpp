#include "pid.hpp"

KiwiPID::KiwiPID(double kp,double ki, double kd){
  init();
  p = kp;
  i = ki;
  d = kd;
}

void KiwiPID::init(){
	p=0;
	i=0;
	d=0;

	iMax = 0;
	errorSum = 0;
  minErrForI = 0;
  lastError = 0;
	maxOutput = 0;
	minOutput = 0;
  rawOutput = 0;
	setpoint = 0;
	lastActual = 0;
	firstRun = true;
}

//resets some stored values for the PID
void KiwiPID::reset(){
	firstRun = true;
	errorSum = 0;
  lastError = 0;
  rawOutput = 0;
}

//sets how much the error can be before the PID starts using integral
void KiwiPID::setMinErrForI(double minErrFrI){
  minErrForI = minErrFrI;
}

//sets the goal for the PID
void KiwiPID::setSetpoint(double setpnt){
  setpoint = setpnt;
}

//set the maximum output of the integral portion of the PID
void KiwiPID::setIMax(double IMaximum){
  iMax = IMaximum;
}

void KiwiPID::setMaxOutput(double maxOut){
  maxOutput = maxOut;
}

void KiwiPID::setMinOutput(double minOut){
  minOutput = minOut;
}

double KiwiPID::getRawOutput(){
  return rawOutput;
}

double KiwiPID::getOutput(double actual){
  double output;
  double pOutput;
  double iOutput;
  double dOutput;

  double error = setpoint - actual;

  pOutput = error*p;

  errorSum += error;

  if(error*lastError<0){
    errorSum = 0;
  }

  /*if(abs(error)*lastError<minErrForI){
    errorSum = 0;
  }*/

  iOutput = errorSum*i;

  if(iOutput>iMax){
    errorSum = iMax/i;
    iOutput = iMax;
  }

  if(iOutput<-iMax){
    errorSum = -iMax/i;
    iOutput = -iMax;
  }

  dOutput = (error-lastError)*d;

  output = pOutput+iOutput+dOutput;
  rawOutput = output;

  if(output>maxOutput){
    output = maxOutput;
  }

  if(output<minOutput){
    output = minOutput;
  }

  lastError = error;

  return output;
}
