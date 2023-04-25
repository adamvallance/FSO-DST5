#include "motorDriver.h"


MotorDriver::MotorDriver(PinName* motorControlsOut): 
    //initialise member digital outputs which are static based on the input list of pin names
    stepUp(motorControlsOut[0], 1),
    stepDown(motorControlsOut[1], 1),
    stepLeft(motorControlsOut[2], 1),
    stepRight(motorControlsOut[3], 1)
    {
        stepMotor(0);

    
    ;//do other setup
}

void MotorDriver::stepMotor(int direction){
    while (true) {
        //motorControls[0] = ! motorControls[0];
        stepUp = !stepUp;
        ThisThread::sleep_for(200ms);
    }
    //step in direction as indicated by input int
    ;
}