/*#include "pid_tuner.hpp"

std::string pidData;


static double turn_p = 600;
static double turn_i = 100;
static double turn_d = 2500;

void turnIMUTuner(double goal_degrees){
  pros::delay(3000);
  double error = 0.0;
  double gain_p = turn_p;
  double gain_i = turn_i;
  double gain_d = turn_d;

  double voltage;
  double time = 0;
  double voltage_limit = 12000;
  double vol_p = 0;
  double vol_i;
  double vol_d;
  double error_i = 0;
  double error_d;
  double vol_i_max = 4000;
  double last_error = 0;
  int count = 0;
  double imu_reading;
  int columnno = 0;
  double raw_voltage = 0;


  while(columnno<399){
    imu_reading = inertialSensor.get_rotation();
    error = goal_degrees - imu_reading;

    vol_p = error*gain_p;

    error_i+=error;

    if(error*last_error <0){
      error_i = 0;
    }

    if(abs(error)>10){
      error_i = 0;
    }

    vol_i = error_i*gain_i;

    if (vol_i >vol_i_max){
      error_i = vol_i_max/gain_i;
      vol_i=vol_i_max;
    }

    if(vol_i< -vol_i_max){
      error_i = -vol_i_max/gain_i;
      vol_i = -vol_i_max;
    }

    error_d = error - last_error;
    vol_d = error_d*gain_d;

    voltage = vol_i+vol_p+vol_d;
    raw_voltage = voltage;

    if(voltage>voltage_limit){
      voltage = voltage_limit;
    }
    else if (voltage <-voltage_limit){
      voltage = -voltage_limit;
    }

    leftFrontMotor.moveVoltage(voltage);
    leftBackMotor.moveVoltage(voltage);
    rightBackMotor.moveVoltage(-voltage);
    rightFrontMotor.moveVoltage(-voltage);

    if(abs(error)<2){
      count++;
      if(count>6){
        voltage = 0;
        break;
      }
    }
    else{
      count = 0;
    }

    last_error=error;
    pros::delay(20);
    time+=20;

    pidData += std::to_string(time)+","+std::to_string(imu_reading)+","+std::to_string(raw_voltage)+"\n";

  }

  leftFrontMotor.moveVoltage(1);
  leftBackMotor.moveVoltage(1);
  rightBackMotor.moveVoltage(1);
  rightFrontMotor.moveVoltage(1);

  leftFrontMotor.moveVoltage(0);
  leftBackMotor.moveVoltage(0);
  rightBackMotor.moveVoltage(0);
  rightFrontMotor.moveVoltage(0);

}

void printToSD(){

lv_obj_clean(lv_scr_act());
lv_obj_t* labelSDStatus;
labelSDStatus = lv_label_create(lv_scr_act(),NULL);

if(pros::usd::is_installed()){
  lv_label_set_text(labelSDStatus,"found an SD card");
  pros::delay(2000);
  FILE* usd_file_write;
  usd_file_write = fopen("/usd/pidString.txt", "w");
  int columnNumber = 0;
  lv_obj_clean(labelSDStatus);

  fputs(pidData.c_str(),usd_file_write);





  columnNumber = 0;



  fclose(usd_file_write);

  lv_label_set_text(labelSDStatus, "\n writing complete");

}
}
*/
