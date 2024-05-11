#include "auton/pid.hpp"
#include "subsystems/drivetrain.hpp"
#include <cmath> 

const int8_t imuPort = 1;
okapi::IMU imu = okapi::IMU(imuPort);

double remap(double deg){
    if(deg == 0)
        return 0;

    int intDeg = (int)deg;
    double decimalDeg = deg - intDeg;

    if(deg > 0)
        intDeg = intDeg % 360;
    else if(deg < 0)
        intDeg = 360-(-intDeg%360);

    deg = intDeg + abs(decimalDeg);

    return (deg <= 180 ? deg : 360-deg);

}

void turnAngle(double target, bool reversed){
    okapi::IterativePosPIDController rotatePID = okapi::IterativeControllerFactory::posPID(0, 0, 0); //initialize pid
    rotatePID.setTarget(0);

    double initAngle = remap(imu.controllerGet() - target);
    
    while (abs(0 - initAngle) >= 3 || abs(leftFrontMotor.getActualVelocity() + rightFrontMotor.getActualVelocity()) > 8){
        initAngle = remap(imu.controllerGet() - target);

        if (initAngle >= 190)
            break; //dont want to overshoot and change to the other side
        
        double vel = rotatePID.step(initAngle);
        chassis->getModel()->tank(vel * (reversed ? -1 : 1), -vel * (reversed ? -1 : 1));
        pros::delay(20);
    }

    rotatePID.reset();
    chassis->getModel()->tank(0,0);
}
    


void driveDistance(double target){
    //if already there, return
    if(abs(target) <= 0.01)
        return;
    
    double distance = 0; //distance/displacement variable
    
    okapi::IterativePosPIDController drivePID = okapi::IterativeControllerFactory::posPID(0, 0, 0); //tune pid values here

    drivePID.setTarget(target); //sets target for pid

    //get initial position of drive
    double orgPosX = chassis->getState().x.convert(okapi::foot);
    double orgPosY = chassis->getState().y.convert(okapi::foot);
    
    while(abs(target - distance) > 10 || abs(leftFrontMotor.getActualVelocity() + rightFrontMotor.getActualVelocity()) > 8){ //bot keeps moving until it gets close enough or slows down enough
       //get updated position of drive
        double state_x = chassis->getState().x.convert(okapi::foot); 
        double state_y = chassis->getState().y.convert(okapi::foot);

        distance = sqrt(pow(orgPosX-state_x, 2) + pow(orgPosY-state_y, 2)); //calculate with the distance formula

        if(target < 0) //go backwards if target is backwards, makes distance negative
            distance = -1 * distance;

        double vel = drivePID.step((distance*2)/3); //velocity variable

        chassis->getModel()->tank(vel, vel); //sends power to motors

        pros::delay(16); //delay

    }

    drivePID.reset();
    chassis->getModel()->tank(0,0);
}

