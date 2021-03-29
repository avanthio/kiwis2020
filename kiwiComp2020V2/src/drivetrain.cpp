#include "drivetrain.hpp"

static lv_obj_t* labelX;

//IMPORTANT NOTES FOR DRIVETRAIN CODE:
//The input for all functions related to the angle of the robot must be in radians!!!

//As a result me wanting nice PID,
//the voltage/velocity for the drivetrain motors is only controlled by PID
//with the maximum being the maximum possible voltage (12000)
//and the minimum being the minimum possible voltage (-12000)

//the PID must be reset every time it is used (reset outputs and stored values, not gains)
//The setpoint (goal for the PID) is always 0 because the input is the current error
//therefore, the setpoints are set in the PID setup function
KiwiPID turnPID(16000,1000,20000); //17750,200,2//17000,500,10000(better?)
KiwiPID straightPID(1200,0.5,20);//1000,1,20
KiwiPID angleAdjustPID(6000,100,0);





std::string pidData;

//This function manages the PIDs at the start of the program.
//It is called in the initialize function in main.cpp
void setUpPIDs(){
  turnPID.setMaxOutput(10000);
  turnPID.setMinOutput(-10000);
  straightPID.setMaxOutput(6500);
  straightPID.setMinOutput(-6500);
  angleAdjustPID.setMaxOutput(2000);
  angleAdjustPID.setMinOutput(-2000);

  turnPID.setSetpoint(0);
  straightPID.setSetpoint(0);
  angleAdjustPID.setSetpoint(0);

  turnPID.setIMax(12000);
  turnPID.setIMin(1000);
  turnPID.setMaxErrForI(degreesToRadians(10));
  turnPID.setDeadzone(degreesToRadians(1));
  straightPID.setIMax(6000);
  straightPID.setIMin(0);
  straightPID.setMaxErrForI(1000);
  straightPID.setDeadzone(0);
  angleAdjustPID.setIMax(6000);
  angleAdjustPID.setDeadzone(0);
  angleAdjustPID.setIMin(0);
  angleAdjustPID.setMaxErrForI(1000);


}


double distanceToPoint(Position current, Position goal){
  Position error;
  error.x = goal.x-current.x;
  error.y = goal.y-current.y;

  return sqrt(error.x*error.x+error.y*error.y);
}

//decides which way is fastest to turn and reach goal heading. true = CC, false = C
//this has also been checked for all cases in Visual Studio, and works :)
bool whichWayToTurn(double currHeading, double goalHeading){
  if((currHeading<goalHeading) && ((goalHeading-currHeading)<=M_PI)){
    return true;
  }
  else if((currHeading>goalHeading) &&((currHeading-goalHeading)>M_PI)){
    return true;
  }
  else if((currHeading<goalHeading) &&((goalHeading-currHeading)>M_PI)){
    return false;
  }
  else if((currHeading>goalHeading) &&((currHeading-goalHeading)<=M_PI)){
    return false;
  }
  return false;
}

struct Position newGoal(Position curr, Position goal, double angleErr) {
    Position newG;
    Position midPoint;
    midPoint.x = (curr.x + goal.x) / 2;
    midPoint.y = (curr.y + goal.y) / 2;
    std::cout << midPoint.x << '\n';
    std::cout << midPoint.y << '\n';
    double distToGoal = distanceToPoint(curr, goal);

    double theta = limitAngle(2 * angleErr);

    newG.x = midPoint.x + (distToGoal/2 * sin(theta));
    newG.y = midPoint.y + (distToGoal/2 * cos(theta));

    return newG;
}


//calculate the necessary heading of the robot to reach a goal position,
//based on current position and goal position
//has been checked over with testing in visual studio
//it works in all quadrants and potential situations (y 0, x+- and x 0, y+-)
double calcHeadingToGoalPos(struct Position curr, struct Position goal) {

    double theta = 0;

    if ((goal.x - curr.x) != 0) {
        theta = atan((goal.y - curr.y) / (goal.x - curr.x));
        int signTheta = getSign(theta);
        if (goal.y > curr.y) {
            if (signTheta == -1) {
                theta += M_PI;
            }
        }
        else if (goal.y < curr.y) {
            if (signTheta == 1) {
                theta += M_PI;
            }
            else if (signTheta == -1) {
                theta += (2 * M_PI);
            }
        }
        else if (goal.y == curr.y) {
            if (goal.x > curr.x) {
                theta = 0;
            }
            else {
                theta = M_PI;
            }
        }
    }
    else {
        theta = M_PI_2;
        if (goal.y < curr.y) {
            theta *= -1;
        }
    }
    theta = limitAngle(theta);


    return theta;
}


void findBlueBall(){

  if(drivetrainDebug){
    lv_obj_clean(lv_scr_act());
    labelX = lv_label_create(lv_scr_act(),NULL);
  }

  std::string visionStr;
  int visionCount = visionSensor.get_object_count();
  visionStr = std::to_string(visionCount);
  if(visionCount>0){
    lv_label_set_text(labelX,visionStr.c_str());

  }

}


//turns the robot to face an ABSOLUTE heading. ABSOLUTE. NOT RELATIVE.
//If you want to face away from a point,remember to set reversed (in structure) to true
//If you want to face a certain heading, use the turn to face heading function
//(which doesn't exist lol)

void turnToFacePosition(Position goal){
  int time = 0;

  if(drivetrainDebug){
    lv_obj_clean(lv_scr_act());
    labelX = lv_label_create(lv_scr_act(),NULL);
  }

  turnPID.reset();

  int x = 0;
  double iOut = 0;
  struct Position current = getPosition();
  int timeInRange = 0;
  int actualVoltage;
  struct Position error;
  std::string outputStr;
  double goalHeading = calcHeadingToGoalPos(current,goal);
  if(goal.reversed){
    goalHeading = limitAngle(goalHeading+M_PI);
  }

  while(1){

    current = getPosition();
    error.angle = limitAngle(goalHeading-current.angle);

    actualVoltage = turnPID.getOutput(error.angle);

    iOut = turnPID.getiOutput();

    if(drivetrainDebug){
      outputStr = "Input:"+std::to_string(radiansToDegrees(error.angle))+ "   Output: "+std::to_string(actualVoltage) + "\nTime: "+std::to_string(time) + "\n I Output: "+std::to_string(iOut);
      lv_label_set_text(labelX,outputStr.c_str());
    }


      leftFrontMotor.moveVoltage(actualVoltage);
      leftBackMotor.moveVoltage(actualVoltage);
      rightFrontMotor.moveVoltage(-actualVoltage);
      rightBackMotor.moveVoltage(-actualVoltage);


    if(abs(error.angle)<degreesToRadians(1.5)){
      x+=1;
    }
    else{
      x = 0;
    }

    //put this back!!
    if(x>10){
      timeInRange = time;
      break;
    }



    pros::delay(20);
    //Below is some stuff to help tune PID, don't worry about it too much.
    time+=20;
    pidData+=std::to_string(time)+','+std::to_string(turnPID.getRawOutput())+'\n';
  }

  leftFrontMotor.moveVoltage(0);
  rightFrontMotor.moveVoltage(0);
  leftBackMotor.moveVoltage(0);
  rightBackMotor.moveVoltage(0);
}


void turnToFaceHeading(double goalHeading){
  int time = 0;

  if(drivetrainDebug){
    lv_obj_clean(lv_scr_act());
    labelX = lv_label_create(lv_scr_act(),NULL);
  }

  turnPID.reset();

  int x = 0;
  double iOut = 0;
  struct Position current = getPosition();
  int timeInRange = 0;
  int actualVoltage;
  struct Position error;
  std::string outputStr;

  while(1){

    current = getPosition();
    error.angle = limitAngle(goalHeading-current.angle);

    actualVoltage = turnPID.getOutput(error.angle);

    iOut = turnPID.getiOutput();

    if(drivetrainDebug){
      outputStr = "Input:"+std::to_string(radiansToDegrees(error.angle))+ "   Output: "+std::to_string(actualVoltage) + "\nTime: "+std::to_string(time) + "\n I Output: "+std::to_string(iOut);
      lv_label_set_text(labelX,outputStr.c_str());
    }


      leftFrontMotor.moveVoltage(actualVoltage);
      leftBackMotor.moveVoltage(actualVoltage);
      rightFrontMotor.moveVoltage(-actualVoltage);
      rightBackMotor.moveVoltage(-actualVoltage);


    if(abs(error.angle)<degreesToRadians(1.5)){
      x+=1;
    }
    else{
      x = 0;
    }

    //put this back!!
    if(x>10){
      timeInRange = time;
      break;
    }



    pros::delay(20);
    //Below is some stuff to help tune PID, don't worry about it too much.
    time+=20;
    pidData+=std::to_string(time)+','+std::to_string(turnPID.getRawOutput())+'\n';
  }

  leftFrontMotor.moveVoltage(0);
  rightFrontMotor.moveVoltage(0);
  leftBackMotor.moveVoltage(0);
  rightBackMotor.moveVoltage(0);
}


//input your goal position to drive to.
//might behave strangely if not turned towards/away from point first
//bool reversed defaults to false.
//input your goal position to drive to.
//might behave strangely if not turned towards/away from point first
//bool reversed defaults to false.
void goToPosition(struct Position goal){

  if(goal.reversed==true){
    straightPID.setMaxOutput(6500);
    straightPID.setMinOutput(-6500);
  }
  else{
    straightPID.setMaxOutput(7000);
    straightPID.setMinOutput(-7000);
  }

  straightPID.reset();
  angleAdjustPID.reset();
  int x = 0;
  int y = 0;
  struct Position current = getPosition();
  Position startOfDrive = current;
  double headingToGoalPos = calcHeadingToGoalPos(current,goal);
  if(goal.reversed==true){
    headingToGoalPos=limitAngle(headingToGoalPos+M_PI);
  }
  double distanceToGoalPos = distanceToPoint(current,goal);
  if(goal.reversed==true){
    distanceToGoalPos*=-1;
  }
  double initialDistance = distanceToGoalPos;
  struct Position error;

  int angleAdjustment = 0;
  int baseVoltage = 0;
  std::string outputStr;
  double pastThreeErrorSum = 0;
  double errAverage = 0;
  double previousErrAverage = 0;
  int loopCount = 0;
  int count = 0;


  if(drivetrainDebug){
    lv_obj_clean(lv_scr_act());
    labelX = lv_label_create(lv_scr_act(),NULL);
  }

  while(1){
    current = getPosition();
    //positionData.give();

    headingToGoalPos = calcHeadingToGoalPos(current, goal);
    if(goal.reversed==true){
      headingToGoalPos = limitAngle(headingToGoalPos+M_PI);
    }

    error.angle = headingToGoalPos-current.angle;
    error.angle = limitAngle(error.angle);

    distanceToGoalPos = distanceToPoint(current,goal);
    if(goal.reversed==true){
      distanceToGoalPos*=-1;
    }
    if(abs(initialDistance)<abs(distanceToPoint(startOfDrive,current))){
      distanceToGoalPos*=-1;
    }



    baseVoltage = straightPID.getOutput(-distanceToGoalPos);

    if(abs(distanceToGoalPos)>4){
      angleAdjustment = angleAdjustPID.getOutput(error.angle);
      pastThreeErrorSum += distanceToGoalPos;
      if(loopCount%6 == 0){
        errAverage = pastThreeErrorSum/3;
        if(abs(previousErrAverage-errAverage)<0.1){
          break;
        }
        previousErrAverage = errAverage;
        errAverage = 0;
        pastThreeErrorSum = 0;
      }
      loopCount+=1;
    }
    else{
      angleAdjustment = 0;
      pastThreeErrorSum += distanceToGoalPos;
      if(loopCount%6 == 0){
        errAverage = pastThreeErrorSum/3;
        if(abs(previousErrAverage-errAverage)<0.25){
          break;
        }
        previousErrAverage = errAverage;
        errAverage = 0;
        pastThreeErrorSum = 0;
      }
      loopCount+=1;
    }

      rightFrontMotor.moveVoltage(baseVoltage-angleAdjustment);
      rightBackMotor.moveVoltage(baseVoltage-angleAdjustment);
      leftFrontMotor.moveVoltage(baseVoltage+angleAdjustment);
      leftBackMotor.moveVoltage(baseVoltage+angleAdjustment);





    if(abs(distanceToGoalPos)<0.5){
      x+=1;
    }
    else{
      x = 0;
    }

    if(x>6){
      break;
    }

    if(drivetrainDebug){
      outputStr = "Input:"+std::to_string(distanceToGoalPos)+ "\nOutput: "+std::to_string(baseVoltage)+ "\nAngle Error:"+std::to_string(error.angle)+ "\nP Output:"+std::to_string(straightPID.getpOutput())+"\nI Output:"+std::to_string(straightPID.getiOutput())+"\nD Output:"+std::to_string(straightPID.getdOutput());
      lv_label_set_text(labelX,outputStr.c_str());
      //master.setText(0,0,outputStr);
    }

    pros::delay(20);
    count+=1;
  }

  leftFrontMotor.moveVoltage(0);
  leftBackMotor.moveVoltage(0);
  rightFrontMotor.moveVoltage(0);
  rightBackMotor.moveVoltage(0);

}



void goToPositionContinuous(Position goal){
  if(goal.reversed==true){
    straightPID.setMaxOutput(6500);
    straightPID.setMinOutput(-6500);
  }
  else{
    straightPID.setMaxOutput(7000);
    straightPID.setMinOutput(-7000);
  }

  straightPID.reset();
  angleAdjustPID.reset();
  int x = 0;
  int y = 0;
  struct Position current = getPosition();
  Position startOfDrive = current;
  double headingToGoalPos = calcHeadingToGoalPos(current,goal);
  if(goal.reversed==true){
    headingToGoalPos=limitAngle(headingToGoalPos+M_PI);
  }
  double distanceToGoalPos = distanceToPoint(current,goal);
  if(goal.reversed==true){
    distanceToGoalPos*=-1;
  }
  double initialDistance = distanceToGoalPos;
  struct Position error;

  int angleAdjustment = 0;
  int baseVoltage = 0;
  std::string outputStr;
  double pastThreeErrorSum = 0;
  double errAverage = 0;
  double previousErrAverage = 0;
  int loopCount = 0;
  int count = 0;


  if(drivetrainDebug){
    lv_obj_clean(lv_scr_act());
    labelX = lv_label_create(lv_scr_act(),NULL);
  }

  while(1){
    current = getPosition();
    //positionData.give();

    headingToGoalPos = calcHeadingToGoalPos(current, goal);
    if(goal.reversed==true){
      headingToGoalPos = limitAngle(headingToGoalPos+M_PI);
    }

    error.angle = headingToGoalPos-current.angle;
    error.angle = limitAngle(error.angle);

    distanceToGoalPos = distanceToPoint(current,goal);
    if(goal.reversed==true){
      distanceToGoalPos*=-1;
    }
    if(abs(initialDistance)<abs(distanceToPoint(startOfDrive,current))){
      distanceToGoalPos*=-1;
    }



    baseVoltage = straightPID.getOutput(-distanceToGoalPos);

    if(abs(distanceToGoalPos)>4){
      angleAdjustment = angleAdjustPID.getOutput(error.angle);
    }
    else{
      angleAdjustment = 0;
      pastThreeErrorSum += distanceToGoalPos;
      if(loopCount%6 == 0){
        errAverage = pastThreeErrorSum/3;
        if(abs(previousErrAverage-errAverage)<0.25){
          break;
        }
        previousErrAverage = errAverage;
        errAverage = 0;
        pastThreeErrorSum = 0;
      }
      loopCount+=1;
    }

      rightFrontMotor.moveVoltage(baseVoltage-angleAdjustment);
      rightBackMotor.moveVoltage(baseVoltage-angleAdjustment);
      leftFrontMotor.moveVoltage(baseVoltage+angleAdjustment);
      leftBackMotor.moveVoltage(baseVoltage+angleAdjustment);





    if(abs(distanceToGoalPos)<1){
      x+=1;
    }
    else{
      x = 0;
    }

    if(x>3){
      break;
    }

    if(drivetrainDebug){
      outputStr = "Input:"+std::to_string(distanceToGoalPos)+ "\nOutput: "+std::to_string(baseVoltage)+ "\nAngle Error:"+std::to_string(error.angle)+ "\nP Output:"+std::to_string(straightPID.getpOutput())+"\nI Output:"+std::to_string(straightPID.getiOutput())+"\nD Output:"+std::to_string(straightPID.getdOutput());
      lv_label_set_text(labelX,outputStr.c_str());
      //master.setText(0,0,outputStr);
    }

    pros::delay(20);
    count+=1;
  }

}

void turnToFacePositionContinuous(struct Position goal){

  int time = 0;

  if(drivetrainDebug){
    lv_obj_clean(lv_scr_act());
    labelX = lv_label_create(lv_scr_act(),NULL);
  }

  turnPID.reset();

  int x = 0;
  double iOut = 0;
  struct Position current = getPosition();
  int timeInRange = 0;
  int actualVoltage;
  struct Position error;
  std::string outputStr;
  double goalHeading = calcHeadingToGoalPos(current,goal);
  if(goal.reversed){
    goalHeading = limitAngle(goalHeading+M_PI);
  }

  while(1){

    current = getPosition();
    error.angle = limitAngle(goalHeading-current.angle);

    actualVoltage = turnPID.getOutput(error.angle);

    iOut = turnPID.getiOutput();

    if(drivetrainDebug){
      outputStr = "Input:"+std::to_string(radiansToDegrees(error.angle))+ "   Output: "+std::to_string(actualVoltage) + "\nTime: "+std::to_string(time) + "\n I Output: "+std::to_string(iOut);
      lv_label_set_text(labelX,outputStr.c_str());
    }


      leftFrontMotor.moveVoltage(actualVoltage);
      leftBackMotor.moveVoltage(actualVoltage);
      rightFrontMotor.moveVoltage(-actualVoltage);
      rightBackMotor.moveVoltage(-actualVoltage);


    if(abs(error.angle)<degreesToRadians(1.5)){
      x+=1;
    }
    else{
      x = 0;
    }

    //put this back!!
    if(x>5){
      timeInRange = time;
      break;
    }



    pros::delay(20);
    //Below is some stuff to help tune PID, don't worry about it too much.
    time+=20;
    pidData+=std::to_string(time)+','+std::to_string(turnPID.getRawOutput())+'\n';
  }


}


void goToPositions(const std::vector<struct Position>& points){

  if(drivetrainDebug){
    //!!lv_obj_clean(lv_scr_act());
    labelX = lv_label_create(lv_scr_act(),NULL);
  }

  straightPID.reset();
  angleAdjustPID.reset();
  int x = 0;
  int y = 0;
  struct Position current = getPosition();
  Position startOfDrive = current;
  double headingToGoalPos;

  double distanceToGoalPos = distanceToPoint(current, points[1]);

  double initialDistance = distanceToGoalPos;
  struct Position error;

  int angleAdjustment = 0;
  int baseVoltage = 0;
  std::string outputStr;
  double pastThreeErrorSum = 0;
  double errAverage = 0;
  double previousErrAverage = 0;
  int loopCount = 0;

  int actualVoltage;
  double goalHeading;

  for(size_t pointNo = 0; pointNo<(points.size()-1);pointNo+=1){
    straightPID.reset();
    angleAdjustPID.reset();
    turnPID.reset();
    current = getPosition();
    startOfDrive = current;
    distanceToGoalPos = distanceToPoint(current, points[pointNo]);
    initialDistance = distanceToGoalPos;
    while(1){
      current = getPosition();
      //positionData.give();

      headingToGoalPos = calcHeadingToGoalPos(current,points[pointNo]);


      error.angle = headingToGoalPos-current.angle;
      error.angle = limitAngle(error.angle);

      distanceToGoalPos = distanceToPoint(current,points[pointNo]);

      if(abs(initialDistance)<abs(distanceToPoint(startOfDrive,current))){
        distanceToGoalPos*=-1;
      }



      baseVoltage = straightPID.getOutput(-distanceToGoalPos);

      angleAdjustment = angleAdjustPID.getOutput(error.angle);

      if(abs(distanceToGoalPos)<5){
        break;
      }


      rightFrontMotor.moveVoltage(baseVoltage-angleAdjustment);
      rightBackMotor.moveVoltage(baseVoltage-angleAdjustment);
      leftFrontMotor.moveVoltage(baseVoltage+angleAdjustment);
      leftBackMotor.moveVoltage(baseVoltage+angleAdjustment);


      if(drivetrainDebug){
        outputStr = "Input:"+std::to_string(distanceToGoalPos)+ "\nOutput: "+std::to_string(baseVoltage)+ "\nAngle Error"+std::to_string(radiansToDegrees(error.angle))+"\nAngle Adjustment:"+std::to_string(angleAdjustment)+"\nCurrent Angle:"+std::to_string(radiansToDegrees(current.angle))+"\nInitial Distance:"+std::to_string(initialDistance)+"\nDistance from start point:"+std::to_string(distanceToPoint(current,startOfDrive));
        lv_label_set_text(labelX,outputStr.c_str());
        master.setText(0,0,outputStr);
      }

      pros::delay(20);

    }

    if(pointNo+1<points.size()){

      goalHeading = calcHeadingToGoalPos(current,points[pointNo+1]);
      if(points[pointNo+1].reversed){
        goalHeading = limitAngle(goalHeading+M_PI);
      }

      while(1){

        current = getPosition();
        error.angle = limitAngle(goalHeading-current.angle);

        actualVoltage = turnPID.getOutput(error.angle);




          leftFrontMotor.moveVoltage(actualVoltage);
          leftBackMotor.moveVoltage(actualVoltage);
          rightFrontMotor.moveVoltage(-actualVoltage);
          rightBackMotor.moveVoltage(-actualVoltage);


        if(abs(error.angle)<degreesToRadians(1.5)){
          break;
        }




        pros::delay(20);
        //Below is some stuff to help tune PID, don't worry about it too much.

      }

    }
  }

  straightPID.reset();
  angleAdjustPID.reset();
  turnPID.reset();
  current = getPosition();
  startOfDrive = current;
  distanceToGoalPos = distanceToPoint(current, points[points.size()-1]);
  initialDistance = distanceToGoalPos;

  while(1){
    current = getPosition();
    //positionData.give();

    headingToGoalPos = calcHeadingToGoalPos(current, points[points.size()-1]);


    error.angle = headingToGoalPos-current.angle;
    error.angle = limitAngle(error.angle);

    distanceToGoalPos = distanceToPoint(current,points[2]);

    if(abs(initialDistance)<abs(distanceToPoint(startOfDrive,current))){
      distanceToGoalPos*=-1;
    }



    baseVoltage = straightPID.getOutput(-distanceToGoalPos);

    if(abs(distanceToGoalPos)>5){
      angleAdjustment = angleAdjustPID.getOutput(error.angle);
    }
    else{
      angleAdjustment = 0;
      pastThreeErrorSum += distanceToGoalPos;
      if(loopCount%6 == 0){
        errAverage = pastThreeErrorSum/3;
        if(abs(previousErrAverage-errAverage)<0.25){
          break;
        }
        previousErrAverage = errAverage;
        errAverage = 0;
        pastThreeErrorSum = 0;
      }
      loopCount+=1;
    }


      rightFrontMotor.moveVoltage(baseVoltage-angleAdjustment);
      rightBackMotor.moveVoltage(baseVoltage-angleAdjustment);
      leftFrontMotor.moveVoltage(baseVoltage+angleAdjustment);
      leftBackMotor.moveVoltage(baseVoltage+angleAdjustment);





    if(abs(distanceToGoalPos)<1){
      x+=1;
    }
    else{
      x = 0;
    }

    if(x>6){
      break;
    }

    if(drivetrainDebug){
      outputStr = "Input:"+std::to_string(distanceToGoalPos)+ "\nOutput: "+std::to_string(baseVoltage)+ "\nAngle Error"+std::to_string(radiansToDegrees(error.angle))+"\nAngle Adjustment:"+std::to_string(angleAdjustment)+"\nCurrent Angle:"+std::to_string(radiansToDegrees(current.angle))+"\nInitial Distance:"+std::to_string(initialDistance)+"\nDistance from start point:"+std::to_string(distanceToPoint(current,startOfDrive));
      lv_label_set_text(labelX,outputStr.c_str());
      master.setText(0,0,outputStr);
    }

    pros::delay(20);

  }

  leftFrontMotor.moveVoltage(0);
  leftBackMotor.moveVoltage(0);
  rightFrontMotor.moveVoltage(0);
  rightBackMotor.moveVoltage(0);

}

void printToSD(std::string stringToSave){

  lv_obj_clean(lv_scr_act());
  lv_obj_t* labelSDStatus;
  labelSDStatus = lv_label_create(lv_scr_act(),NULL);

  if(pros::usd::is_installed()){
    lv_label_set_text(labelSDStatus,"found an SD card");
    pros::delay(2000);
    FILE* usd_file_write;
    usd_file_write = fopen("/usd/angleAdjust.txt", "w");
    int columnNumber = 0;
    lv_obj_clean(labelSDStatus);

    fputs(stringToSave.c_str(),usd_file_write);
    columnNumber = 0;

    fclose(usd_file_write);

    lv_label_set_text(labelSDStatus, "\n writing complete");

  }
}


/*std::string info;
const int loopDelay = 20;
static lv_obj_t* labelMoveForwardDebug;
static lv_obj_t* labelTurnDebug;

const double tireCircumference = 3.25*M_PI;//Never, ever, under any circumstances mess with this
double calcDriveDegrees( double targetDistanceInInches ) {//for calculating distance driving forward, not turning, in inches
    //divides goal distance by tire circumference (calculate wheel rotations needed to move a given distance)
    //then multiply by 360 to get the degrees of motor rotation
    return targetDistanceInInches / tireCircumference *360.0 ;
}
double calcWheelDistTravelled(double trackingWheelEncoderValue){
  return trackingWheelEncoderValue/360*tireCircumference;
}

int calcStep(int timeToAccel){//calculates the number of steps needed based on the time spent to accelerate and the delay in the loop
  return timeToAccel/loopDelay;
}
int calcAccel(int goalVelocity){//calculates the velocity increase per step based on # of steps and goal velocity
  int accelTime = 700;
  return goalVelocity/(calcStep(accelTime));
}

double distBetweenLandR = 8.5;

void moveForward(double goalDistance, int velocityPCT){

  //lv_obj_clean(lv_scr_act());
  labelMoveForwardDebug = lv_label_create(lv_scr_act(), NULL);

  	double goal = calcDriveDegrees(goalDistance);
  	int goalVelocity = velocityPCT*2;
    int step = calcAccel(goalVelocity);
    int initialVelocity = calcAccel(goalVelocity);
    int actualVelocity = initialVelocity;
  	double currEnc = 0;
    double endEnc = 0;
  	double currInertVal = 0;
  	double redirect = 0;
    int loopNumber = 0;
    std::string moveForwardDebugString;

  	leftTrackingWheel.reset();
    rightTrackingWheel.reset();



  	while(abs(currEnc)<abs(goal)){
  		currEnc = (leftTrackingWheel.get()+rightTrackingWheel.get())/2.0;

      if(currEnc<=(0.5*goal)&&actualVelocity<goalVelocity){
        actualVelocity+=step;
        endEnc = currEnc;
      }
      else if((currEnc)>=(goal-endEnc)&&abs(actualVelocity)>abs(initialVelocity)){
        actualVelocity-=step;
      }




  		leftFrontMotor.moveVelocity(actualVelocity);
  		rightFrontMotor.moveVelocity(actualVelocity);
  		leftBackMotor.moveVelocity(actualVelocity);
  		rightBackMotor.moveVelocity(actualVelocity);



      if(loopNumber%20){
        moveForwardDebugString = "Left TW = " + std::to_string(leftTrackingWheel.get()) + "   " + "Right TW: " + std::to_string(rightTrackingWheel.get());
        lv_label_set_text(labelMoveForwardDebug, moveForwardDebugString.c_str());
        master.setText(1, 1, std::to_string(actualVelocity));
      }
      ++loopNumber;
  		pros::delay(loopDelay);
  	}

    leftFrontMotor.moveVelocity(1);
    rightFrontMotor.moveVelocity(1);
    leftBackMotor.moveVelocity(1);
    rightBackMotor.moveVelocity(1);


    leftFrontMotor.moveVelocity(0);
    rightFrontMotor.moveVelocity(0);
    leftBackMotor.moveVelocity(0);
    rightBackMotor.moveVelocity(0);


}


//turns the robot some number of degrees. negative degrees means counterclockwise
//velocity input in pct
//increases velocity slowly in beginning and decreases at end to prevent jolting (loss of cubes)
void turnForDegrees(double degreeGoal, int turnVelocityPCT){

  lv_obj_clean(lv_scr_act());
  labelTurnDebug = lv_label_create(lv_scr_act(), NULL);

  leftTrackingWheel.reset();
  rightTrackingWheel.reset();

  int goalVelocity = turnVelocityPCT*2;
  int step = calcAccel(goalVelocity);
  int initialVelocity = calcAccel(goalVelocity);
  int actualVelocity = goalVelocity;
  int finalVelocity = 50;
	double currEnc = 0;
  int endEnc = 0;
  double rightDistTravelled = 0;
  double leftDistTravelled = 0;
  double changeInAngle = 0;
  double endAngle = 0;
  int loopNumber = 0;
  std::string turnDebugString;

  leftFrontMotor.moveVelocity(initialVelocity);
  rightFrontMotor.moveVelocity(-initialVelocity);
  leftBackMotor.moveVelocity(initialVelocity);
  rightBackMotor.moveVelocity(-initialVelocity);

  master.clear();

  while(abs(changeInAngle)<abs(degreeGoal)){
    currEnc = (leftTrackingWheel.get()-rightTrackingWheel.get())/2.0;
    rightDistTravelled = calcWheelDistTravelled(rightTrackingWheel.get());
    leftDistTravelled = calcWheelDistTravelled(leftTrackingWheel.get());
    changeInAngle = ((leftDistTravelled-rightDistTravelled)/distBetweenLandR) *180/M_PI;



      leftFrontMotor.moveVelocity(actualVelocity);
      rightFrontMotor.moveVelocity(-actualVelocity);
      leftBackMotor.moveVelocity(actualVelocity);
      rightBackMotor.moveVelocity(-actualVelocity);



    if(loopNumber%100){
      turnDebugString = "Left TW = " + std::to_string(leftTrackingWheel.get()) + "   " + "Right TW: " + std::to_string(rightTrackingWheel.get()) + "   Angle: " + std::to_string(changeInAngle);
      lv_label_set_text(labelTurnDebug, turnDebugString.c_str());
    }
    ++loopNumber;
    pros::delay(loopDelay);
  }
  leftFrontMotor.moveVelocity(1);
  rightFrontMotor.moveVelocity(1);
  leftBackMotor.moveVelocity(1);
  rightBackMotor.moveVelocity(1);

  leftFrontMotor.moveVelocity(0);
  rightFrontMotor.moveVelocity(0);
  leftBackMotor.moveVelocity(0);
  rightBackMotor.moveVelocity(0);

  leftFrontMotor.moveAbsolute(goalDegrees,finalVelocity);
  rightFrontMotor.moveAbsolute(-goalDegrees,finalVelocity);
  leftBackMotor.moveAbsolute(goalDegrees, finalVelocity);
  rightBackMotor.moveAbsolute(-goalDegrees,finalVelocity);


  while(abs(currEnc)<abs(goalDegrees)){
    currEnc =((leftFrontMotor.getPosition()+leftBackMotor.getPosition())-(rightFrontMotor.getPosition()+rightBackMotor.getPosition()))/4.0;
    pros::delay(loopDelay);
  }
  master.setText(1,1,info);

}*/
