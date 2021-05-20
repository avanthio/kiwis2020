#include "ballmovement.hpp"
#include "device_setup.hpp"
#include "pros/vision.h"
#define BLUEBALL 2
#define REDBALL 1

KiwiPID strPID(300,10,20);

void strPIDsettings(){
    
    strPID.setIMax(6000);
    strPID.setIMin(0);
    strPID.setMaxErrForI(10);
    strPID.setDeadzone(0);
    strPID.setMaxOutput(12000);
    strPID.setMinOutput(-12000);
    strPID.setSetpoint(0);

}
bool checkBlue(){
    double detectedHue = opticalSens.get_hue();
    if(detectedHue>190&&detectedHue<230){
        printf("Blue Found");
        return true;
    }
    else{
        printf("No Blue :(");
        return false;
    }
}

bool checkRed(){
    double detectedHue = opticalSens.get_hue();
    if(detectedHue>0&&detectedHue<30){ 
        printf("Red Found");
        return true;
    }
    else{
        printf("No Red :(");
        return false;
    }
}

//this should result in a goal that is fully cycled, with no red inside the robot
void redCycleFull(){
    //cycle until you hit the blue ball
    int time = 0;
    while(checkBlue()==false&&time<7000){
        Intake.moveVelocity(200);
        bottomConveyorMotor.moveVelocity(400);
        topConveyorMotor.moveVelocity(600);
        pros::delay(20);
        time+=20;
    }

    //run the intakes out a little and the conveyor belt up to score the remaining red balls
    //hopefully without bouncing them together and missing some
    Intake.moveVelocity(-50);
    bottomConveyorMotor.moveVelocity(300);
    topConveyorMotor.moveVelocity(600);
    pros::delay(700);
    bottomConveyorMotor.moveVelocity(0);
    topConveyorMotor.moveVelocity(0);
    Intake.moveVelocity(0);
}


//this should cycle the goal and keep one of the red balls (hopefully)
void redCycleSimple(){
    int time = 0;
    //cycle until you hit blue
    while(checkBlue()==false&&time<7000){
        Intake.moveVelocity(200);
        bottomConveyorMotor.moveVelocity(600);
        topConveyorMotor.moveVelocity(600);
        pros::delay(20);
        time+=20;
    }
    //stop everything to keep one red
    Intake.moveVelocity(0);
    bottomConveyorMotor.moveVelocity(0);
    topConveyorMotor.moveVelocity(0);
}

//cycle out a goal and score all the blue balls
void blueCycleFull(){
    int time = 0;
    while(checkRed()==false&&time<7000){
        Intake.moveVelocity(200);
        bottomConveyorMotor.moveVelocity(400);
        topConveyorMotor.moveVelocity(600);
        pros::delay(20);
        time+=20;
    }

    //run the intakes out a little and the conveyor belt up to score the remaining red balls
    //hopefully without bouncing them together and missing some
    Intake.moveVelocity(-50);
    bottomConveyorMotor.moveVelocity(300);
    topConveyorMotor.moveVelocity(600);
    pros::delay(700);
    bottomConveyorMotor.moveVelocity(0);
    topConveyorMotor.moveVelocity(0);
    Intake.moveVelocity(0);
}


//cycle out a goal and keep one of the blue balls
void blueCycleSimple(){
    int time = 0;
    //cycle until you hit red
     while(checkRed()==false&&time<7000){
        Intake.moveVelocity(200);
        bottomConveyorMotor.moveVelocity(600);
        topConveyorMotor.moveVelocity(600);
        pros::delay(20);
        time+=20;
    }

    //stop everything (so you keep one blue)
    Intake.moveVelocity(0);
    bottomConveyorMotor.moveVelocity(0);
    topConveyorMotor.moveVelocity(0);
}


pros::vision_object_s_t identifyRedBall(){
    pros::vision_object_s_t redBall = visionSensor.get_by_sig(0,REDBALL);
    
    return redBall;
}

pros::vision_object_s_t identifyBlueBall(){
    pros::vision_object_s_t blueBall = visionSensor.get_by_sig(0,BLUEBALL);

    return blueBall;
}

void goToRedBall(struct Position goalP){

    strPID.reset();

    pros::vision_object_s_t redBall;
    int angleError = 0;
    int angleAdjustment = 0;
    int baseVoltage = 8000;
    int voltage = 0;
    struct Position currentPos = getPosition();
    struct Position startOfDrive = currentPos;
    double distanceToGoalPos = distanceToPoint(currentPos,goalP);
    double initialDistance = distanceToGoalPos;
    double distanceTravelled;
    double pastThreeErrorSum;
    int loopCount = 0;
    double errAverage = 0;
    double previousErrAverage = 0;
    int x = 0;

    while(abs(distanceToGoalPos)>9){
        errno = 0;
        redBall = identifyRedBall();
        if(errno == EDOM){
            break;
        }
        angleError = 158 - redBall.x_middle_coord; 
        angleAdjustment = angleError*25;
        currentPos = getPosition();
        distanceToGoalPos = distanceToPoint(currentPos,goalP);

        rightFrontMotor.moveVoltage(baseVoltage+angleAdjustment);
        rightBackMotor.moveVoltage(baseVoltage+angleAdjustment);
        leftFrontMotor.moveVoltage(baseVoltage-angleAdjustment);
        leftBackMotor.moveVoltage(baseVoltage-angleAdjustment);  
      
        pros::delay(50);
        currentPos = getPosition();
        distanceToGoalPos = distanceToPoint(currentPos,goalP);
        if(distanceToGoalPos<9){
            break;
        }
        pros::delay(50);
        currentPos = getPosition();
        distanceToGoalPos = distanceToPoint(currentPos,goalP);
        if(distanceToGoalPos<9){
            break;
        }
        pros::delay(50);
        currentPos = getPosition();
        distanceToGoalPos = distanceToPoint(currentPos,goalP);
        if(distanceToGoalPos<9){
            break;
        }
        pros::delay(50);
        currentPos = getPosition();
        distanceToGoalPos = distanceToPoint(currentPos,goalP);
        if(distanceToGoalPos<9){
            break;
        }
        pros::delay(50);
        currentPos = getPosition();
        distanceToGoalPos = distanceToPoint(currentPos,goalP);
        if(distanceToGoalPos<9){
            break;
        }
        pros::delay(50);
        currentPos = getPosition();
        distanceToGoalPos = distanceToPoint(currentPos,goalP);
        if(distanceToGoalPos<9){
            break;
        }
        pros::delay(50);
        currentPos = getPosition();
        distanceToGoalPos = distanceToPoint(currentPos,goalP);
        if(distanceToGoalPos<9){
            break;
        }
        pros::delay(50);
        currentPos = getPosition();
        distanceToGoalPos = distanceToPoint(currentPos,goalP);
        if(distanceToGoalPos<9){
            break;
        }
        pros::delay(50);
        currentPos = getPosition();
        distanceToGoalPos = distanceToPoint(currentPos,goalP);
        if(distanceToGoalPos<9){
            break;
        }
    }

        rightFrontMotor.moveVoltage(baseVoltage);
        rightBackMotor.moveVoltage(baseVoltage);
        leftFrontMotor.moveVoltage(baseVoltage);
        leftBackMotor.moveVoltage(baseVoltage);  

    //std::cout<<"broke first loop\n";

    while(1){
        currentPos = getPosition();
        distanceTravelled = distanceToPoint(startOfDrive,currentPos);
    
        distanceToGoalPos = initialDistance-distanceTravelled;

        //std::cout<<"distance to goal "<< distanceToGoalPos <<"\n";

        baseVoltage = strPID.getOutput(-distanceToGoalPos);

        pastThreeErrorSum += distanceToGoalPos;
        if(loopCount%20 == 0){
            errAverage = pastThreeErrorSum/3;
        if(abs(previousErrAverage-errAverage)<0.05){
          break;
        }
            previousErrAverage = errAverage;
            errAverage = 0;
            pastThreeErrorSum = 0;
        }
        loopCount+=1;


        if(abs(distanceToGoalPos)<1){
          x+=1;
        }
        else{
            x = 0;
        }

        if(x>10){
        break;
        }

        rightFrontMotor.moveVoltage(baseVoltage);
        rightBackMotor.moveVoltage(baseVoltage);
        leftFrontMotor.moveVoltage(baseVoltage);
        leftBackMotor.moveVoltage(baseVoltage); 

    pros::delay(20);
    }
    //std::cout<<"all done";

    rightFrontMotor.moveVoltage(0);
    leftFrontMotor.moveVoltage(0);
    rightBackMotor.moveVoltage(0);
    leftBackMotor.moveVoltage(0);

}

void goToBlueBall(struct Position goalP){
    strPID.reset();

    pros::vision_object_s_t blueBall;
    int angleError = 0;
    int angleAdjustment = 0;
    int baseVoltage = 6000;
    int voltage = 0;
    struct Position currentPos = getPosition();
    struct Position startOfDrive = currentPos;
    double distanceToGoalPos = distanceToPoint(currentPos,goalP);
    double initialDistance = distanceToGoalPos;
    double distanceTravelled;
    double pastThreeErrorSum;
    int loopCount = 0;
    double errAverage = 0;
    double previousErrAverage = 0;
    int x = 0;

    while(1){
        errno = 0;
        blueBall = identifyBlueBall();
        if(errno == EDOM){
            break;
        }
        angleError = 158 - blueBall.x_middle_coord; 
        angleAdjustment = angleError*25;
        currentPos = getPosition();
        distanceToGoalPos = distanceToPoint(currentPos,goalP);

        rightFrontMotor.moveVoltage(baseVoltage+angleAdjustment);
        rightBackMotor.moveVoltage(baseVoltage+angleAdjustment);
        leftFrontMotor.moveVoltage(baseVoltage-angleAdjustment);
        leftBackMotor.moveVoltage(baseVoltage-angleAdjustment);  
      
       pastThreeErrorSum += distanceToGoalPos;

            errAverage = pastThreeErrorSum/3;
        if(abs(previousErrAverage-errAverage)<0.05){
          break;
        }
            previousErrAverage = errAverage;
            errAverage = 0;
            pastThreeErrorSum = 0;
        

        pros::delay(150);
        currentPos = getPosition();
        distanceToGoalPos = distanceToPoint(currentPos,goalP);
               pastThreeErrorSum += distanceToGoalPos;
            errAverage = pastThreeErrorSum/3;
        if(abs(previousErrAverage-errAverage)<0.05){
          break;
        }
            previousErrAverage = errAverage;
            errAverage = 0;
            pastThreeErrorSum = 0;
        
        pros::delay(150);
        currentPos = getPosition();
        distanceToGoalPos = distanceToPoint(currentPos,goalP);
               pastThreeErrorSum += distanceToGoalPos;
       
            errAverage = pastThreeErrorSum/3;
        if(abs(previousErrAverage-errAverage)<0.05){
          break;
        }
            previousErrAverage = errAverage;
            errAverage = 0;
            pastThreeErrorSum = 0;
    
        pros::delay(150);
        
        
 
    }
    rightFrontMotor.moveVoltage(0);
    leftFrontMotor.moveVoltage(0);
    rightBackMotor.moveVoltage(0);
    leftBackMotor.moveVoltage(0);
}


void goToBlueBallSoft(struct Position goalP){
    strPID.reset();

    pros::vision_object_s_t blueBall;
    int angleError = 0;
    int angleAdjustment = 0;
    int baseVoltage = 6000;
    int voltage = 0;
    struct Position currentPos = getPosition();
    struct Position startOfDrive = currentPos;
    double distanceToGoalPos = distanceToPoint(currentPos,goalP);
    double initialDistance = distanceToGoalPos;
    double distanceTravelled;
    double pastThreeErrorSum;
    int loopCount = 0;
    double errAverage = 0;
    double previousErrAverage = 0;
    int x = 0;

    while(1){
        errno = 0;
        blueBall = identifyBlueBall();
        if(errno == EDOM){
            break;
        }
        angleError = 158 - blueBall.x_middle_coord; 
        angleAdjustment = angleError*25;
        currentPos = getPosition();
        distanceToGoalPos = distanceToPoint(currentPos,goalP);

        rightFrontMotor.moveVoltage(baseVoltage+angleAdjustment);
        rightBackMotor.moveVoltage(baseVoltage+angleAdjustment);
        leftFrontMotor.moveVoltage(baseVoltage-angleAdjustment);
        leftBackMotor.moveVoltage(baseVoltage-angleAdjustment);  
      
      pastThreeErrorSum += distanceToGoalPos;

            errAverage = pastThreeErrorSum/3;
        if(abs(previousErrAverage-errAverage)<0.05){
          break;
        }
            previousErrAverage = errAverage;
            errAverage = 0;
            pastThreeErrorSum = 0;
        

        pros::delay(150);
        currentPos = getPosition();
        distanceToGoalPos = distanceToPoint(currentPos,goalP);
               pastThreeErrorSum += distanceToGoalPos;
            errAverage = pastThreeErrorSum/3;
        if(abs(previousErrAverage-errAverage)<0.05){
          break;
        }
            previousErrAverage = errAverage;
            errAverage = 0;
            pastThreeErrorSum = 0;
        
        pros::delay(150);
        currentPos = getPosition();
        distanceToGoalPos = distanceToPoint(currentPos,goalP);
               pastThreeErrorSum += distanceToGoalPos;
       
            errAverage = pastThreeErrorSum/3;
        if(abs(previousErrAverage-errAverage)<0.05){
          break;
        }
            previousErrAverage = errAverage;
            errAverage = 0;
            pastThreeErrorSum = 0;
    
        pros::delay(150);
    }
    rightFrontMotor.moveVoltage(0);
    leftFrontMotor.moveVoltage(0);
    rightBackMotor.moveVoltage(0);
    leftBackMotor.moveVoltage(0);
}


void alignToBlue(struct Position goalP){

     pros::vision_object_s_t blueBall;
    int angleError = 0;
    int angleAdjustment = 0;
    int baseVoltage = 6000;
    int voltage = 0;
    struct Position currentPos = getPosition();
    struct Position startOfDrive = currentPos;
    double distanceToGoalPos = distanceToPoint(currentPos,goalP);
    double initialDistance = distanceToGoalPos;
    double distanceTravelled;
    double pastThreeErrorSum;
    int loopCount = 0;
    double errAverage = 0;
    double previousErrAverage = 0;
    int x = 0;


    while(1){
        errno = 0;
        blueBall = identifyBlueBall();
        if(errno == EDOM){
            break;
        }
        angleError = 158 - blueBall.x_middle_coord; 
        angleAdjustment = angleError*25;
        currentPos = getPosition();
        distanceToGoalPos = distanceToPoint(currentPos,goalP);

        rightFrontMotor.moveVoltage(-baseVoltage+angleAdjustment);
        rightBackMotor.moveVoltage(-baseVoltage+angleAdjustment);
        leftFrontMotor.moveVoltage(-baseVoltage-angleAdjustment);
        leftBackMotor.moveVoltage(-baseVoltage-angleAdjustment);  
      
       pastThreeErrorSum += distanceToGoalPos;

            errAverage = pastThreeErrorSum/3;
        if(abs(previousErrAverage-errAverage)<0.05){
          break;
        }
            previousErrAverage = errAverage;
            errAverage = 0;
            pastThreeErrorSum = 0;
        

        pros::delay(150);
        currentPos = getPosition();
        distanceToGoalPos = distanceToPoint(currentPos,goalP);
               pastThreeErrorSum += distanceToGoalPos;
            errAverage = pastThreeErrorSum/3;
        if(abs(previousErrAverage-errAverage)<0.05){
          break;
        }
            previousErrAverage = errAverage;
            errAverage = 0;
            pastThreeErrorSum = 0;
        
        pros::delay(150);
        currentPos = getPosition();
        distanceToGoalPos = distanceToPoint(currentPos,goalP);
               pastThreeErrorSum += distanceToGoalPos;
       
            errAverage = pastThreeErrorSum/3;
        if(abs(previousErrAverage-errAverage)<0.05){
          break;
        }
            previousErrAverage = errAverage;
            errAverage = 0;
            pastThreeErrorSum = 0;
    
        pros::delay(150);
    }
    rightFrontMotor.moveVoltage(0);
    leftFrontMotor.moveVoltage(0);
    rightBackMotor.moveVoltage(0);
    leftBackMotor.moveVoltage(0);
}