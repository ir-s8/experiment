#include "subsystems/shooter.hpp"
#include "subsystems/globals.hpp"
#include "subsystems/drivetrain.hpp"

//initialize motor port
const int8_t shooterPort = 8;

//initialize motor
okapi::Motor shooter(shooterPort, true, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);

int shooterState = 0; //global state variable

void updateShooter(){
    if(controller[okapi::ControllerDigital::R2].isPressed()){
				if(shooterState == 0){
					shooterState++;
					shooter.moveVelocity(45);
					//ensures bot will not move while shooting
					//hold
					leftFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
					rightFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
					
				}
				else if(shooterState == 2){
					shooterState++;
					shooter.moveVelocity(0);
					//coast
					leftFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
					rightFrontMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
				}
		}
		else if(!controller[okapi::ControllerDigital::R2].isPressed()){
				if(shooterState == 1){
					shooterState++;
				}
				else if(shooterState == 3){
					shooterState = 0;
				}
		}
}