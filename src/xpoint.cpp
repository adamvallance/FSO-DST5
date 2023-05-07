#include "xpoint.h"
XPoint::XPoint(PinName* motorControlsOut, PinName* motorButtonInputs): 
    //initialise member digital outputs which are static based on the input list of pin names
    i2c()
    
    motor1Step(motorControlsOut[0], 0),
    motor1Dir(motorControlsOut[1], 0),
    motor2Step(motorControlsOut[2], 0),
    motor2Dir(motorControlsOut[3], 0), 
    //initialise member interrupt inputs 
    motorDirCtrlUp(motorButtonInputs[0]),
    motorDirCtrlDown(motorButtonInputs[1]),
    motorDirCtrlLeft(motorButtonInputs[2]),
    motorDirCtrlRight(motorButtonInputs[3])

{   
    
    ;
}

void MotorDriver::start(){
    //register interrupt callbacks
    motorDirCtrlUp.fall(callback(this, &MotorDriver::stepUp));
    motorDirCtrlDown.fall(callback(this, &MotorDriver::stepDown));
    motorDirCtrlLeft.fall(callback(this, &MotorDriver::stepLeft));
    motorDirCtrlRight.fall(callback(this, &MotorDriver::stepRight));

    exec();
}