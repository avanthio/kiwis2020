#pragma once
#include "main.h"

class KiwiPID{
public:
  KiwiPID(double, double, double);
  void reset();
  void init();

  void setSetpoint(double);
  void setMinErrForI(double);
  void setIMax(double);
  void setMaxOutput(double);
  void setMinOutput(double);
  double getOutput(double);
  double getOutput(double setpt, double actual);
  double getRawOutput();


private:
  double p;
  double i;
  double d;
  double iMax;
  double maxOutput;
  double minOutput;
  double setpoint;
  double errorSum;
  double lastError;
  double lastActual;
  double rawOutput;
  bool firstRun;
  double minErrForI;
  void initialize();

};
