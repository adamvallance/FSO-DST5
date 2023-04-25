#include "motorDriver.h"


MotorDriver::MotorDriver(DigitalOut* motorControlsIn): motorControls(motorControlsIn){
    while (true) {
        motorControls[0] = ! motorControls[0];
        ThisThread::sleep_for(200ms);
    }
    
    ;//do other setup
}

void MotorDriver::stepMotor(int direction){
    //step in direction as indicated by input int
    ;
}