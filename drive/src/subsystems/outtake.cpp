#include "subsystems/outtake.hpp"
#include "subsystems/globals.hpp"
#include "subsystems/intake.hpp"

//intitializing motor port
//const int8_t outtakePort = 10;

//initialize motor
okapi::Motor outtake(intakePort, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);

int outtakeState = 0; //global state variable

void updateOuttake(){
	//toggle to control outtake
    if(controller[okapi::ControllerDigital::L1].isPressed()){
				if(outtakeState == 0){
					outtakeState++;
					outtake.moveVelocity(-600);
				}
				else if(outtakeState == 2){
					outtakeState++;
					outtake.moveVelocity(0);
				}
		}
		else if(!controller[okapi::ControllerDigital::L1].isPressed()){
				if(outtakeState == 1){
					outtakeState++;
				}
				else if(outtakeState == 3){
					outtakeState = 0;
				}
		}
}