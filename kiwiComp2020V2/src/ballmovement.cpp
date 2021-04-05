#include "ballmovement.hpp"
#include "device_setup.hpp"

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