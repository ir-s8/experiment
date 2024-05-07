#include "subsystems/intake.hpp"
#include "subsystems/globals.hpp"

const int8_t intakePort = 1;

//initializing motor with motor ports, cartridge, etc.
okapi::Motor intake(intakePort, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);

int intakeState = 0; //global state variable

//defining intake function
void updateIntake(){
    //toggle with various states
	if(controller[okapi::ControllerDigital::R1].isPressed()){
				if(intakeState == 0){
					intakeState++;
					intake.moveVelocity(600);
				}
				else if(intakeState == 2){
					intakeState++;
					intake.moveVelocity(0);
				}
		}
		else if(controller[okapi::ControllerDigital::R1].isPressed()){
				if(intakeState == 1){
					intakeState++;
				}
				else if(intakeState == 3){
					intakeState = 0;
				}
		}
}