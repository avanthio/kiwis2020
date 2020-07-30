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
	setpoint = 0;
	lastActual = 0;
	firstRun = true;
}

void KiwiPID::reset(){
	firstRun = true;
	errorSum = 0;
  lastError = 0;
}

void KiwiPID::setMinErrForI(double minErrFrI){
  minErrForI = minErrFrI;
}

void KiwiPID::setSetpoint(double setpnt){
  setpoint = setpnt;
}

void KiwiPID::setIMax(double IMaximum){
  iMax = IMaximum;
}

void KiwiPID::setMaxOutput(double maxOut){
  maxOutput = maxOut;
}

void KiwiPID::setMinOutput(double minOut){
  minOutput = minOut;
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

  if(abs(error)*lastError<minErrForI){
    errorSum = 0;
  }

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

  if(output>maxOutput){
    output = maxOutput;
  }

  if(output<-maxOutput){
    output = -maxOutput;
  }

  lastError = error;

  return output;
}
