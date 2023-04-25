#include "motorDriver.h"


MotorDriver::MotorDriver(PinName* motorControlsOut, PinName* motorButtonInputs): 
    //initialise member digital outputs which are static based on the input list of pin names
    motor1Step(motorControlsOut[0], 1),
    motor1Dir(motorControlsOut[1], 1),
    motor2Step(motorControlsOut[2], 1),
    motor2Dir(motorControlsOut[3], 1), 
    //initialise member interrupt inputs 
    motorDirCtrlUp(motorButtonInputs[0]),
    motorDirCtrlDown(motorButtonInputs[1]),
    motorDirCtrlLeft(motorButtonInputs[2]),
    motorDirCtrlRight(motorButtonInputs[3])

    {
        stepMotor(0);

    
    ;//do other setup
}

void MotorDriver::stepMotor(int direction){
    while (true) {
        //motorControls[0] = ! motorControls[0];
        motor1Step = !motor1Step;
        ThisThread::sleep_for(200ms);
    }
    //step in direction as indicated by input int
    ;
}