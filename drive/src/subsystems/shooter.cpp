#include "subsystems/shooter.hpp"
#include "subsystems/globals.hpp"
#include "subsystems/drivetrain.hpp"

//initialize motor port
const int8_t shooterPort = 1;

//initialize motor
okapi::Motor shooter(shooterPort, true, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);

int shooterState = 0; //global state variable

void updateShooter(){
    if(controller[okapi::ControllerDigital::R2].isPressed()){
				if(shooterState == 0){
					shooterState++;
					shooter.moveVelocity(500);
					//ensures bot will not move while shooting
					//hold
					leftMiddleMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
					rightMiddleMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
					
				}
				else if(shooterState == 2){
					shooterState++;
					shooter.moveVelocity(0);
					//coast
					leftMiddleMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
					rightMiddleMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
				}
		}
		else if(controller[okapi::ControllerDigital::R2].isPressed()){
				if(shooterState == 1){
					shooterState++;
				}
				else if(shooterState == 3){
					shooterState = 0;
				}
		}
}