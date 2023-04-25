#include "motorDriver.h"


MotorDriver::MotorDriver(PinName* motorControlsIn): 
    //initialise member digital outputs which are static based on the input list of pin names
    stepUp(motorControlsIn[0]),
    stepDown(motorControlsIn[1]),
    stepLeft(motorControlsIn[2]),
    stepRight(motorControlsIn[3])
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