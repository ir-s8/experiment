#include "main.h"

extern const int8_t imuPort;
extern okapi::IMU imu;

void driveDistance(double targetDistance);
double remap(double deg);
void turnAngle(double target, bool reversed);